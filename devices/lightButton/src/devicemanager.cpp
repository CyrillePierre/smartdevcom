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
//        osEvent evt = _queue.get(100);
//        std::cout << "event : " << std::hex << evt.status << std::endl;
//        if (evt.status & osEventMessage) {
        _queueSem.wait();
        dbg::ledSignal();
//		NetDeviceElem * nde = (NetDeviceElem *) evt.value.p;
        NetDeviceElem * nde = _queue.front();
        _queue.pop_front();
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
//                    _queue.put(&nde);
                    _queue.push_back(&nde);
                    _queueSem.release();
                }
            }
        }
        rtos::Thread::wait(LISTEN_PERIOD);
    }
}
