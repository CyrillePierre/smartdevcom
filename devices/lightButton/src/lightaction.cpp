#include "lightaction.hpp"
#include "net/netstream.hpp"

using sdc::LightAction;

constexpr sdc::type::Byte const LightAction::proto[];

void LightAction::operator ()(sdc::net::NetStream & ns) {
    sdc::type::Byte state;
    ns.read(state);
    _light = state;
}
