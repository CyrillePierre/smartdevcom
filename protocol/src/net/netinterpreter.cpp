#include "types.hpp"
#include "net/netinterpreter.hpp"
#include "net/varpheader.hpp"
#include "net/netdevice.hpp"
#include "addr.hpp"

#include <string.h>
#include <iostream>
>>>>>>> 7613bd5491bcf010b262caacc58b13d7d4a7bf68

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

    ns.read(header.scAddrSrc,  header.scale);
    ns.read(header.addrSrc,    vSize);
    ns.read(header.scAddrDest, header.scale);
    ns.read(header.addrDest,   vSize);

    Addr scAddrDest{header.scAddrDest, header.scale},
         addrDest{header.addrDest, vSize};

    if ((header.op == COM_ADDR_REQUEST && nd.virtualAddr().accept(addrDest))
         || (header.op == VIP_ADDR_REQUEST && nd.comAddr().accept(scAddrDest)))
        sendVARP(ns, header);
}

/**
 * @brief Cette méthode permet d'envoyer un header VARP
 * @param ns : le stream sur lequel envoyer les données
 * @param header : la trame reçue à modifier pour l'envoi
 */
void NetInterpreter::sendVARP(NetStream &ns, const VARPHeader &header) const
{
    DynamicBitset & dbs = ns.writingBitset();

    dbs.clear();
    dbs.push((type::Byte) Proto::VARP, 5);
    dbs.push(header.version,           3);
    dbs.push((type::Byte) RESPONSE,    3);
    dbs.push(header.scale,             5);

    NetDevice const & nd = ns.device();
    Addr const & comAddr = nd.comAddr(), addr = nd.virtualAddr();

    dbs.push(comAddr.vals, comAddr.size);
    dbs.push(addr.vals, addr.size);
    dbs.push(header.scAddrSrc, comAddr.size);
    dbs.push(header.addrSrc, addr.size);

    ns.flushOut();
}


