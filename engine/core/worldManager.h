#pragma once

#include <iostream>
#include <vector>

#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "core/random.h"

#include "entity.h"
#include "NetBase.h"
#include "NetServer.h"
#include "NetClient.h"

namespace Thingies
{
class WorldManager
{
private:
	// Vector for entities
	std::vector<Entity*> entities;
	std::unordered_map<uint32_t, size_t> entityIndex;
	uint32_t nextID = 1;
	NetBase* ENetServices;


	// Resources
	Render::ModelId models[6];
	Physics::ColliderMeshId colliderMeshes[6];
	Render::ModelId shipModel;

public:
	WorldManager();
	~WorldManager();
	void Start(bool isServer, std::string IP);
	void Update(float dt);

	void AddAsteroid(float span, uint32_t ID);
	void AddShip(uint32_t ID);
	void UpdateIndexMap();
	
};
}



