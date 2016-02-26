#include "rtos/Thread.h"
#include "devicemanager.hpp"
#include "net/uart.hpp"
#include "device.hpp"
#include "debug.hpp"
#include "button.hpp"
#include "sdcpbutton.hpp"

using namespace sdc;


template <class C, void (C::*fn)()>
void thread_cast(void const * arg) {
    C & c = *const_cast<C *>(static_cast<C const *>(arg));
    (c.*fn)();
}

int main() {
    for (int i = 0; i < 4; ++i) dbg::ledSignal(), rtos::Thread::wait(140);

    DeviceManager dm;
//    dm += new net::Uart{comAddr, vAddrBLE, sizeof(comAddr), PA_11, PA_12};
//    dm += new net::Uart{net::makeAddr<0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6>(),
//                        net::makeAddr<0x66, 0x66, 0x66>(),
//                        net::makeAddr<0x66, 0x66, 0x00>(),
//                        USBTX, USBRX};
    dm += new net::Uart{net::makeAddr<0x00, 0x15, 0x83, 0x00, 0xfa, 0x33>(),
                        net::makeAddr<0x91, 0x92, 0x18>(),
                        net::makeAddr<0x91, 0x92, 0x00>(), D8, D2};

    using Dm = DeviceManager;
    rtos::Thread tListen(&thread_cast<Dm, &Dm::listenNetDevices>, &dm);

//    Button btn{dm.net(), net::makeAddr<0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6>(),
//               USER_BUTTON};
    SDCPButton btn{dm.sdcp(), net::makeAddr<0x91, 0x92, 0x93>(), USER_BUTTON};

    dm.parseData();
}
