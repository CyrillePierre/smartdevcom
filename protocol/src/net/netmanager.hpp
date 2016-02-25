#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include "net/netinterpreter.hpp"
#include "vnet/sdcpinterpreter.hpp"
#include "vnet/vipinterpreter.h"
#include "net/routingtable.hpp"

namespace sdc {
namespace net {

class NetManager {
    vnet::SDCPInterpreter _sdcp;
    vnet::VIPInterpreter  _vip;
    NetInterpreter        _net;
    RoutingTable		  _rtable;

public:
    NetManager() : _vip{_sdcp}, _net{_rtable, _vip} {}

    NetInterpreter & net() { return _net; }
    RoutingTable & rtable() { return _rtable; }
};

} // net
} // sdc

#endif // NETMANAGER_HPP
