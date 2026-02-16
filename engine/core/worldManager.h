#pragma once

#include <iostream>
#include <vector>
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "core/random.h"
#include "entity.h"

namespace Thingies
{
class WorldManager
{
private:
	// Vector for entities
	std::vector<Entity*> entities;

	// Vectors for different components
	//std::vector<MeshComp> meshes;
	//std::vector<TransformComp> transforms;
	//std::vector<ColliderComp> colliders;


	// Resources
	Render::ModelId models[6];
	Physics::ColliderMeshId colliderMeshes[6];

public:
	WorldManager();
	~WorldManager();
	void Start();
	void Update();

	void AddAsteroid(float span);
	Render::ModelId GetMesh(size_t index);
	glm::mat4 GetTransform(size_t index);
	
};
}



