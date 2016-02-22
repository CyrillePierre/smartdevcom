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
    case ReqID::test:         return test(ns, vhead, id);
    case ReqID::getSensors:   return getSensors(ns, vhead, id);
    case ReqID::getActuators: return getActuators(ns, vhead, id);
    case ReqID::getActions:   return getActions(ns, vhead, id);
    case ReqID::getActionDef: return getActionDef(ns, vhead, id);
    case ReqID::execAction:   return execAction(ns, vhead, id);
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
    VIPInterpreter::buildHeader(db, nd.virtualAddr().vals, vh.addrSrc, size + 1);
    db.push(id,       6);
    db.push(reqType,  2);
}


void SDCPInterpreter::test(NetStream &       ns,
                           VIPHeader const & vhead,
                           Byte              id)
{
    buildHeader(ns, vhead, id, 0);
    ns.flushOut();
}


void SDCPInterpreter::getSensors(NetStream &       ns,
                                 VIPHeader const & vhead,
                                 Byte              id)
{
    DynamicBitset & db      = ns.writingBitset();
    auto            sensors = Device::get().sensors();

    buildHeader(ns, vhead, id, sensors.size() * 3 + 1);
    db.push((Byte) sensors.size(), 8);
    for (std::size_t i = 0; i < sensors.size(); ++i) {
        db.push(i, 8);
        db.push(sensors[i]->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::getActuators(NetStream &       ns,
                                   VIPHeader const & vhead,
                                   Byte              id)
{
    DynamicBitset & db        = ns.writingBitset();
    auto            actuators = Device::get().actuators();

    buildHeader(ns, vhead, id, actuators.size() * 3 + 1);
    db.push((Byte) actuators.size(), 8);
    for (std::size_t i = 0; i < actuators.size(); ++i) {
        db.push(i, 8);
        db.push(actuators[i]->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::getActions(NetStream &       ns,
                                 VIPHeader const & vhead,
                                 Byte              id)
{
    DynamicBitset & db      = ns.writingBitset();
    auto            actions = Device::get().actions();

    buildHeader(ns, vhead, id, actions.size() * 3 + 1);
    db.push((Byte) actions.size(), 8);
    for (std::size_t i = 0; i < actions.size(); ++i) {
        db.push(i, 8);
        db.push(actions[i]->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::getActionDef(NetStream &       ns,
                                   VIPHeader const & vhead,
                                   Byte              id)
{
    // Lecture de l'identifiant de l'action
    Word actionId;
    ns.read(actionId, 16);

    DynamicBitset & db = ns.writingBitset();
    Action * a = Device::get().action(actionId);

    std::cout << "id = " << actionId << std::endl;

    // Si l'action existe on ajoute son prototype au bitset
    if (a) {
        std::cout << "protoSize = " << a->prototypeSize() << std::endl;
        buildHeader(ns, vhead, id, (Byte) a->prototypeSize() + 1);
        a->pushPrototype(db);
    }

    // Sinon on envoie que l'identifiant
    else {
        buildHeader(ns, vhead, id, 2);
        db.push(actionId, 16);
    }

    ns.flushOut();
}


void SDCPInterpreter::execAction(NetStream &       ns,
                                 VIPHeader const & vhead,
                                 Byte              id)
{
    // Lecture de l'identifiant de l'action
    Word actionId;
    ns.read(actionId, 16);

    Action * a = Device::get().action(actionId);
    if (a) {
        buildHeader(ns, vhead, id, (Byte) a->returnSize());
        (*a)(ns);
    }

    // Sinon on envoie le code d'erreur "action inconnue"
    else {
        buildHeader(ns, vhead, id, 1);
        DynamicBitset & db = ns.writingBitset();
        db.push((Byte) ErrorCode::UNKNOWN, 4);
        db.push(0, 4);
    }

    ns.flushOut();
}


