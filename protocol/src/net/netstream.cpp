#include "netstream.hpp"

using sdc::net::NetStream;
using namespace sdc::type;

NetStream & operator <<(NetStream &ns, Bit bit) {
    return ns;
}

NetStream & operator <<(NetStream &ns, Byte byte) {
    return ns;
}
