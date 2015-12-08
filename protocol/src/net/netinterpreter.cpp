#include "netinterpreter.hpp"

using namespace sdc::net;
using sdc::type;

void NetInterpreter::operator ()(NetStream const &ns) const {
    // Lecture du protocole (5 bits)
    type::Byte protocol;
    ns.read(protocol, 5);

    switch (protocol) {
    case Proto::VIP:	break;
    case Proto::VARP: 	break;
    }
}
