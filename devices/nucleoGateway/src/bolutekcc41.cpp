#include <iostream>
#include "bolutekcc41.hpp"
#include "mbed/wait_api.h"

using namespace sdc::ble;

sdc::BolutekCC41::BolutekCC41(sdc::net::Uart &uart, PinName disconnectPin)
    : _uart{uart}, _disconnect{disconnectPin}
{
    _disconnect = 1;
}

void sdc::BolutekCC41::setATMode() {
    _disconnect = 0;
    wait_us(1);
    _disconnect = 1;
}

void sdc::BolutekCC41::setMaster(bool state) {
    type::Byte b = state + '0';

    _uart.write(END.buf, END.size);
    _uart.write(ROLE.buf, ROLE.size);
    _uart.write(&b, 1);
    _uart.write(END.buf, END.size);

    waitResponse();
}

bool sdc::BolutekCC41::isMaster() {
    _uart.write(ROLE.buf, ROLE.size);
    _uart.write(END.buf, END.size);
    _uart.write(ROLE.buf, ROLE.size);
    _uart.write(END.buf, END.size);
//    std::cout.write((char const *) ROLE.buf, ROLE.size);
//    std::cout.write((char const *) END.buf, END.size);

    return readCode();
}



bool sdc::BolutekCC41::waitResponse() {
    std::size_t i = 0, j = 0;
    type::Byte b;

    for (;;) {
        b = _uart.read();

        if (b == OK.buf[i]) {
            if (++i == OK.size) return true;
        }
        else i = 0;

        if (b == ERR.buf[j]) {
            if (++j == ERR.size) return false;
        }
        else j = 0;
    }
}

sdc::type::Byte sdc::BolutekCC41::readCode() {
    for (;;) {
//        std::cout << "read" << std::endl;
        type::Byte b = _uart.read();
        if (b == '=')
            return _uart.read() - '0';
    }
}
