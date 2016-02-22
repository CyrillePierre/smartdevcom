#include "types.hpp"
#include "net/netinterpreter.hpp"
#include "net/varpheader.hpp"
#include "net/netdevice.hpp"
#include "addr.hpp"

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

void NetInterpreter::manageVARP(NetStream & ns) const {
    NetDevice const & nd = ns.device();
    std::size_t const cSize = nd.comAddrSize(),
                      vSize = NetDevice::virtualAddrSize;
    VARPHeader header{cSize};

    header.version = ns.read<type::Byte>(3);
    header.op      = ns.read<type::Byte>(3);
    header.scale   = ns.read<type::Byte>(5);

    ns.read(header.scAddrSrc,  cSize);
    ns.read(header.addrSrc,    vSize);
    ns.read(header.scAddrDest, cSize);
    ns.read(header.addrDest,   vSize);

    {
        std::size_t i;
        std::cout << std::hex;
        std::cout << "comAddrSrc = ";
        for (i = 0; i < cSize - 1; ++i)
            std::cout << (int) header.scAddrSrc[i] << ":";
        std::cout << (int) header.scAddrSrc[i] << std::endl;
    }

    Addr scAddrDest{header.scAddrDest, cSize},
         addrDest{header.addrDest, vSize};
//    if (header.op == COM_ADDR_REQUEST && )

}

#if 0
/**
 * @brief Cette méthode permer de traiter les paquets de type VARP
 * @param ns : la trame reçue
 */
void NetInterpreter::manageVARP(NetStream &ns) const {
    NetDevice const & device = ns.device();
    uint16_t const cSize = device.comAddrSize(),
                   vSize = NetDevice::virtualAddrSize;

    VARPHeader  readingVarp(cSize), writingVarp(cSize);
    type::Byte  byte;

    ns.read(byte, 3);
    readingVarp.version = byte;

    ns.read(byte, 3);
    readingVarp.op = byte;

    ns.read(byte, 5);
    readingVarp.scale = byte;

    ns.read(readingVarp.scAddrSrc,  cSize);
    ns.read(readingVarp.addrSrc,    vSize);
    ns.read(readingVarp.scAddrDest, cSize);
    ns.read(readingVarp.addrDest,   vSize);

    {
        int i;
        std::cout << std::hex;
        std::cout << "comAddrSrc = ";
        for (i = 0; i < cSize - 1; ++i)
            std::cout << (int) readingVarp.scAddrSrc[i] << ":";
        std::cout << (int) readingVarp.scAddrSrc[i] << std::endl;
    }

    /* Si l'adresse de destination dans le support ou dans le réseau virtuel,
     * c'est moi ou si c'est du broadcast, et que c'est une demande d'adresse */
    if((memcmp(readingVarp.scAddrDest, device.getComAddr(), readingVarp.scale)  ||
        memcmp(readingVarp.addrDest, device.getVirtualAddr(), vSize)     ||
        memcmp(readingVarp.scAddrDest, NetDevice::BROADCAST, readingVarp.scale) ||
        memcmp(readingVarp.addrDest, NetDevice::BROADCAST, vSize))       &&
       (readingVarp.op == 0x01 || readingVarp.op == 0x00))
    {
        writingVarp.version = readingVarp.version;
        writingVarp.scale   = readingVarp.scale;
        writingVarp.op      = 0x02;

        memcpy((char*) writingVarp.scAddrSrc, (char*) device.getComAddr(), cSize);
        memcpy((char*) writingVarp.addrSrc, (char*) device.getVirtualAddr(), vSize);
        memcpy((char*) writingVarp.scAddrDest, (char*) readingVarp.scAddrSrc, cSize);
        memcpy((char*) writingVarp.addrDest, (char*) readingVarp.addrSrc, vSize);

        sendVARP(ns, writingVarp);
    }
}

#endif

/**
 * @brief Cette méthode permet d'envoyer un header VARP
 * @param ns : le stream sur lequel envoyer les données
 * @param header : la trame à envoyer
 */
void NetInterpreter::sendVARP(NetStream &ns, const VARPHeader &header) const
{
    DynamicBitset dbs = ns.writingBitset();
    uint16_t const cSize = ns.device().comAddrSize(),
                   vSize = NetDevice::virtualAddrSize;

    dbs.push(header.version);
    dbs.push(header.scale);
    dbs.push(header.op);

    std::cout << dbs.data();

    dbs.push(header.scAddrSrc,  cSize);
    dbs.push(header.addrSrc,    vSize);
    dbs.push(header.scAddrDest, cSize);
    dbs.push(header.addrDest,   vSize);

    ns.flushOut();
}


