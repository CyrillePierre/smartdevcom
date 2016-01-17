#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include <vector>
#include <list>
#include <types.hpp>
#include <net/netinterpreter.hpp>
#include <vnet/vipinterpreter.h>
#include <vnet/sdcpinterpreter.hpp>

namespace sdc {

namespace net { class NetDevice; }

/**
 * Cette classe est le médiateur du programme. Elle s'occupe d'instancier
 * chacun des interpréteurs et gère les périphériques réseaux. Une fois qu'elle
 * est démarrée, l'objet connecté est en fonctionnement.
 */
class DeviceManager {
    std::vector<net::NetDevice *> _nds;
    std::list<net::NetDevice *>   _queue;

    vnet::SDCPInterpreter _sdcp;
    vnet::VIPInterpreter  _vip;
    net::NetInterpreter   _ni;

public:
    /**
     * @brief DeviceManager
     * @param devices la liste des NetDevices que gère le DeviceManager (façon
     * 		  tableau)
     */
    DeviceManager(std::size_t size = 1) : _nds(size), _vip{_sdcp}, _ni{_vip} {}

    /** @param nd le NetDevice à ajouter */
    void add(net::NetDevice * nd) { _nds.push_back(nd); }

    /**
     * Démarre l'écoute des périphériques réseaux et traite les messages reçus
     */
    void run();
};

} // sdc

#endif // NETMANAGER_HPP
