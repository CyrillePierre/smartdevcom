#ifndef ROUTINGTABLE_HPP
#define ROUTINGTABLE_HPP

#include <vector>
#include <initializer_list>
#include <stdexcept>
#include "net/netdevice.hpp"

namespace sdc {
namespace net {

struct UnknownAddr : public std::runtime_error {
    UnknownAddr(Addr const & addr)
        : std::runtime_error{"Unknown address " + addr.str()} {}
};

/**
 * Table de routage. Attention l'ordre d'insertion est inverse à l'odre de
 * lecture. Cela signifie que la première ligne de la table doit correspondre au
 * NetDevice par défaut.
 */
struct RoutingTable {
    using Routes        = std::vector<NetDevice *>;
    using SizeType      = Routes::size_type;
    using ConstIterator = Routes::const_iterator;
    using Iterator      = Routes::iterator;

private:
    Routes _routes;

public:
    RoutingTable() {}
    RoutingTable(std::initializer_list<NetDevice *> list) : _routes{list} {}
    RoutingTable(RoutingTable const &) = delete;
    RoutingTable(RoutingTable &&) = default;

    /** Ajout d'une nouvelle route */
    RoutingTable & operator +=(NetDevice * nd)
    { _routes.push_back(nd); return *this; }

    /** Récupération d'un support à partir d'une adresse */
    NetDevice & operator[](Addr const &);

    SizeType      size()  const noexcept { return _routes.size(); }
    Iterator      begin()       noexcept { return _routes.begin(); }
    Iterator      end()         noexcept { return _routes.end(); }
    ConstIterator begin() const noexcept { return _routes.begin(); }
    ConstIterator end()   const noexcept { return _routes.end(); }
    bool          empty() const noexcept { return _routes.empty(); }
};

} // net
} // sdc

#endif // ROUTINGTABLE_HPP
