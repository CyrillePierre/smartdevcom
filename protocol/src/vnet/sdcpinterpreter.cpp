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

void SDCPInterpreter::operator ()(NetStream & ns, const VIPHeader & vhead) {
    Byte id, type;
    ns.read(id, 6);
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
                                  VIPHeader const & vh,
                                  Byte              id,
                                  Byte              reqType)
{
    DynamicBitset & db = ns.writingBitset();
    VIPInterpreter::buildHeader(db, ns.device().getVirtualAddr(), vh.addrSrc);
    db.push(id,       8);	// Identifiant (sur 8 bits)
    db.push(reqType,  2);	// Type de requête (sur 2 bits)
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

    buildHeader(ns, vhead, type);
    db.push((Byte) sensors.size(), 8);
    for (Sensor * sensor : sensors) {
        db.push(sensor->id()  ,  8);
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

    buildHeader(ns, vhead, type);
    db.push((Byte) actuators.size(), 8);
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

    buildHeader(ns, vhead, type);
    db.push((Byte) actions.size(), 8);
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
        buildHeader(ns, vhead, type, 2);
        db.push(actionId, 16);
    }

    ns.flushOut();
}


void SDCPInterpreter::execAction(NetStream &       ns,
                                 VIPHeader const & vhead,
                                 Byte              type)
{
    // Lecture de l'identifiant de l'action
    Word actionId;
    ns.read(actionId, 16);


    Action * a = Device::get().action(actionId);
    if (a) {
        buildHeader(ns, vhead, type, (Byte) a->returnSize());
        (*a)(ns);
    }

    // Sinon on envoie le code d'erreur "action inconnue"
    else {
        buildHeader(ns, vhead, type, 1);
        DynamicBitset & db = ns.writingBitset();
        db.push((Byte) ErrorCode::UNKNOWN, 4);
        db.push(0, 4);
    }

    ns.flushOut();
}


