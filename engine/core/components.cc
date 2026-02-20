#include "config.h"
#include "components.h"
#include "entity.h"
#include "render/renderdevice.h"
#include "render/input/inputserver.h"
#include "render/cameramanager.h"
#include "render/debugrender.h"






// Base Component functions------------------------------------------------------------------------------

Thingies::BaseComponent::BaseComponent()
{
	owner = nullptr;
	type = BASE;
	//std::cout << "Base Component Created!" << std::endl;
}

Thingies::BaseComponent::~BaseComponent()
{
	//std::cout << "Base Component Destroyed!" << std::endl;
}

void Thingies::BaseComponent::Start()
{
	//std::cout << "Base Component Start!" << std::endl;
}

Thingies::Entity* Thingies::BaseComponent::GetOwner()
{
	return owner;
}

CompType Thingies::BaseComponent::GetType()
{
	return type;
}



// Mesh Component functions------------------------------------------------------------------------------

Thingies::MeshComp::~MeshComp()
{
	//std::cout << "Mesh Component Destroyed!" << std::endl;
}

Render::ModelId Thingies::MeshComp::GetMesh()
{
	return mesh;
}

glm::mat4 Thingies::MeshComp::PullTransform()
{
	return transform->GetTransform();
}

void Thingies::MeshComp::Draw()
{
	Render::RenderDevice::Draw(this->GetMesh(), this->PullTransform());
}





// Transform Component functions-------------------------------------------------------------------------

Thingies::TransformComp::~TransformComp()
{
	//std::cout << "Transform Component Destroyed!" << std::endl;
}

glm::mat4 Thingies::TransformComp::GetTransform()
{
	return transform;
}






// Collider Component functions-------------------------------------------------------------------------

Thingies::ColliderComp::~ColliderComp()
{
	//std::cout << "Collider Component Destroyed!" << std::endl;
}

Physics::ColliderId Thingies::ColliderComp::GetCollider()
{
	return collider;
}






// Ship Component functions-------------------------------------------------------------------------

Thingies::ShipComp::ShipComp(Entity* newOwner, Render::ModelId mID)
{
    this->owner = newOwner;
    uint32_t numParticles = 2048;
    this->particleEmitterLeft = new Render::ParticleEmitter(numParticles);
    this->particleEmitterLeft->data = {
        .origin = glm::vec4(this->position + (glm::vec3(this->transform[2]) * emitterOffset),1), // TODO: Ask Fredrik to explain how this works after the ship moves (It is not updated in Update function)
        .dir = glm::vec4(glm::vec3(-this->transform[2]), 0),
        .startColor = glm::vec4(0.38f, 0.76f, 0.95f, 1.0f) * 2.0f,
        .endColor = glm::vec4(0,0,0,1.0f),
        .numParticles = numParticles,
        .theta = glm::radians(0.0f),
        .startSpeed = 1.2f,
        .endSpeed = 0.0f,
        .startScale = 0.025f,
        .endScale = 0.0f,
        .decayTime = 2.58f,
        .randomTimeOffsetDist = 2.58f,
        .looping = 1,
        .emitterType = 1,
        .discRadius = 0.020f
    };
    this->particleEmitterRight = new Render::ParticleEmitter(numParticles);
    this->particleEmitterRight->data = this->particleEmitterLeft->data;

    Render::ParticleSystem::Instance()->AddEmitter(this->particleEmitterLeft);
    Render::ParticleSystem::Instance()->AddEmitter(this->particleEmitterRight);

    model = mID;
}

Thingies::ShipComp::~ShipComp()
{
	//std::cout << "Ship Component Destroyed!" << std::endl;
}

void Thingies::ShipComp::Update(float dt)
{
    Input::Mouse* mouse = Input::GetDefaultMouse();
    Input::Keyboard* kbd = Input::GetDefaultKeyboard();

    Render::Camera* cam = Render::CameraManager::GetCamera(CAMERA_MAIN);

    if (kbd->held[Input::Key::W])
    {
        if (kbd->held[Input::Key::Shift])
            this->currentSpeed = glm::mix(this->currentSpeed, this->boostSpeed, std::min(1.0f, dt * 30.0f));
        else
            this->currentSpeed = glm::mix(this->currentSpeed, this->normalSpeed, std::min(1.0f, dt * 90.0f));
    }
    else
    {
        this->currentSpeed = 0;
    }
    glm::vec3 desiredVelocity = glm::vec3(0, 0, this->currentSpeed);
    desiredVelocity = this->transform * glm::vec4(desiredVelocity, 0.0f);

    this->linearVelocity = mix(this->linearVelocity, desiredVelocity, dt * accelerationFactor);

    float rotX = kbd->held[Input::Key::Left] ? 1.0f : kbd->held[Input::Key::Right] ? -1.0f : 0.0f;
    float rotY = kbd->held[Input::Key::Up] ? -1.0f : kbd->held[Input::Key::Down] ? 1.0f : 0.0f;
    float rotZ = kbd->held[Input::Key::A] ? -1.0f : kbd->held[Input::Key::D] ? 1.0f : 0.0f;

    this->position += this->linearVelocity * dt * 10.0f;

    const float rotationSpeed = 1.8f * dt;
    rotXSmooth = glm::mix(rotXSmooth, rotX * rotationSpeed, dt * cameraSmoothFactor);
    rotYSmooth = glm::mix(rotYSmooth, rotY * rotationSpeed, dt * cameraSmoothFactor);
    rotZSmooth = glm::mix(rotZSmooth, rotZ * rotationSpeed, dt * cameraSmoothFactor);
    glm::quat localOrientation = glm::quat(glm::vec3(-rotYSmooth, rotXSmooth, rotZSmooth));
    this->orientation = this->orientation * localOrientation;
    this->rotationZ -= rotXSmooth;
    this->rotationZ = glm::clamp(this->rotationZ, -45.0f, 45.0f);
    glm::mat4 T = translate(this->position) * (glm::mat4)this->orientation;
    this->transform = T * (glm::mat4)glm::quat(glm::vec3(0, 0, rotationZ));
    this->rotationZ = glm::mix(this->rotationZ, 0.0f, dt * cameraSmoothFactor);

    // update camera view transform
    glm::vec3 desiredCamPos = this->position + glm::vec3(this->transform * glm::vec4(0, camOffsetY, -4.0f, 0));
    this->camPos = mix(this->camPos, desiredCamPos, dt * cameraSmoothFactor);
    cam->view = lookAt(this->camPos, this->camPos + glm::vec3(this->transform[2]), glm::vec3(this->transform[1]));

    const float thrusterPosOffset = 0.365f;
    this->particleEmitterLeft->data.origin = glm::vec4(glm::vec3(this->position + (glm::vec3(this->transform[0]) * -thrusterPosOffset)) + (glm::vec3(this->transform[2]) * emitterOffset), 1);
    this->particleEmitterLeft->data.dir = glm::vec4(glm::vec3(-this->transform[2]), 0);
    this->particleEmitterRight->data.origin = glm::vec4(glm::vec3(this->position + (glm::vec3(this->transform[0]) * thrusterPosOffset)) + (glm::vec3(this->transform[2]) * emitterOffset), 1);
    this->particleEmitterRight->data.dir = glm::vec4(glm::vec3(-this->transform[2]), 0);

    float t = (currentSpeed / this->normalSpeed);
    this->particleEmitterLeft->data.startSpeed = 1.2 + (3.0f * t);
    this->particleEmitterLeft->data.endSpeed = 0.0f + (3.0f * t);
    this->particleEmitterRight->data.startSpeed = 1.2 + (3.0f * t);
    this->particleEmitterRight->data.endSpeed = 0.0f + (3.0f * t);
    //this->particleEmitter->data.decayTime = 0.16f;//+ (0.01f  * t);
    //this->particleEmitter->data.randomTimeOffsetDist = 0.06f;/// +(0.01f * t);

    // Add transformcomp.transform = this->tramsform

    CheckCollisions();
}

void Thingies::ShipComp::Draw()
{
    Render::RenderDevice::Draw(model, transform);
}

bool Thingies::ShipComp::CheckCollisions()
{
    glm::mat4 rotation = (glm::mat4)orientation;
    bool hit = false;
    for (int i = 0; i < sizeof(colliderEndPoints) / sizeof(glm::vec3); i++)
    {
        glm::vec3 pos = position;
        glm::vec3 dir = this->transform * glm::vec4(glm::normalize(colliderEndPoints[i]), 0.0f);
        float len = glm::length(colliderEndPoints[i]);
        Physics::RaycastPayload payload = Physics::Raycast(position, dir, len);

        // debug draw collision rays
        Debug::DrawLine(pos, pos + dir * len, 1.0f, glm::vec4(0, 1, 0, 1), glm::vec4(0, 1, 0, 1), Debug::RenderMode::AlwaysOnTop);

        if (payload.hit)
        {
            Debug::DrawDebugText("HIT", payload.hitPoint, glm::vec4(1, 1, 1, 1));
            hit = true;
        }
    }  
    return hit;
}

glm::vec3 Thingies::ShipComp::GetPos()
{
    return position;
}

glm::mat4 Thingies::ShipComp::GetTrans()
{
    return transform;
}







// Laser Component functions-------------------------------------------------------------------------
Thingies::LaserComp::LaserComp(ShipComp* sComp)
{
    // Set component variables
    laserSpeed = 10.0f;
    ship = sComp;



    // Create Particle emitter
    numParticles = 1;
    emitter = new Render::ParticleEmitter(numParticles);
    this->emitter->data = {
        .origin = glm::vec4(0,0,0,1.0f), // TODO::SET POSITION
        .dir = glm::vec4(glm::vec3(ship->GetTrans()[2]), 0),
        .startColor = glm::vec4(0.38f, 0.76f, 0.95f, 1.0f) * 2.0f,
        .endColor = glm::vec4(0,0,0,1.0f),
        .numParticles = numParticles,
        .theta = glm::radians(0.0f),
        .startSpeed = 1.2f,
        .endSpeed = 0.0f,
        .startScale = 0.025f,
        .endScale = 0.0f,
        .decayTime = 2.58f,
        .randomTimeOffsetDist = 2.58f,
        .looping = 0,
        .emitterType = 1,
        .discRadius = 0.020f
    };
    Render::ParticleSystem::Instance()->AddEmitter(emitter);

}

Thingies::LaserComp::~LaserComp()
{
    //std::cout << "Laser Component Destroyed!" << std::endl;
}

void Thingies::LaserComp::Update(float dt)
{
    Input::Keyboard* kbd = Input::GetDefaultKeyboard();
    if (kbd->held[Input::Key::Space])
    {
        //Update Position
        //Emitt particles
        // Raycast
    }
}
