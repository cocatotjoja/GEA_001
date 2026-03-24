#pragma once
#include <iostream>
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "render/particlesystem.h"
#include "core/random.h"


#include <enet/enet.h>
#include "NetBase.h"

class NetClient : public NetBase
{
private:
	ENetHost* client;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;

public:
	NetClient() {};
	~NetClient() {};
	ActionResult Start(std::string IP) override;
	ActionResult End() override;
	void Update() override;
};