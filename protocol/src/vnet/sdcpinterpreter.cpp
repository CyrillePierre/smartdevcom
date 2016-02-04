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
                                  Word              size,
                                  Byte              reqType)
{
    DynamicBitset & db = ns.writingBitset();
    net::NetDevice const & nd = ns.device();
    VIPInterpreter::buildHeader(db, nd.getVirtualAddr(), vh.addrSrc, size + 1);
    db.push(id,       6);
    db.push(reqType,  2);
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

    std::cout << "getSensors()" << std::endl;

    buildHeader(ns, vhead, type, sensors.size() * 3 + 1);
    db.push((Byte) sensors.size(), 8);
    for (std::size_t i = 0; i < sensors.size(); ++i) {
        db.push(i, 8);
        db.push(sensors[i]->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::getActuators(NetStream &       ns,
                                   VIPHeader const & vhead,
                                   Byte              type)
{
    DynamicBitset & db        = ns.writingBitset();
    auto            actuators = Device::get().actuators();

    std::cout << "getActuators()" << std::endl;

    buildHeader(ns, vhead, type, actuators.size() * 3 + 1);
    db.push((Byte) actuators.size(), 8);
    for (std::size_t i = 0; i < actuators.size(); ++i) {
        db.push(i, 8);
        db.push(actuators[i]->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::getActions(NetStream &       ns,
                                 VIPHeader const & vhead,
                                 Byte              type)
{
    DynamicBitset & db      = ns.writingBitset();
    auto            actions = Device::get().actions();

    std::cout << "getActions()" << std::endl;

    buildHeader(ns, vhead, type, actions.size() * 3 + 1);
    db.push((Byte) actions.size(), 8);
    for (std::size_t i = 0; i < actions.size(); ++i) {
        db.push(i, 8);
        db.push(actions[i]->type(), 16);
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

    std::cout << "getActionDef()" << std::endl;

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

    std::cout << "getActionDef()" << std::endl;

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


