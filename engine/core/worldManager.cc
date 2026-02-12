#include "worldManager.h"


using namespace Thingies;

void WorldManager::Start()
{
    // load all models
    models[0] = Render::LoadModel("assets/space/Asteroid_1.glb");
    models[1] = Render::LoadModel("assets/space/Asteroid_2.glb");
    models[2] = Render::LoadModel("assets/space/Asteroid_3.glb");
    models[3] = Render::LoadModel("assets/space/Asteroid_4.glb");
    models[4] = Render::LoadModel("assets/space/Asteroid_5.glb");
    models[5] = Render::LoadModel("assets/space/Asteroid_6.glb");
    
    // load all colliders
    colliderMeshes[0] = Physics::LoadColliderMesh("assets/space/Asteroid_1_physics.glb");
    colliderMeshes[1] = Physics::LoadColliderMesh("assets/space/Asteroid_2_physics.glb");
    colliderMeshes[2] = Physics::LoadColliderMesh("assets/space/Asteroid_3_physics.glb");
    colliderMeshes[3] = Physics::LoadColliderMesh("assets/space/Asteroid_4_physics.glb");
    colliderMeshes[4] = Physics::LoadColliderMesh("assets/space/Asteroid_5_physics.glb");
    colliderMeshes[5] = Physics::LoadColliderMesh("assets/space/Asteroid_6_physics.glb");
    

    for (size_t i = 0; i < 100; i++)
    {
        AddAsteroid()

    }
}

void WorldManager::AddAsteroid()
{
    size_t resourceIndex = (size_t)(Core::FastRandom() % 6);
    // Create Asteroid Entity
    entities.push_back(Entity());
    // Add Mesh Component to mesh vector
    meshes.push_back(MeshComp(models[resourceIndex]));

    // Create Transform Component
    // Generate random location
    float span = 80.0f;
    glm::vec3 translation = glm::vec3(
        Core::RandomFloatNTP() * span,
        Core::RandomFloatNTP() * span,
        Core::RandomFloatNTP() * span
    );
    glm::vec3 rotationAxis = normalize(translation);
    float rotation = translation.x;
    glm::mat4 transform = glm::rotate(rotation, rotationAxis) * glm::translate(translation);
    // Add to transform vector
    transforms.push_back(TransformComp(transform));

    // Create Collider Component
    colliders.push_back(ColliderComp(Physics::CreateCollider(colliderMeshes[resourceIndex], transform)));

    // Add MeshComp to Asteroid
    entities.back().AddComp(&meshes.back());
    // Add TransformComp to Asteroid
    entities.back().AddComp(&transforms.back());
    // Add Collider Comp to Asteroid
    entities.back().AddComp(&colliders.back());
}



/*
for (int i = 0; i < 50; i++)
{
    std::tuple<ModelId, Physics::ColliderId, glm::mat4> asteroid;
    //size_t resourceIndex = (size_t)(Core::FastRandom() % 6);
    std::get<0>(asteroid) = models[resourceIndex];
    float span = 80.0f;
    glm::vec3 translation = glm::vec3(
        Core::RandomFloatNTP() * span,
        Core::RandomFloatNTP() * span,
        Core::RandomFloatNTP() * span
    );
    glm::vec3 rotationAxis = normalize(translation);
    float rotation = translation.x;
    glm::mat4 transform = glm::rotate(rotation, rotationAxis) * glm::translate(translation);


    std::get<1>(asteroid) = Physics::CreateCollider(colliderMeshes[resourceIndex], transform);
    std::get<2>(asteroid) = transform;
    asteroids.push_back(asteroid);
}
*/