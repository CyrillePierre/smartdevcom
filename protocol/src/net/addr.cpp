#include "addr.hpp"

using sdc::net::Addr;
namespace type = sdc::type;


int Addr::broadcastLvl() const {
    int cpt = 0;
    for (int i = size - 1; i >= 0 && vals[i] == 0xff; ++i, ++cpt);
    return cpt;
}

bool sdc::net::operator ==(const Addr & a, const Addr & b) {
    bool result = a.size == b.size;
    for (std::size_t i = 0; result && i < a.size; ++i)
        result &= a[i] == b[i];
    return result;
}


bool sdc::net::operator !=(const Addr & a, const Addr & b) {
    return !(a == b);
}

