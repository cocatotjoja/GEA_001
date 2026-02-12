#pragma once

#include <iostream>
#include <vector>
#include "config.h"
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "core/random.h"

namespace Thingies
{
class WorldManager
{
private:
	std::vector<Entity> entities;
	std::vector<MeshComp> meshes;
	std::vector<TransformComp> transforms;
	std::vector<ColliderComp> colliders;

	// Vectors for different components

	// Resources
	Render::ModelId models[6];
	Physics::ColliderMeshId colliderMeshes[6];

public:
	WorldManager();
	~WorldManager();
	void Start();
	void Update();

	void AddAsteroid();
};
}



