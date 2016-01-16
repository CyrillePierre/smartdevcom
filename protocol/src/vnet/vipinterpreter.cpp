#include "vipinterpreter.h"
#include "netinterpreter.hpp"
#include "sdcpinterpreter.hpp"
#include "vipheader.h"
#include "netstream.hpp"

#include <string.h>

using namespace sdc;
using sdc::vnet::VIPInterpreter;

/**
 * @brief Cette méthode permet de gérer une trame VIP
 * @param ns : la trame reçue
 */
void VIPInterpreter::operator() (net::NetStream &ns)
{
    const net::NetDevice &device = ns.device();

    vnet::VIPHeader header;
    type::Byte  byte;

    ns.read(byte, 3);
    header.version = byte;

    ns.read(byte, 8);
    header.ttl = byte;

    if(header.ttl == 0)
        return;

    ns.read(header.addrSrc,  VIRTUAL_SIZE);
    ns.read(header.addrDest, VIRTUAL_SIZE);

    if(memcmp(header.addrDest, device.getVirtualAddr(), VIRTUAL_SIZE)  ||
       memcmp(header.addrDest, net::NetDevice::BROADCAST, VIRTUAL_SIZE))
    {
        _sdcp(ns, header);
    }
}

void VIPInterpreter::buildHeader(DynamicBitset &    bitset,
                                 const type::Byte * src,
                                 const type::Byte * dest,
                                 type::Byte         ttl)
{
    bitset.push((type::Byte) net::Proto::VIP, 5);	// Protocole sur 5 bits
    bitset.push(VIP_VERSION, 3);		// Version sur 3 bits
    bitset.push(ttl, 8);				// Durée de vie sur 8 bits
    bitset.push(src, 3);				// Adresse source sur 3 octets
    bitset.push(dest, 3);				// Adresse de destination sur 3 octets
}






