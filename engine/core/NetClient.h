#pragma once
#include <iostream>
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "render/particlesystem.h"
#include "core/random.h"


#include <enet/enet.h>


class NetClient
{
private:
	ENetHost* client;
	ENetAddress address;
	ENetEvent event;
	ENetPeer* peer;

public:
	NetClient();
	~NetClient();
	void Update();
};