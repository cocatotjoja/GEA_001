#include "config.h"
#include "NetClient.h"


ActionResult NetClient::Start(std::string IP)
{
	client = enet_host_create(NULL, 1, 1, 0, 0);

	if (client == NULL)
	{
		printf( "ENet failed to create a client host!\n");
		return ACTION_FAILED;
	}
	//enet_address_set_host(&address, IP.c_str());
	enet_address_set_host(&address, "192.168.0.192");
	address.port = 7777; 

	peer = enet_host_connect(client, &address, 1, 0);
	if (peer == NULL)
	{
		printf("ENet couldn't find any peer to connect with!\n");
		return ACTION_FAILED;
	}

	if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		printf("Connection to server succeeded!\n");

		if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_RECEIVE)
		{
			// Handle recived packet
			ClientStart* packet = (ClientStart*)event.packet->data;
			if (packet->packetType == CLIENT_START)
		}
	}
	else
	{
		enet_peer_reset(peer);
		printf("Connection to server failed!\n");
		return ACTION_FAILED;
	}

	printf("Succeded to set up ENet services\n");
	return ACTION_SUCCEEDED;
}

ActionResult NetClient::End()
{
	enet_peer_disconnect(peer, 0);
	while (enet_host_service(client, &event, 3000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			enet_packet_destroy(event.packet);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			std::cout << "Disconnected from server!" << std::endl;
			break;
		}
	}

	return ACTION_SUCCEEDED;
}

void NetClient::Update()
{
	while (enet_host_service(client, &event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			printf("A packet of length %u containing %s was received from %x : %u on channel %u.\n",
				event.packet ->dataLength,
				event.packet ->data,
				event.peer ->data,
				event.channelID);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			// Deal with what happens if server goes down
			break;
		}
	}
}