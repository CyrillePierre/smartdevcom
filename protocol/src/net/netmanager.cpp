

using sdc::net::NetManager;
using sdc::net::NetDevice;
using sdc::net::Addr;

NetDevice & NetManager::operator [](const Addr & addr) throw(UnknownAddr) {
    for (NetDevice & nd : nds)
        if (nd.virtualAddr().accept(addr))
            return nd;
    throw sdc::net::UnknownAddr{addr};
}

