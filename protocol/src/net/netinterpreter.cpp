#include "types.hpp"
#include "net/netinterpreter.hpp"

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

//    std::cout << "NetInterpreter::operator()" << std::endl;
//    std::cout << "protocol = " << std::dec << (int) protocol << std::endl;

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
    NetDevice const & device = ns.device();
    uint16_t const cSize = device.comAddrSize(),
                   vSize = NetDevice::virtualAddrSize;

    VARPHeader  readingVarp(cSize), writingVarp(cSize);
    type::Byte  byte;

    ns.read(byte, 3);
    readingVarp.version = byte;

    ns.read(byte, 5);
    readingVarp.scale = byte;

    ns.read(readingVarp.scAddrSrc,  cSize);
    ns.read(readingVarp.addrSrc,    vSize);
    ns.read(readingVarp.scAddrDest, cSize);
    ns.read(readingVarp.addrDest,   vSize);

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


