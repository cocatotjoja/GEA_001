#include "config.h"
#include "worldManager.h"
//#include "entity.h"

using namespace Thingies;

WorldManager::WorldManager()
{
    std::cout << "World Manager Created" << std::endl;
}

WorldManager::~WorldManager()
{
    //std::cout << "World Manager Destroyed" << std::endl;
}

void WorldManager::Start(bool isServer, std::string IP)
{
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


    // Set up ENet manager
    if (isServer == true)
    {
        ENetServices = new NetServer(*this);


        AddShip(nextID);

        // Add near asteroids
        for (size_t i = 0; i < 100; i++)
        {
            // Update entityID

            AddAsteroid(20.0f, nextID);
            nextID++;
        }
        // Add far asteroids
        for (size_t i = 0; i < 50; i++)
        {
            // Update entityID
            AddAsteroid(80.0f, nextID);
            nextID++;
        }
    }
    else
    {
        ENetServices = new NetClient(*this);
    }
    ENetServices->Start(IP);
    this->entities.reserve(10000);
}

void WorldManager::AddAsteroid(float span, uint32_t ID)
{
    // Generate random mesh index
    size_t resourceIndex = (size_t)(Core::FastRandom() % 6);
    // Create Asteroid Entity
    Entity* entity = new Entity();
    entities.push_back(entity);

    UpdateIndexMap();

    // Generate random location
    glm::vec3 translation = glm::vec3(
        Core::RandomFloatNTP() * span,
        Core::RandomFloatNTP() * span,
        Core::RandomFloatNTP() * span
    );
    glm::vec3 rotationAxis = normalize(translation);
    float rotation = translation.x;
    glm::mat4 transform = glm::rotate(rotation, rotationAxis) * glm::translate(translation);
    
    
    TransformComp* tComp = new TransformComp(entity, transform);
    MeshComp* mComp = new MeshComp(entity, models[resourceIndex], tComp);
    ColliderComp* cComp = new ColliderComp(entity, Physics::CreateCollider(colliderMeshes[resourceIndex], transform), tComp);
    MoveComp* moveComp = new MoveComp(entity, rotationAxis, glm::radians(Core::RandomFloatNTP()*4), tComp);


    entity->AddComp(tComp);
    entity->AddComp(mComp);
    entity->AddComp(cComp);
    entity->AddComp(moveComp);
}

void WorldManager::AddShip(uint32_t ID)
{
    Entity* entity = new Entity();
    entities.push_back(entity);

    UpdateIndexMap();

    TransformComp* tComp = new TransformComp(entity, glm::mat4(1));
    MeshComp* mComp = new MeshComp(entity, shipModel, tComp);
    ShipComp* sComp = new ShipComp(entity, tComp);
    HealthComp* hComp = new HealthComp(entity, 100);
    LaserComp* lComp = new LaserComp(entity, tComp);

    entity->AddComp(tComp);
    entity->AddComp(mComp);
    entity->AddComp(sComp);
    entity->AddComp(hComp);
}

void Thingies::WorldManager::UpdateIndexMap()
{
    entityIndex[nextID] = entities.size() - 1;
    nextID++;
}

Entity* Thingies::WorldManager::GetEntity(uint32_t index)
{
    size_t entIndex;

    auto it = entityIndex.find(index);

    if (it != entityIndex.end())
    {
        entIndex = entityIndex.at(index);
    }
    else
    {
        return nullptr;
    }

    if (entIndex < entities.size())
    {
        return entities[entIndex];
    }

    return nullptr;
}

void WorldManager::Update(float dt)
{
    // For checking that colliders rotate
    //Physics::DebugDrawColliders();

    // Check for ENet events
    ENetServices->Update();

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