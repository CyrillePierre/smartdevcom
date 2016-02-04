#include <iostream>
#include "net/netstream.hpp"
#include "net/netinterpreter.hpp"

using sdc::net::NetStream;
using namespace sdc::type;

void NetStream::flushOut() {
    type::Byte b = sdc::net::NetInterpreter::START_DELIM;
    _netDevice.write(&b, 1);
    _netDevice.write(_bits.data(), _bits.blockSize());
    _bits.clear();
}

void NetStream::flushIn() {

}

void NetStream::read(type::Byte *buf, uint16_t size) {
    _netDevice.read(buf, size);
}


