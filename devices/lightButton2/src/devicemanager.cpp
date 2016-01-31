#include "devicemanager.hpp"
#include "debug.hpp"

using sdc::DeviceManager;


DeviceManager::DeviceManager() : _vip{_sdcp}, _ni{_vip} {
    _readTicker.attach_us(this, &DeviceManager::listenNetDevice, LISTEN_PERIOD);
}

DeviceManager::~DeviceManager()
{
    for (NetDeviceElem & nde : _nds)
        delete nde.nd;
}

void DeviceManager::run() {
    for (;;) {
        while (!_queue.empty()) {
            dbg::ledSignal();
            NetDeviceElem * nde = _queue.front();
            sdc::net::NetStream ns{*nde->nd};
            _ni(ns);
            _queue.pop_front();
            nde->queued = false;
        }

        wait_ms(100);
    }
}

void DeviceManager::listenNetDevice() {
    for (NetDeviceElem & nde : _nds) {
        if (nde.nd->readable() && !nde.queued) {
            nde.queued = true;
            _queue.push_back(&nde);
        }
    }
}
