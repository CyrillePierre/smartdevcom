#include <iostream>
#include <chrono>
#include <cstdint>
#include <unistd.h>
#include <thread>
#include "uart.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Syntaxe : \n    " << argv[0] << " <deviceFile>"
                  << std::endl;
        return 1;
    }

    Uart uart(argv[1]);
    if (!uart.open(B9600)) {
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
        return 2;
    }

    std::uint8_t const msg[] = {0x36, 0xcc, 0x00, 0xff, 0xa0, 0xa1, 0xa2,
                                0x0a, 0xb0, 0xc0, 0x00, 0x04,
                                0x14, 0x00, 0x00, 0x01};

    std::thread t([&] {
        using namespace std::literals;
        for (;;) {
            uart.write(msg, 16);
            std::this_thread::sleep_for(1000ms);
        }
    });

    std::uint8_t buf[32];
    ssize_t nb;
    while ((nb = uart.read(buf, 32))) write(1, buf, nb);

    return 0;
}
