#include <iostream>
#include "rtos/Thread.h"
#include "devicemanager.hpp"
#include "net/uart.hpp"
#include "device.hpp"
#include "debug.hpp"
#include "bolutekcc41.hpp"

using namespace sdc;

type::Byte const comAddr[]  = {0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6};
type::Byte const vAddrBLE[] = {0xaa, 0xbb, 0xcc};
type::Byte const vAddrPC[]  = {0x1a, 0x2a, 0x3a};


template <class C, void (C::*fn)()>
void thread_cast(void const * arg) {
    C & c = *const_cast<C *>(static_cast<C const *>(arg));
    (c.*fn)();
}

int main() {
    for (int i = 0; i < 4; ++i) dbg::ledSignal(), rtos::Thread::wait(140);
    std::cout << "start" << std::endl;

    net::Uart uart{comAddr, vAddrBLE, sizeof(comAddr), D8, D2};
    BolutekCC41 bolu{uart, D4};

    bolu.setMaster(1);
    rtos::Thread::wait(1000);
    std::cout << "isMaster ? : " << bolu.isMaster() << std::endl;
    bolu.setMaster(0);
    rtos::Thread::wait(1000);
    std::cout << "isMaster ? : " << bolu.isMaster() << std::endl;

    std::cout << "end" << std::endl;
    for (;;);
}
