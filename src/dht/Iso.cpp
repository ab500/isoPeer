// Iso.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <list>
#include <memory>
#include <ctype.h>

#include "Message.h"

namespace Iso { namespace Dht {
    struct NodeAddress {
        uint32_t IpAddress;
        uint16_t Port;
    };

    class Node {

    };

    struct PersistedDhtConfiguration {

    };

    class Storage {
        Storage(std::wstring folderLocation);
    };

    class Network {
        void SendMessage();
    };



    class Server {
    public:
        Server(std::vector<NodeAddress> bootstrapNodes, Storage storage, Network network);
    private:
        std::vector<std::list<Node>> m_buckets;
    };

} }


int _tmain(int argc, _TCHAR* argv[])
{
    std::cout << "Hello world";

    int result = getchar();
    return 0;
}

