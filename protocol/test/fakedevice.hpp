#ifndef FAKEDEVICE_HPP
#define FAKEDEVICE_HPP

#include "types.hpp"
#include "netdevice.hpp"

namespace sdc {
namespace test {

/**
 * Un pseudo-device pour faire des tests sans avoir à utiliser de réseau.
 */
struct FakeDevice : public net::NetDevice {
    type::Byte *buf;
    int pos;

    FakeDevice(net::Addr const & comAddr,
               net::Addr const & virtualAddr,
               net::Addr const & netAddr)
        : net::NetDevice(comAddr, virtualAddr, netAddr), pos(0) {}

    virtual std::size_t read(type::Byte * b, std::size_t size)
    { while (size--) *b++ = buf[pos++]; return size; }


    virtual std::size_t write(type::Byte const * b, std::size_t size)
    { for (type::Byte * it = buf; size--;) *it++ = *b++; return size; }

    void reset() { pos = 0; }
};

} // test
} // sdc

#endif // FAKEDEVICE_HPP
