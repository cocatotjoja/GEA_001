#include "config.h"
#include "NetServer.h"


ActionResult NetServer::Start(std::string IP)
{
	address.host = ENET_HOST_ANY;
	address.port = 7777;
	server = enet_host_create(&address, 32, 1, 0, 0);

	if (server == NULL)
	{
		printf("ENet failed to create a server host!\n");
		return ACTION_FAILED;
	}

	printf("ENet succeeded to create a server host!\n");
	return ACTION_SUCCEEDED;
}

ActionResult NetServer::End()
{
	enet_host_destroy(server);
	return ACTION_SUCCEEDED;
}

void NetServer::Update()
{
	while (enet_host_service(server, &event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			printf("A new client has connected from %x:%u.\n",
				event.peer->address.host,
				event.peer->address.port);
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			printf("A packet of length %u containing %s was received from %x : %u on channel %u.\n",
				event.packet->dataLength,
				event.packet->data,
				event.peer->data,
				event.channelID);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			printf("%x:%u has disconnected.?n",
				event.peer->address.host,
				event.peer->address.port);
			break;
		}
	}
	//std::cout << "ENet update ended" << std::endl;
}

void NetServer::AddClient()
{
	// TO DO
}

void NetServer::RemoveClient()
{
	// TO DO
}

void NetServer::Broadcast()
{
	// TO DO
}
