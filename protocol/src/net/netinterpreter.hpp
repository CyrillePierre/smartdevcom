#ifndef NETINTERPRETER_HPP
#define NETINTERPRETER_HPP

#include "net/netstream.hpp"
#include "net/varpheader.hpp"
#include "vnet/vipinterpreter.h"

namespace sdc {
namespace net {


enum Proto : type::Byte {
    VIP  = 0,	// virtual IP
    VARP = 1	// virtual ARP
};

/**
 * Cette classe s'occupe de l'interpretation des paquets reçues au niveau de la
 * couche réseau. Les protocoles qui peuvent être géré sont VIP et VARP.
 */
struct NetInterpreter {
    static constexpr sdc::type::Byte START_DELIM = 0xcc;

private:
    vnet::VIPInterpreter & _vip;

public:
    /**
     * @brief NetInterpreter
     * @param vip l'interpreteur de la couche VIP
     */
    NetInterpreter(vnet::VIPInterpreter & vip) : _vip(vip) {}

    /**
     * Cette méthode permet de parser la dernière requête reçue.
     * @param ns : le stream sur lequel netInterpreter va travailler
     */
    void operator ()(NetStream &);

private :
    void manageVARP(NetStream &) const;
    void sendVARP(NetStream &ns, const sdc::net::VARPHeader &header) const;
};

} // net
} // sdc

#endif // NETINTERPRETER_HPP
