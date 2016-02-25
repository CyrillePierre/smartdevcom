#include <iostream>
#include <chrono>
#include <cstdint>
#include <unistd.h>
#include <map>
#include <string>
#include <thread>
#include "uart.h"

/*
 * Test pour appareil avec les caractéristiques suivantes :
 * comAddr = 00:15:83:00:6e:d6
 * vipAddr = a1:a2:a3
 */
#define MY_VIP_ADDR   0xda, 0xb0, 0x0b
#define MY_COM_ADDR   0x12, 0x99, 0x99, 0x76, 0xf0, 0x0f
#define COM_BROADCAST 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
#define VIP_BROADCAST 0xff, 0xff, 0xff
#define COM_ADDR      0x00, 0x15, 0x83, 0x00, 0x6e, 0xd6
#define VIP_ADDR      0xa1, 0xa2, 0xa3

using Buf = std::uint8_t[];
std::map<std::string, std::pair<int, std::uint8_t const *>> const bufs {
    {"sdcp.exec", 	 {16, Buf{0x36, 0xcc, 0x00, 0xff, MY_VIP_ADDR, VIP_ADDR,
                              0x00, 0x04, 0x14, 0x00, 0x00, 0x01}}},
    {"varp.com", 	 {21, Buf{0xcc, 0x08, 0x06,
                              MY_COM_ADDR, 	 MY_VIP_ADDR,
                              COM_BROADCAST, VIP_ADDR}}},
    {"varp.vip", 	 {21, Buf{0xcc, 0x08, 0x26,
                              MY_COM_ADDR, 	 MY_VIP_ADDR,
                              COM_ADDR,	     VIP_BROADCAST}}},
    {"varp.all", 	 {21, Buf{0xcc, 0x08, 0x26,
                              MY_COM_ADDR, 	 MY_VIP_ADDR,
                              COM_BROADCAST, VIP_BROADCAST}}}
};

void showAvailableBuffers() {
    std::cerr << "Buffers disponibles : ";
    for (auto const & buf : bufs)
        std::cerr << buf.first << ' ';
    std::cerr << std::endl;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Syntaxe : \n    " << argv[0]
                  << " <deviceFile> <buffer>" << std::endl;
        showAvailableBuffers();
        return 1;
    }

    Uart uart(argv[1]);
    if (!uart.open(B9600)) {
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
        return 2;
    }

    try {
        auto const & buf = bufs.at(argv[2]);
        std::thread t([&buf, &uart] {
            using namespace std::literals;
            for (;;) {
                uart.write(buf.second, buf.first);
                std::this_thread::sleep_for(1000ms);
            }
        });

        std::uint8_t bs[32];
        ssize_t nb;
        while ((nb = uart.read(bs, 32))) write(1, bs, nb);
    }
    catch (...) {
        std::cerr << "Erreur : Buffer inconnu." << std::endl;
        showAvailableBuffers();
        return 3;
    }

    return 0;
}
