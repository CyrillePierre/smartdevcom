#include "uart.hpp"
#include "rtos/Thread.h"
#include "mbed/Ticker.h"
#include <iostream>

using sdc::net::Uart;
using sdc::net::Addr;

//static mbed::Ticker tk;

Uart::Uart(Addr const & comAddr,
           Addr const & virtualAddr,
           Addr const & netAddr,
           PinName	    tx,
           PinName      rx)
    : ReadableNetDevice(comAddr, virtualAddr, netAddr),
      _sr(tx, rx),
      _bufSem(0)
{
    _sr.attach(this, &Uart::readHandler);
//    tk.attach_us(this, &Uart::bufferInfo, 1000000);
}

std::size_t Uart::read(sdc::type::Byte * buf, std::size_t size) {
    std::size_t i;
    for (i = 0; i < size; ++i, ++buf) {
        _bufSem.wait();

        *buf = _buffer.front();
        _buffer.pop_front();
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

void Uart::readHandler() {
    while (_sr.readable()) {
        char b = _sr.getc();
        _buffer.push_back(b);
        _bufSem.release();
    }
}

// TODO à enlever
void Uart::bufferInfo() {
//    for (;;) {
        _sr.printf("buffer.size = %d\n", _buffer.size());
//        rtos::Thread::wait(1000);
//    }
}




















