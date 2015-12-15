#include <iostream>
#include "netstream.hpp"

using sdc::net::NetStream;
using namespace sdc::type;

void NetStream::flushOut() {
    _netDevice.write(_bits.data(), _bits.blockSize());
    _bits.clear();
}

void NetStream::flushIn() {

}

NetStream & operator <<(NetStream &ns, Bit bit) {
    return ns;
}

NetStream & operator <<(NetStream &ns, Byte byte) {
    return ns;
}

void NetStream::read(type::Byte *buf, uint16_t size) {
    _netDevice.read(buf, size);
}


