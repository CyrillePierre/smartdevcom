#include "netstream.hpp"

using sdc::net::NetStream;
using namespace sdc::type;

void NetStream::flushOut() {
    _socket.write((type::Byte *) _bits.begin(), _bits.size() >> 3);
    _bits.clear();
}

NetStream & operator <<(NetStream &ns, Bit bit) {
    return ns;
}

NetStream & operator <<(NetStream &ns, Byte byte) {
    return ns;
}
