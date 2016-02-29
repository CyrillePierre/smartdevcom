#include "list.hpp"

using sdc::view::List;
using sdc::net::NetStream;
using namespace sdc::type;

List::List(NetStream & ns) : _elems{ns.read<Byte>()} {
    for (Elem & elem : _elems) {
        elem.id   = ns.read<Word>();
        elem.type = ns.read<Word>();
    }
}
