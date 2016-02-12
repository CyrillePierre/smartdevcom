#include "rtos/Thread.h"
#include "devicemanager.hpp"
#include "debug.hpp"
#include <iostream>

using sdc::DeviceManager;


DeviceManager::~DeviceManager()
{
    for (NetDeviceElem & nde : _nds)
        delete nde.nd;
}

void DeviceManager::parseData() {
    for (;;) {
        NetDeviceElem * nde = _queue.pop();	// Bloquant
        dbg::ledSignal();
        sdc::net::NetStream ns{*nde->nd};
        _ni(ns);
        nde->queued = false;
    }
}

void DeviceManager::listenNetDevices() {
    for (;;) {
        for (NetDeviceElem & nde : _nds) {
            if (nde.nd->readable() && !nde.queued) {
                sdc::type::Byte b;
                nde.nd->read(&b, 1);

                if (b == sdc::net::NetInterpreter::START_DELIM) {
                    nde.queued = true;
                    _queue.push(&nde);
                }
            }
        }
        rtos::Thread::wait(LISTEN_PERIOD);
    }
}
