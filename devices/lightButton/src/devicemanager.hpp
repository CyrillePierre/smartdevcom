#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include <vector>
#include <list>
#include <types.hpp>
#include "rtos/Queue.h"
#include "rtos/Mutex.h"
#include "rtos/Semaphore.h"
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

        NetDeviceElem(net::ReadableNetDevice * nd) : nd{nd}, queued{false} {}
        NetDeviceElem(NetDeviceElem && nde) : nd{nde.nd}, queued{nde.queued} {}
    };

public:
    static constexpr int LISTEN_PERIOD = 40; // Période entre 2 écoutes (en ms)

private:
    std::vector<NetDeviceElem> _nds;
//    rtos::Queue<NetDeviceElem, 4> _queue;
    std::list<NetDeviceElem *> _queue;
    rtos::Semaphore			   _queueSem;

    vnet::SDCPInterpreter _sdcp;
    vnet::VIPInterpreter  _vip;
    net::NetInterpreter   _ni;

    rtos::Mutex _mutex;

public:
    DeviceManager() : _queueSem{0}, _vip{_sdcp}, _ni{_vip} {}
    ~DeviceManager();

    /**
     * Les périphériques ajoutés doivent être alloué avec new. DeviceManager
     * s'occupera de libérer la mémoire.
     * @param nd le NetDevice à ajouter
     */
    DeviceManager & operator +=(net::ReadableNetDevice * nd)
    { _nds.push_back(NetDeviceElem{nd}); return *this; }

    /**
     * @brief Mise à jour de la file si un nouveau périphérique contient des
     * données à lire.
     */
    void listenNetDevices();

    /** Traite les messages reçus */
    void parseData();
};

} // sdc

#endif // NETMANAGER_HPP
