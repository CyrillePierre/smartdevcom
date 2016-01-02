#include "vipinterpreter.h"
#include "vipheader.h"
#include "types.hpp"

#include <string.h>

using namespace sdc;
using sdc::vnet::VIPInterpreter;

VIPInterpreter::VIPInterpreter()
{

}

/**
 * @brief Cette méthode permet de gérer une trame VIP
 * @param ns : la trame reçue
 */
void VIPInterpreter::operator() (net::NetStream &ns) const
{
    const net::NetDevice &device = ns.device();

    vnet::VIPHeader readingVarp, writingVarp;
    type::Byte  byte;

    ns.read(byte, 3);
    readingVarp.version = byte;

    ns.read(byte, 8);
    readingVarp.ttl = byte;

    if(readingVarp.ttl == 0)
        return;

    ns.read(readingVarp.addrSrc,    VIRTUAL_SIZE);
    ns.read(readingVarp.addrDest,   VIRTUAL_SIZE);

    if(memcmp(readingVarp.addrDest, device.getVirtualAddr(), VIRTUAL_SIZE)  ||
       memcmp(readingVarp.addrDest, net::NetDevice::BROADCAST, VIRTUAL_SIZE))
    {
        //manage SDCP

    }
}
