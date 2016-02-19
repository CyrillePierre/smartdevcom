#ifndef UART_HPP
#define UART_HPP

#include <deque>
#include "mbed/Serial.h"
#include "rtos/Semaphore.h"
#include "readablenetdevice.hpp"

namespace sdc {
namespace net {


struct Uart : public ReadableNetDevice {
    static constexpr uint32_t QUEUE_SIZE = 64;

    using Buffer = std::deque<type::Byte>;

private:
    mbed::Serial    _sr;
    Buffer          _buffer;
    rtos::Semaphore _bufSem;

public:
    /**
     * @param comAddr l'adresse sur le support de communication
     * @param virtualAddr l'adresse sur le réseau virtuelle
     * @param comAddrSize la taille de l'adresse du support de com en octets
     * @param tx : pin d'émission
     * @param rx : pin de réception
     */
    Uart(type::Byte const *,
         type::Byte const *,
         std::size_t,
         PinName,
         PinName);

    /** @see sdc::net::NetDevice::read */
    virtual std::size_t read(type::Byte *, std::size_t);

    /** @brief Lecture d'un octet */
    type::Byte read();

    /** @see sdc::net::NetDevice::write */
    virtual std::size_t write(type::Byte const *, std::size_t);

    virtual bool readable() { return _buffer.size(); }
    virtual bool writeable() { return _sr.writeable(); }

    void bufferInfo();

private:
    /** @brief Interruption gérant la lecture du port série */
    void readHandler();

    void print();
};



} // net
} // sdc

#endif // UART_HPP
