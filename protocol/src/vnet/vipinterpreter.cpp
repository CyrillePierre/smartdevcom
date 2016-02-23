#include "vipinterpreter.h"
#include "netinterpreter.hpp"
#include "sdcpinterpreter.hpp"

#ifndef DEBUG
#define DBG if (0)
#endif

using namespace sdc;
using sdc::vnet::VIPInterpreter;

/**
 * @brief Cette méthode permet de gérer une trame VIP
 * @param ns : la trame reçue
 */
void VIPInterpreter::operator()(net::NetStream &ns)
{
    const net::NetDevice &device = ns.device();

    DBG { std::cout << "VIPInterpreter::operator()" << std::endl; }

    vnet::VIPHeader header;
    type::Byte  byte;

    ns.read(byte, 3);
    header.version = byte;

    DBG { std::cout << "vip.version = " << (int) header.version << std::endl; }

    ns.read(byte, 8);
    header.ttl = byte;

    DBG { std::cout << "vip.ttl     = " << (int) header.ttl << std::endl; }

    if(header.ttl == 0)
        return;

    ns.read(header.addrSrc,  VIRTUAL_SIZE);

    DBG {
        int i;
        std::cout << "vip.addrSrc = " << std::hex;
        for (i = 0; i < VIRTUAL_SIZE - 1; ++i)
            std::cout << (int) header.addrSrc[i] << ":";
        std::cout << (int) header.addrSrc[i] << std::endl;
    }

    ns.read(header.addrDest, VIRTUAL_SIZE);

    DBG {
        int i;
        std::cout << "vip.addrSrc = ";
        for (i = 0; i < VIRTUAL_SIZE - 1; ++i)
            std::cout << (int) header.addrDest[i] << ":";
        std::cout << (int) header.addrDest[i] << std::endl;
    }

    ns.read(header.length, 16);
    DBG { std::cout << "vip.length  = " << (int) header.length << std::endl; }

    if(memcmp(header.addrDest, device.virtualAddr().vals, VIRTUAL_SIZE)  ||
       memcmp(header.addrDest, net::NetDevice::BROADCAST, VIRTUAL_SIZE))
    {
        _sdcp(ns, header);
    }
}

void VIPInterpreter::buildHeader(DynamicBitset &    bitset,
                                 const type::Byte * src,
                                 const type::Byte * dest,
                                 type::Word         length,
                                 type::Byte         ttl)
{
    bitset.push((type::Byte) net::Proto::VIP, 5);	// Protocole sur 5 bits
    bitset.push(VIP_VERSION, 3);		// Version sur 3 bits
    bitset.push(ttl, 8);				// Durée de vie sur 8 bits
    bitset.push(src, 3);				// Adresse source sur 3 octets
    bitset.push(dest, 3);				// Adresse de destination sur 3 octets
    bitset.push(length, 16);
}






