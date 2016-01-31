#include "rtos/Thread.h"
#include "devicemanager.hpp"
#include "debug.hpp"
#include "mbed.h"

using sdc::DeviceManager;


DeviceManager::~DeviceManager()
{
    for (NetDeviceElem & nde : _nds)
        delete nde.nd;
}

void DeviceManager::parseData() {
    for (;;) {
        if (!_queue.empty()) {
            dbg::ledSignal();
            NetDeviceElem * nde = _queue.front();
            sdc::net::NetStream ns{*nde->nd};
            _ni(ns);
            _queue.pop_front();
            nde->queued = false;
        }

        rtos::Thread::wait(100);
    }
}

void DeviceManager::listenNetDevices() {
    for (;;) {
        for (NetDeviceElem & nde : _nds) {
            if (nde.nd->readable() && !nde.queued) {
                nde.queued = true;
                _queue.push_back(&nde);
            }
        }
        rtos::Thread::wait(LISTEN_PERIOD);
    }
}
