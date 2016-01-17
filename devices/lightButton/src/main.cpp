#include <mbed.h>
#include <ST_F401_84MHZ.h>
#include "devicemanager.hpp"
#include "net/uart.hpp"
#include "net/netdevice.hpp"

using namespace sdc;

int main() {
    F401_init84 nucleoF401RE{0};

    type::Byte const comAddr[]  = {0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6},
                     virtAddr[] = {0xaa, 0xbb, 0xcc};
    DeviceManager dm;

    dm.add(new net::Uart{comAddr, virtAddr, sizeof(comAddr), D8, D2});

    for(;;) {
    }
}
