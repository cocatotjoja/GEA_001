#pragma once
#include <iostream>

namespace Thingies
{
	class WorldManager;
}

enum ActionResult
{
	ACTION_FAILED,
	ACTION_SUCCEEDED
};

enum PacketType
{
	CLIENT_START = 1,
	ASTEROID_START = 2,
	ASTEROID_UPDATE = 3,
	SHIP_START = 4,
	SHIP_UPDATE = 5
};

struct ClientStart
{
	int packetType;
	int ClientID;
};

struct AsteroidStart
{
	int packetType;
	uint32_t meshID;
	uint32_t entityID;
	float transform[16];
	float axis[3];
	float angle;
};

struct AsteroidUpdate
{
	int packetType;
	uint32_t entityID;
	float transform[16];
};

struct ShipStart
{
	uint32_t OwnerID;
	uint32_t entityID;
	float transform[16];
	int health;
};

struct ShipUpdate
{
	uint32_t entityID;
	float transform[16];
	int health;
};

class NetBase
{
public:
	Thingies::WorldManager& owner;

	NetBase(Thingies::WorldManager& newOwner) : owner(newOwner) {};
	virtual ~NetBase() {};
	virtual ActionResult Start(std::string IP);
	virtual ActionResult End();
	virtual void Update() {};

	void UpdateAsteroid(AsteroidUpdate packetData);
};