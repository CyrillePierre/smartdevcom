#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include <stdexcept>
#include <vector>
#include "net/netinterpreter.hpp"
#include "vnet/sdcpinterpreter.hpp"
#include "vnet/vipinterpreter.h"

namespace sdc {
namespace net {

struct UnknownAddr : public std::runtime_error {
    UnknownAddr(Addr const & addr)
        : std::runtime_error{"Unknown address " + addr.str()} {}
};

struct NetManager {
    using NetDevices = std::vector<NetDevice>;

private:
    vnet::SDCPInterpreter _sdcp;
    vnet::VIPInterpreter  _vip;
    NetInterpreter        _net;

protected:
    NetDevices            nds;

public:
    NetManager() : _vip{_sdcp}, _net{*this, _vip} {}

    /**
     * Récupération du NetDevice qui matche le mieux avec l'adresse passé
     * en paramètre
     * @param addr l'adresse permettant de déterminer quel NetDevice récupérer
     * @return le NetDevice correspondant
     */
    NetDevice & operator [](Addr const &) throw(UnknownAddr);

    /** @return l'instance de NetInterpreter */
    NetInterpreter & net() { return _net; }
};

} // net
} // sdc

#endif // NETMANAGER_HPP
