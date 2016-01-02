#include <iostream>
#include "sdcpinterpreter.hpp"
#include "net/netstream.hpp"

using sdc::vnet::SDCPInterpreter;
using sdc::vnet::ReqID;
using sdc::net::NetStream;
using namespace sdc::type;

SDCPInterpreter::SDCPInterpreter()
{
}

void SDCPInterpreter::operator ()(NetStream &ns) {
    Byte id, type;
    ns.read(id);
    ns.read(type, 2);

    switch (id) {
    case ReqID::test:         return test(ns, type);
    case ReqID::getSensors:   return getSensors(ns, type);
    case ReqID::getActuators: return getActuators(ns, type);
    case ReqID::getActions:   return getActions(ns, type);
    case ReqID::getActionDef: return getActionDef(ns, type);
    }

    std::cerr << "[ERR] Parsing SDCP: unknown request ID : " << (int)id
              << std::endl;
}

void SDCPInterpreter::test(NetStream & ns, type::Byte type) {
}

void SDCPInterpreter::getSensors(sdc::net::NetStream &, Byte) {
}

void SDCPInterpreter::getActuators(sdc::net::NetStream &, Byte) {
}

void SDCPInterpreter::getActions(sdc::net::NetStream &, Byte) {
}

void SDCPInterpreter::getActionDef(sdc::net::NetStream &, Byte) {
}

void SDCPInterpreter::execAction(sdc::net::NetStream &, Byte) {
}
