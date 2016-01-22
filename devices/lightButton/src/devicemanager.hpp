#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include "mbed.h"
#include <vector>
#include <list>
#include <types.hpp>
#include <net/netinterpreter.hpp>
#include <vnet/vipinterpreter.h>
#include <vnet/sdcpinterpreter.hpp>
#include "net/readablenetdevice.hpp"

namespace sdc {

namespace net { class NetDevice; }

/**
 * Cette classe est le médiateur du programme. Elle s'occupe d'instancier
 * chacun des interpréteurs et gère les périphériques réseaux. Une fois qu'elle
 * est démarrée, l'objet connecté est en fonctionnement.
 */
class DeviceManager {
    struct NetDeviceElem {
        net::ReadableNetDevice * nd;
        bool			         queued;
    };

public:
    static constexpr int LISTEN_PERIOD = 40000; // Période entre 2 écoutes (en us)

private:
    std::vector<NetDeviceElem> _nds;
    std::list<NetDeviceElem *> _queue;

    vnet::SDCPInterpreter _sdcp;
    vnet::VIPInterpreter  _vip;
    net::NetInterpreter   _ni;

    Ticker _readTicker;	// Timer d'écoute des périphériques réseaux

public:
    /**
     * @brief DeviceManager
     * @param devices la liste des NetDevices que gère le DeviceManager (façon
     * 		  tableau)
     */
    DeviceManager(std::size_t = 1);

    ~DeviceManager();

    /**
     * Les périphériques ajoutés doivent être alloué avec new. DeviceManager
     * s'occupera de libérer la mémoire.
     * @param nd le NetDevice à ajouter
     */
    void add(net::ReadableNetDevice * nd)
    { _nds.push_back(NetDeviceElem{nd, false}); }

    /**
     * Démarre l'écoute des périphériques réseaux et traite les messages reçus
     */
    void run();

private:
    /**
     * @brief Mise à jour de la file si un nouveau périphérique contient des
     * données à lire.
     */
    void listenNetDevice();
};

} // sdc

#endif // NETMANAGER_HPP
