#include <iostream>
#include <cstdint>
#include <unistd.h>
#include "uart.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Syntaxe : \n    " << argv[0] << " <deviceFile>"
                  << std::endl;
        return 1;
    }

    std::uint8_t c;
    std::uint8_t msg[] = {0x00, 0xff, 0xa0, 0xa1, 0xa2, 0x1a,
                          0x2a, 0x3a, 0x00, 0x00, 0x00};
//    Uart uart(argv[1]);
//    uart.write(msg, sizeof(msg));

    write(1, msg, sizeof(msg));

//    std::cout << std::hex;
//    while (uart.read(&c, 1))
//        std::cout << "read : " << (unsigned) c << std::endl;
//        write(1, &c, 1);

    return 0;
}
