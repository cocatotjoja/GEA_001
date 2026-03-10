#include "config.h"
#include "NetClient.h"

NetClient::NetClient()
{
	client = enet_host_create(NULL, 1, 1, 0, 0);

	if (client == NULL)
	{
		std::cout << "ENet failed to create a client host!" << std::endl;
		// ASK FREDRIK
		// return EXIT_FAILURE;
	}
	enet_address_set_host(&address, "127.0.0.1");
	address.port = 7777; //ASK FREDRIK / Check presentation

	peer = enet_host_connect(client, &address, 1, 0);
	if (peer == NULL)
	{
		std::cout << "ENet couldn't find any peer to connect with!" << std::endl;
		// ASK FREDRIK
		// return EXIT_FAILURE;
	}

	if (enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
	{
		std::cout << "Connection to server succeeded!" << std::endl;
	}
	else
	{
		enet_peer_reset(peer);
		std::cout << "Connection to server failed!" << std::endl;
		// ASK FREDRIK
		// return EXIT_SUCCESS;
	}
}

void NetClient::Update()
{
	while (enet_host_service(client, &event, 1000) > 0)
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			// ASK FREDRIK
			std::cout << "A packet of length %u containing %s was received from %x : %u on channel %u.",
				event.packet ->dataLength,
				event.packet ->data,
				event.peer ->data,
				event.channelID;
			break;
		}
	}
}