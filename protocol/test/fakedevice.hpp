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

    FakeDevice(type::Byte const * comAddr,
               type::Byte const * virtualAddr,
               std::size_t        comAddrSize)
        : net::NetDevice(comAddr, virtualAddr, comAddrSize), pos(0) {}

    virtual void read(type::Byte * b, int size)
    { while (size--) *b++ = buf[pos++]; }


    virtual void write(type::Byte const * b, int size)
    { for (type::Byte * it = buf; size--;) *it++ = *b++; }

    void reset() { pos = 0; }
};

} // test
} // sdc

#endif // FAKEDEVICE_HPP
