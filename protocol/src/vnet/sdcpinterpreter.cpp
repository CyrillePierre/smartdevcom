#include <iostream>
#include "sdcpinterpreter.hpp"
#include "vipinterpreter.h"
#include "device.hpp"
#include "sensor.hpp"
#include "actuator.hpp"
#include "action.hpp"
#include "view/view.hpp"
#include "view/list.hpp"

using sdc::net::NetStream;
using namespace sdc::vnet;
using namespace sdc::type;

void SDCPInterpreter::operator ()(NetStream & ns, const VIPHeader & vhead) {
    Byte id, type;
    ns.read(id, 6);
    ns.read(type, 2);

    if (type == FrameType::response) {
        switch (id) {
        case ReqID::test:         return rpTest(ns, vhead, id);
        case ReqID::getSensors:   return rpGetSensors(ns, vhead, id);
        case ReqID::getActuators: return rpGetActuators(ns, vhead, id);
        case ReqID::getActions:   return rpGetActions(ns, vhead, id);
        case ReqID::getActionDef: return rpGetActionDef(ns, vhead, id);
        case ReqID::execAction:   return rpExecAction(ns, vhead, id);
        }
    }

    else if (type == FrameType::request) {
        switch (id) {
        case ReqID::test:         return _reqHandler(view::View{});
        case ReqID::getSensors:
        case ReqID::getActuators:
        case ReqID::getActions:   return _reqHandler(view::List{ns});
        case ReqID::getActionDef: return _reqHandler(view::View{});
        case ReqID::execAction:   return _reqHandler(view::View{});
        }
    }

    else {
        std::cerr << "[ERR] Parsing SDCP: unknown type : " << (int)type
                  << std::endl;
        return;
    }

    std::cerr << "[ERR] Parsing SDCP: unknown request ID : " << (int)id
              << std::endl;
}

void SDCPInterpreter::buildHeader(NetStream &  ns,
                                  Byte const * addr,
                                  Byte         id,
                                  Word         size,
                                  Byte         reqType)
{
    DynamicBitset & db = ns.writingBitset();
    net::NetDevice const & nd = ns.device();
    VIPInterpreter::buildHeader(db, nd.virtualAddr().vals, addr, size + 1);
    db.push(id,      6);
    db.push(reqType, 2);
}


void SDCPInterpreter::rpTest(NetStream &       ns,
                             VIPHeader const & vhead,
                             Byte              id)
{
    buildHeader(ns, vhead.addrSrc, id, 0);
    ns.flushOut();
}


void SDCPInterpreter::rpGetSensors(NetStream &       ns,
                                   VIPHeader const & vhead,
                                   Byte              id)
{
    DynamicBitset & db      = ns.writingBitset();
    auto            sensors = Device::get().sensors();

    buildHeader(ns, vhead.addrSrc, id, sensors.size() * 3 + 1);
    db.push((Byte) sensors.size(), 8);
    for (std::size_t i = 0; i < sensors.size(); ++i) {
        db.push(i, 8);
        db.push(sensors[i]->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::rpGetActuators(NetStream &       ns,
                                     VIPHeader const & vhead,
                                     Byte              id)
{
    DynamicBitset & db        = ns.writingBitset();
    auto            actuators = Device::get().actuators();

    buildHeader(ns, vhead.addrSrc, id, actuators.size() * 3 + 1);
    db.push((Byte) actuators.size(), 8);
    for (std::size_t i = 0; i < actuators.size(); ++i) {
        db.push(i, 8);
        db.push(actuators[i]->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::rpGetActions(NetStream &       ns,
                                   VIPHeader const & vhead,
                                   Byte              id)
{
    DynamicBitset & db      = ns.writingBitset();
    auto            actions = Device::get().actions();

    buildHeader(ns, vhead.addrSrc, id, actions.size() * 3 + 1);
    db.push((Byte) actions.size(), 8);
    for (std::size_t i = 0; i < actions.size(); ++i) {
        db.push(i, 8);
        db.push(actions[i]->type(), 16);
    }
    ns.flushOut();
}


void SDCPInterpreter::rpGetActionDef(NetStream &       ns,
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
        buildHeader(ns, vhead.addrSrc, id, (Byte) a->prototypeSize() + 1);
        a->pushPrototype(db);
    }

    // Sinon on envoie que l'identifiant
    else {
        buildHeader(ns, vhead.addrSrc, id, 2);
        db.push(actionId, 16);
    }

    ns.flushOut();
}


void SDCPInterpreter::rpExecAction(NetStream &       ns,
                                   VIPHeader const & vhead,
                                   Byte              id)
{
    // Lecture de l'identifiant de l'action
    Word actionId;
    ns.read(actionId, 16);

    Action * a = Device::get().action(actionId);
    if (a) {
        buildHeader(ns, vhead.addrSrc, id, (Byte) a->returnSize());
        (*a)(ns);
    }

    // Sinon on envoie le code d'erreur "action inconnue"
    else {
        buildHeader(ns, vhead.addrSrc, id, 1);
        DynamicBitset & db = ns.writingBitset();
        db.push((Byte) ErrorCode::UNKNOWN, 4);
        db.push(0, 4);
    }

    ns.flushOut();
}


