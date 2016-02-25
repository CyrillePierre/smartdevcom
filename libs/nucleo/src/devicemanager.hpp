#ifndef DEVICEMANAGER_HPP
#define DEVICEMANAGER_HPP

#include <vector>
#include <types.hpp>
#include "rtos/Mutex.h"
#include "net/netmanager.hpp"
#include "net/readablenetdevice.hpp"
#include "util/msgqueue.hpp"

namespace sdc {

namespace net { class NetDevice; }

/**
 * Cette classe est le médiateur du programme. Elle s'occupe d'instancier
 * chacun des interpréteurs et gère les périphériques réseaux. Une fois qu'elle
 * est démarrée, l'objet connecté est en fonctionnement.
 */
class DeviceManager : public net::NetManager {
    struct NetDeviceElem {
        net::ReadableNetDevice * nd;
        bool			         queued;

        NetDeviceElem(net::ReadableNetDevice * nd) : nd{nd}, queued{false} {}
        NetDeviceElem(NetDeviceElem && nde) = default;
    };

public:
    static constexpr int LISTEN_PERIOD = 40; // Période entre 2 écoutes (en ms)

private:
    std::vector<NetDeviceElem> _nds;
    util::MsgQueue<NetDeviceElem *, util::SingleWriter, util::SingleReader>
        _queue;

    rtos::Mutex _mutex;

public:
    ~DeviceManager();

    /**
     * @brief Mise à jour de la file si un nouveau périphérique contient des
     * données à lire.
     */
    void listenNetDevices();

    /** Traite les messages reçus */
    void parseData();

    /**
     * Les périphériques ajoutés doivent être alloué avec new. DeviceManager
     * s'occupera de libérer la mémoire.
     * @param nd le NetDevice à ajouter
     */
    NetManager & operator +=(net::ReadableNetDevice * nd)
    { _nds.push_back(NetDeviceElem{nd}); rtable() += nd; return *this; }
};

} // sdc

#endif // NETMANAGER_HPP
