#include "rtos/Thread.h"
#include "devicemanager.hpp"
#include "net/uart.hpp"
#include "device.hpp"
#include "debug.hpp"
#include "mbed.h"

using namespace sdc;

template <class C, void (C::*fn)()>
void thread_cast(void const * arg) {
    puts("thread_cast");
    C & c = *const_cast<C *>(static_cast<C const *>(arg));
    (c.*fn)();
}

type::Byte const comAddr[]  = {0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6};
type::Byte const vAddrBLE[] = {0xaa, 0xbb, 0xcc};
type::Byte const vAddrPC[]  = {0x1a, 0x2a, 0x3a};


int main() {
    for (int i = 0; i < 4; ++i) dbg::ledSignal(), wait_ms(140);

    DeviceManager dm;
//    dm.add(new net::Uart{comAddr, vAddrBLE, sizeof(comAddr), D8, D2});
    dm.add(new net::Uart{comAddr, vAddrPC, sizeof(comAddr), USBTX, USBRX});

    using Dm = DeviceManager;
    rtos::Thread tListen(&thread_cast<Dm, &Dm::listenNetDevices>, &dm);

    dm.parseData();
}
