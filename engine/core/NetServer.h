#pragma once
#include <iostream>
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "render/particlesystem.h"
#include "core/random.h"

#include <enet/enet.h>

#include "NetClient.h"

class NetServer : public NetBase
{
private:
	ENetHost* server;
	ENetAddress address;
	ENetEvent event;

public:
	NetServer(Thingies::WorldManager& newOwner) : NetBase(newOwner) {};
	~NetServer() {};
	ActionResult Start(std::string IP) override;
	ActionResult End() override;
	void Update() override;
	void AddClient();
	void RemoveClient();
	void Broadcast();
};

