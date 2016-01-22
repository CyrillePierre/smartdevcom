#include "devicemanager.hpp"

using sdc::DeviceManager;


DeviceManager::DeviceManager(std::size_t size)
    : _nds(size), _vip{_sdcp}, _ni{_vip}
{
    _readTicker.attach_us(this, &DeviceManager::listenNetDevice, LISTEN_PERIOD);
}

DeviceManager::~DeviceManager()
{
    for (NetDeviceElem & nde : _nds)
        delete nde.nd;
}

void DeviceManager::run() {
    for (;;) {
        if (!_queue.empty()) {
            sdc::net::NetStream ns{*_queue.front()->nd};
            _ni(ns);
            _queue.pop_front();
        }
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
