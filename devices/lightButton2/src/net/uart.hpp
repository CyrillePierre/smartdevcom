#ifndef UART_HPP
#define UART_HPP

#include "mbed.h"
#include "readablenetdevice.hpp"

namespace sdc {
namespace net {


class Uart : public ReadableNetDevice {
    Serial _sr;

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

    /** @see sdc::net::NetDevice::write */
    virtual std::size_t write(type::Byte const *, std::size_t);

    virtual bool readable() { return _sr.readable(); }
    virtual bool writeable() { return _sr.writeable(); }
};


inline Uart::Uart(type::Byte const * comAddr,
                  type::Byte const * virtualAddr,
                  std::size_t        comAddrSize,
                  PinName			 tx,
                  PinName   		 rx)
    : ReadableNetDevice(comAddr, virtualAddr, comAddrSize), _sr(tx, rx) {}

} // net
} // sdc

#endif // UART_HPP
