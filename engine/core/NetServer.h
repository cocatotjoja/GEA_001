#pragma once
#include <iostream>
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "render/particlesystem.h"
#include "core/random.h"

#include <enet/enet.h>


class NetServer
{
private:
	ENetHost* server;

public:
	NetServer();
	~NetServer();
	void Update();
	void AddClient();
	void RemoveClient();
	void Broadcast();
};

