#include "uart.hpp"

using sdc::net::Uart;


std::size_t Uart::read(sdc::type::Byte * buf, std::size_t size) {
    std::size_t i;
    for (i = 0; i < size; ++i, ++buf) {
        while (!_sr.readable());	// Attente de données
        *buf = _sr.getc();
    }
    return i;
}

std::size_t Uart::write(sdc::type::Byte const * buf, std::size_t size) {
    std::size_t i;
    for (i = 0; i < size; ++i, ++buf) {
        while (!_sr.writeable());	// Attente que l'UART soit prête
        _sr.putc(*buf);
    }
    return i;
}
