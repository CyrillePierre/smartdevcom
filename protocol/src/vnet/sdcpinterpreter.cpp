#include <iostream>
#include "sdcpinterpreter.hpp"
#include "netstream.hpp"
#include "vipinterpreter.h"

using sdc::net::NetStream;
using namespace sdc::vnet;
using namespace sdc::type;

SDCPInterpreter::SDCPInterpreter(VIPInterpreter const & vip) : _vip(vip)
{
}


void SDCPInterpreter::operator ()(NetStream & ns, const VIPHeader & vhead) {
    Byte id, type;
    ns.read(id);
    ns.read(type, 2);

    switch (id) {
    case ReqID::test:         return test(ns, vhead, type);
    case ReqID::getSensors:   return getSensors(ns, vhead, type);
    case ReqID::getActuators: return getActuators(ns, vhead, type);
    case ReqID::getActions:   return getActions(ns, vhead, type);
    case ReqID::getActionDef: return getActionDef(ns, vhead, type);
    }

    std::cerr << "[ERR] Parsing SDCP: unknown request ID : " << (int)id
              << std::endl;
}


void SDCPInterpreter::buildHeader(sdc::DynamicBitset & db,
                                  Byte                 id,
                                  Byte                 reqType,
                                  Word                 length)
{
    db.push(id,       8);	// Identifiant (sur 8 bits)
    db.push(reqType,  2);	// Type de requête (sur 2 bits)
    db.push(length,  14);	// Longueur des données (sur 14 bits)
}


void SDCPInterpreter::test(NetStream &       ns,
                           VIPHeader const & vhead,
                           Byte              type)
{
    DynamicBitset & db = ns.writingBitset();

    // Construction du début de la trame (VIP)
    _vip.buildHeader(db, ns.device().getVirtualAddr(), vhead.addrSrc);
    buildHeader(db, type, FrameType::response, 0);
}


void SDCPInterpreter::getSensors(NetStream &, VIPHeader const &, Byte) {
}


void SDCPInterpreter::getActuators(NetStream &, VIPHeader const &, Byte) {
}


void SDCPInterpreter::getActions(NetStream &, VIPHeader const &, Byte) {
}


void SDCPInterpreter::getActionDef(NetStream &, VIPHeader const &, Byte) {
}


void SDCPInterpreter::execAction(NetStream &, VIPHeader const &, Byte) {
}


