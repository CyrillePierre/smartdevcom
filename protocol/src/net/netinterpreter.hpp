#ifndef NETINTERPRETER_HPP
#define NETINTERPRETER_HPP

#include <functional>
#include "net/varpheader.hpp"
#include "net/addr.hpp"

namespace sdc {
namespace vnet { class VIPInterpreter; }
namespace net {
class RoutingTable;


enum Proto : type::Byte {
    VIP  = 0,	// virtual IP
    VARP = 1	// virtual ARP
};

enum VarpOperation : type::Byte {
    COM_ADDR_REQ = 0,
    VIP_ADDR_REQ,
    RESPONSE
};


/**
 * Cette classe s'occupe de l'interpretation des paquets reçues au niveau de la
 * couche réseau. Les protocoles qui peuvent être géré sont VIP et VARP.
 */
struct NetInterpreter {
    using ReqHandler = std::function<void(Addr const &, Addr const &)>;

    static constexpr sdc::type::Byte START_DELIM  = 0xcc;
    static constexpr sdc::type::Byte VARP_VERSION = 0;

private:
    RoutingTable         & _rtable;
    vnet::VIPInterpreter & _vip;
    ReqHandler             _reqHandler;

public:
    /**
     * @brief NetInterpreter
     * @param vip l'interpreteur de la couche VIP
     */
    NetInterpreter(RoutingTable & rt, vnet::VIPInterpreter & vip)
        : _rtable{rt}, _vip{vip}, _reqHandler{nullptr} {}

    /**
     * Cette méthode permet de parser la dernière requête reçue.
     * @param ns : le stream sur lequel netInterpreter va travailler
     */
    void operator ()(NetStream &);

    /**
     * Cette méthode permet d'envoyer une requête VARP. La réponse sera
     * réceptionnée de façon asynchrone par le Callable passé en paramètre.
     * @param addr l'adresse VIP ou du support (en fonction de isVIPReq)
     * @param isVIPReq permet de choisir entre une demande d'adresse VIP et
     * 	      une adresse de support. (true : founir une adresse de support)
     * @param callable la fonction qui sera appelée lorsque la réponse à la
     *        requête sera reçue.
     * 		  (prototype : void(*)(Addr const &, Addr const &) avec
     * 		  Addr1 = adresse de support
     * 		  Addr2 = adresse VIP)
     */
    template <class Callable>
    void asyncRequest(Addr const &, bool, Callable &&);

private :
    void manageVARP(NetStream &) const;
    void sendVARPResponse(NetStream &, const sdc::net::VARPHeader &) const;

    void findTargets(Addr const &, bool);
    void sendVARPRequest(NetDevice &, Addr const &, bool);
};

template <class Callable>
void NetInterpreter::asyncRequest(Addr const & addr,
                                  bool         isVIPReq,
                                  Callable &&  callable)
{
    findTargets(addr, isVIPReq);
    _reqHandler = std::forward<Callable>(callable);
}

} // net
} // sdc

#endif // NETINTERPRETER_HPP
