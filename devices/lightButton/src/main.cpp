#include "rtos/Thread.h"
#include "devicemanager.hpp"
#include "net/uart.hpp"
#include "device.hpp"
#include "lightbutton.hpp"
#include "lightaction.hpp"
#include "debug.hpp"
#include "mbed.h"

using namespace sdc;

//type::Byte const comAddr[]  = {0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6};
//type::Byte const vAddrBLE[] = {0xaa, 0xbb, 0xcc};
//type::Byte const vAddrPC[]  = {0x1a, 0x2a, 0x3a};


template <class C, void (C::*fn)()>
void thread_cast(void const * arg) {
    C & c = *const_cast<C *>(static_cast<C const *>(arg));
    (c.*fn)();
}

int main() {
    for (int i = 0; i < 4; ++i) dbg::ledSignal(), rtos::Thread::wait(140);

    LightButton * lb = new LightButton(D3);

    Device & d = Device::get();
    d += lb;
    d += new LightAction(*lb);

    DeviceManager dm;
    dm += new net::Uart{net::makeAddr<0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6>(),
                        net::makeAddr<0x91, 0x92, 0x93>(), D8, D2};
//    dm += new net::Uart{comAddr, vAddrBLE, sizeof(comAddr), PA_11, PA_12};
    dm += new net::Uart{net::makeAddr<0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6>(),
                        net::makeAddr<0xa1, 0xa2, 0xa3>(),
                        USBTX, USBRX};

    using Dm = DeviceManager;
    rtos::Thread tListen(&thread_cast<Dm, &Dm::listenNetDevices>, &dm);

    dm.parseData();

    tListen.terminate();
}
