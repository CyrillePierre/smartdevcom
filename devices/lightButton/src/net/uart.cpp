#include "uart.hpp"
#include "rtos/Thread.h"
#include <iostream>

using sdc::net::Uart;

Uart::Uart(type::Byte const * comAddr,
           type::Byte const * virtualAddr,
           std::size_t        comAddrSize,
           PinName			 tx,
           PinName   		 rx)
    : ReadableNetDevice(comAddr, virtualAddr, comAddrSize),
      _sr(tx, rx),
      _bufSem(0)
{
    _sr.attach(this, &Uart::readHandler);
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
    for (;;) {
        _sr.printf("buffer.size = %d\n", _buffer.size());
        rtos::Thread::wait(1000);
    }
}




















