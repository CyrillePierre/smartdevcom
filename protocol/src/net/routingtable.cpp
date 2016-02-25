#include "routingtable.hpp"

using sdc::net::NetDevice;
using sdc::net::RoutingTable;
using sdc::net::Addr;

NetDevice & RoutingTable::operator [](const Addr & addr) {
    for (NetDevice * nd : _routes)
        if (addr.isInNet(nd->netAddr()))
            return *nd;
    throw sdc::net::UnknownAddr{addr};
}
