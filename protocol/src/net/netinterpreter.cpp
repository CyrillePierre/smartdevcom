#include "types.hpp"
#include "vnet/vipinterpreter.h"
#include "net/netinterpreter.hpp"
#include "net/routingtable.hpp"
#include "net/varpheader.hpp"
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

void NetInterpreter::manageVARP(NetStream & ns) const {
    NetDevice const & nd = ns.device();
    VARPHeader header{nd.comAddrSize()};

    header.version = ns.read<type::Byte>(3);
    header.op      = ns.read<type::Byte>(3);
    header.scale   = ns.read<type::Byte>(5);

    ns.read(header.scAddrSrc,  header.scale);
    ns.read(header.addrSrc,    NetDevice::virtualAddrSize);
    ns.read(header.scAddrDest, header.scale);
    ns.read(header.addrDest,   NetDevice::virtualAddrSize);

    Addr scAddrDest{header.scAddrDest, header.scale},
         addrDest  {header.addrDest, NetDevice::virtualAddrSize};

    if ((header.op == COM_ADDR_REQ && nd.virtualAddr().accept(addrDest))
         || (header.op == VIP_ADDR_REQ && nd.comAddr().accept(scAddrDest)))
        sendVARPResponse(ns, header);

    // Appel de l'handler s'il y en a un
    if (header.op == RESPONSE && _reqHandler)
        _reqHandler(Addr{header.scAddrSrc, header.scale},
                    Addr{header.addrSrc,   NetDevice::virtualAddrSize});
}

/**
 * @brief Cette méthode permet d'envoyer un header VARP
 * @param ns : le stream sur lequel envoyer les données
 * @param header : la trame reçue à modifier pour l'envoi
 */
void NetInterpreter::sendVARPResponse(NetStream &ns,
                                      const VARPHeader &header) const
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

void NetInterpreter::findTargets(const Addr & addr, bool isVIPReq) {
    try {
        if (!isVIPReq)
            sendVARPRequest(_rtable[addr], addr, isVIPReq);
        else
            for (NetDevice * route : _rtable)
                sendVARPRequest(*route, addr, isVIPReq);
    }
    catch (UnknownAddr & e) {
        std::cout << "Exception : " << e.what() << std::endl;
    }
}

void NetInterpreter::sendVARPRequest(NetDevice &  nd,
                                     const Addr & addr,
                                     bool         isVIPReq)
{
    NetStream ns{nd};
    DynamicBitset & db = ns.writingBitset();

    std::cout << "NetInterpreter::sendVARPRequest()" << std::endl;
    std::cout << "isVIPReq ? : " << isVIPReq << std::endl;

    db.push((type::Byte) Proto::VARP, 5);
    db.push(NetInterpreter::VARP_VERSION, 3);
    db.push((type::Byte)(isVIPReq ? VIP_ADDR_REQ : COM_ADDR_REQ), 3);
    db.push(nd.comAddrSize(), 5);

    Addr const & srcComAddr = nd.comAddr();
    Addr const & srcAddr    = nd.virtualAddr();

    std::cout << "srcComAddr = " << srcComAddr.str() << std::endl;
    std::cout << "srcAddr = " << srcAddr.str() << std::endl;
    std::cout << "addr = " << addr.str() << std::endl;

    db.push(srcComAddr.vals, srcComAddr.size);
    db.push(srcAddr.vals, srcAddr.size);
    if (isVIPReq) {
        db.push(addr.vals, addr.size);
        db.push(NetDevice::BROADCAST, NetDevice::virtualAddrSize);
    }
    else {
        db.push(NetDevice::BROADCAST, nd.comAddrSize());
        db.push(addr.vals, addr.size);
    }

    std::cout << std::hex;
    for (auto const & byte : db) std::cout << (int) byte << ' ';
    std::cout << std::dec << std::endl;

    ns.flushOut();
}




