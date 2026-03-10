#pragma once
#include <iostream>
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "render/particlesystem.h"
#include "core/random.h"


#include <enet/enet.h>

enum ConnectionResult
{
	CONNECTION_FAILED,
	CONNECTION_SUCCEEDED
};

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
	ConnectionResult Start();
	void Update();
};