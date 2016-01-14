#include "net/netinterpreter.hpp"
#include "net/varpheader.hpp"
#include "types.hpp"
#include "net/netdevice.hpp"

#include <string.h>
#include <iostream>

using namespace sdc::net;
namespace type = sdc::type;

/**
 * @brief Cette méthode permet de traiter la trame
 * @param ns : la trame
 */
void NetInterpreter::operator ()(NetStream &ns) {
    // Lecture du protocole (5 bits)
    type::Byte protocol;
    ns.read(protocol, 5);

    switch (protocol) {
        case Proto::VIP:  _vip(ns);       break;
        case Proto::VARP: manageVARP(ns); break;
    }
}

/**
 * @brief Cette méthode permer de traiter les paquets de type VARP
 * @param ns : la trame reçue
 */
void NetInterpreter::manageVARP(NetStream &ns) const {
    uint16_t size = ns.comSize();
    const NetDevice &device = ns.device();

    VARPHeader  readingVarp(size), writingVarp(size);
    type::Byte  byte;

    ns.read(byte, 3);
    readingVarp.version = byte;

    ns.read(byte, 5);
    readingVarp.scale = byte;

    ns.read(readingVarp.scAddrSrc,  size);
    ns.read(readingVarp.addrSrc,    VIRTUAL_SIZE);
    ns.read(readingVarp.scAddrDest, size);
    ns.read(readingVarp.addrDest,   VIRTUAL_SIZE);

    /* Si l'adresse de destination dans le support ou dans le réseau virtuel,
     * c'est moi ou si c'est du broadcast, et que c'est une demande d'adresse */
    if((memcmp(readingVarp.scAddrDest, device.getComAddr(), readingVarp.scale)  ||
        memcmp(readingVarp.addrDest, device.getVirtualAddr(), VIRTUAL_SIZE)     ||
        memcmp(readingVarp.scAddrDest, NetDevice::BROADCAST, readingVarp.scale) ||
        memcmp(readingVarp.addrDest, NetDevice::BROADCAST, VIRTUAL_SIZE))       &&
       (readingVarp.op == 0x01 || readingVarp.op == 0x00))
    {
        writingVarp.version = readingVarp.version;
        writingVarp.scale   = readingVarp.scale;
        writingVarp.op      = 0x02;

        memcpy((char*) writingVarp.scAddrSrc, (char*) device.getComAddr(), size);
        memcpy((char*) writingVarp.addrSrc, (char*) device.getVirtualAddr(), VIRTUAL_SIZE);
        memcpy((char*) writingVarp.scAddrDest, (char*) readingVarp.scAddrSrc, size);
        memcpy((char*) writingVarp.addrDest, (char*) readingVarp.addrSrc, VIRTUAL_SIZE);

        sendVARP(ns, writingVarp);
    }
}

/**
 * @brief Cette méthode permet d'envoyer un header VARP
 * @param ns : le stream sur lequel envoyer les données
 * @param header : la trame à envoyer
 */
void NetInterpreter::sendVARP(NetStream &ns, const VARPHeader &header) const
{
    DynamicBitset dbs = ns.writingBitset();
    uint16_t size = ns.comSize();

    dbs.push(header.version);
    dbs.push(header.scale);
    dbs.push(header.op);

    std::cout << dbs.data();

    dbs.push(header.scAddrSrc, size);
    dbs.push(header.addrSrc, VIRTUAL_SIZE);
    dbs.push(header.scAddrDest, size);
    dbs.push(header.addrDest, VIRTUAL_SIZE);

    ns.flushOut();
}


