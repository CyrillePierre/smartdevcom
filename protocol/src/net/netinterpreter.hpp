#ifndef NETINTERPRETER_HPP
#define NETINTERPRETER_HPP

#include "net/netstream.hpp"

namespace sdc {
namespace net {

enum class Proto {
    VIP  = 0,	// virtual IP
    VARP = 1	// virtual ARP
};

/**
 * Cette classe s'occupe de l'interpretation des paquets reçues au niveau de la
 * couche réseau. Les protocoles qui peuvent être géré sont VIP et VARP.
 */
struct NetInterpreter {
    /**
     * Cette méthode permet de parser la dernière requête reçue.
     * @param ns : le stream sur lequel netInterpreter va travailler
     */
    void operator ()(NetStream const &) const;
};

} // net
} // sdc

#endif // NETINTERPRETER_HPP
