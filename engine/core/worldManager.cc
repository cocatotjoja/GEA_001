#include "config.h"
#include "worldManager.h"
//#include "entity.h"

using namespace Thingies;

Thingies::WorldManager::WorldManager()
{
    //std::cout << "World Manager Created" << std::endl;
}

Thingies::WorldManager::~WorldManager()
{
    //std::cout << "World Manager Destroyed" << std::endl;
}

void WorldManager::Start()
{
    this->entities.reserve(10000);

    // Load all models
    models[0] = Render::LoadModel("assets/space/Asteroid_1.glb");
    models[1] = Render::LoadModel("assets/space/Asteroid_2.glb");
    models[2] = Render::LoadModel("assets/space/Asteroid_3.glb");
    models[3] = Render::LoadModel("assets/space/Asteroid_4.glb");
    models[4] = Render::LoadModel("assets/space/Asteroid_5.glb");
    models[5] = Render::LoadModel("assets/space/Asteroid_6.glb");
    
    // Load all colliders
    colliderMeshes[0] = Physics::LoadColliderMesh("assets/space/Asteroid_1_physics.glb");
    colliderMeshes[1] = Physics::LoadColliderMesh("assets/space/Asteroid_2_physics.glb");
    colliderMeshes[2] = Physics::LoadColliderMesh("assets/space/Asteroid_3_physics.glb");
    colliderMeshes[3] = Physics::LoadColliderMesh("assets/space/Asteroid_4_physics.glb");
    colliderMeshes[4] = Physics::LoadColliderMesh("assets/space/Asteroid_5_physics.glb");
    colliderMeshes[5] = Physics::LoadColliderMesh("assets/space/Asteroid_6_physics.glb");

    // Load ship model
    shipModel = Render::LoadModel("assets/space/spaceship.glb");
    
    // Add near asteroids
    for (size_t i = 0; i < 100; i++)
    {
        AddAsteroid(20.0f);
    }
    // Add far asteroids
    for (size_t i = 0; i < 50; i++)
    {
        AddAsteroid(80.0f);
    }
}

void WorldManager::AddAsteroid(float span)
{
    // Generate random mesh index
    size_t resourceIndex = (size_t)(Core::FastRandom() % 6);
    // Create Asteroid Entity
    Entity* entity = new Entity();
    entities.push_back(entity);

    // Generate random location
    glm::vec3 translation = glm::vec3(
        Core::RandomFloatNTP() * span,
        Core::RandomFloatNTP() * span,
        Core::RandomFloatNTP() * span
    );
    glm::vec3 rotationAxis = normalize(translation);
    float rotation = translation.x;
    glm::mat4 transform = glm::rotate(rotation, rotationAxis) * glm::translate(translation);
    
    // Add component to transform vector
    TransformComp* tComp = new TransformComp(entity, transform);

    // Add Mesh Component to mesh vector
    MeshComp* mComp = new MeshComp(entity, models[resourceIndex], tComp);

    // Create Collider Component
    ColliderComp* cComp = new ColliderComp(entity, Physics::CreateCollider(colliderMeshes[resourceIndex], transform));

    // Add TransformComp to Asteroid
    entity->AddComp(tComp);
    // Add MeshComp to Asteroid
    entity->AddComp(mComp);
    // Add Collider Comp to Asteroid
    entity->AddComp(cComp);
}

void Thingies::WorldManager::AddShip()
{
    Entity* entity = new Entity();
    entities.push_back(entity);

    // Add Ship Component
    ShipComp* sComp = new ShipComp(entity, shipModel);
}

void WorldManager::Update(float dt)
{
    // TODO: Update entities
    for (size_t i = 0; i < this->entities.size(); i++)
    {
        this->entities[i]->Update(dt);
    }
    
    for (size_t i = 0; i < this->entities.size(); i++)
    {
        this->entities[i]->Draw();
    }
}