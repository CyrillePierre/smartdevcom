#include <mbed.h>
#include <ST_F401_84MHZ.h>
#include "devicemanager.hpp"
#include "net/uart.hpp"
#include "device.hpp"
#include "debug.hpp"

using namespace sdc;

type::Byte const comAddr[]  = {0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6};
type::Byte const vAddrBLE[] = {0xaa, 0xbb, 0xcc};
type::Byte const vAddrPC[]  = {0x1a, 0x2a, 0x3a};


int main() {
    F401_init84 nucleoF401RE{0};

    for (int i = 0; i < 4; ++i) dbg::ledSignal(), wait_ms(140);

//    auto uart = new net::Uart{comAddr, vAddrPC, sizeof(comAddr), USBTX, USBRX};

    DeviceManager dm;
//    dm.add(new net::Uart{comAddr, vAddrBLE, sizeof(comAddr), D8, D2});
    dm.add(new net::Uart{comAddr, vAddrPC, sizeof(comAddr), USBTX, USBRX});
    dm.run();
}
