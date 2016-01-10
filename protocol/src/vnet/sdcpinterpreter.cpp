#include <iostream>
#include "sdcpinterpreter.hpp"
#include "netstream.hpp"
#include "vipinterpreter.h"
#include "device.hpp"
#include "sensor.hpp"
#include "actuator.hpp"
#include "action.hpp"

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


void SDCPInterpreter::buildHeader(NetStream &       ns,
                                  VIPHeader const & vhead,
                                  Byte              id,
                                  Word              length,
                                  Byte              reqType)
{
    DynamicBitset & db = ns.writingBitset();
    _vip.buildHeader(db, ns.device().getVirtualAddr(), vhead.addrSrc);
    db.push(id,       8);	// Identifiant (sur 8 bits)
    db.push(reqType,  2);	// Type de requête (sur 2 bits)
    db.push(length,  14);	// Longueur des données (sur 14 bits)
}


void SDCPInterpreter::test(NetStream &       ns,
                           VIPHeader const & vhead,
                           Byte              type)
{
    buildHeader(ns, vhead, type, 0);
    ns.flushOut();
}


void SDCPInterpreter::getSensors(NetStream &       ns,
                                 VIPHeader const & vhead,
                                 Byte              type)
{
    DynamicBitset & db      = ns.writingBitset();
    auto            sensors = Device::get().sensors();

    buildHeader(ns, vhead, type, (Byte) sensors.size());
    for (Sensor * sensor : sensors) {
        db.push(sensor->id(),    8);
        db.push(sensor->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::getActuators(NetStream &       ns,
                                   VIPHeader const & vhead,
                                   Byte              type)
{
    DynamicBitset & db        = ns.writingBitset();
    auto            actuators = Device::get().actuators();

    buildHeader(ns, vhead, type, (Byte) actuators.size());
    for (Actuator * actuator : actuators){
        db.push(actuator->id(),    8);
        db.push(actuator->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::getActions(NetStream &       ns,
                                 VIPHeader const & vhead,
                                 Byte              type)
{
    DynamicBitset & db      = ns.writingBitset();
    auto            actions = Device::get().actions();

    buildHeader(ns, vhead, type, (Byte) actions.size());
    for (Action * action : actions) {
        db.push(action->id(),   16);
        db.push(action->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::getActionDef(NetStream &       ns,
                                   VIPHeader const & vhead,
                                   Byte              type)
{
    // Lecture de l'identifiant de l'action
    Word actionId;
    ns.read(actionId, 16);


    DynamicBitset & db = ns.writingBitset();
    Action * a = Device::get().action(actionId);
    // Si l'action existe on ajoute son prototype au bitset
    if (a) {
        buildHeader(ns, vhead, type, (Byte) a->prototypeSize());
        a->pushPrototype(db);
    }

    // Sinon on envoie que l'identifiant
    else {
        db.push(actionId, 16);
        buildHeader(ns, vhead, type, 2);
    }

    ns.flushOut();
}


void SDCPInterpreter::execAction(NetStream &, VIPHeader const &, Byte) {
}


