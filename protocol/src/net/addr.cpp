#include "addr.hpp"
#include <iostream>

using sdc::net::Addr;
namespace type = sdc::type;


int Addr::broadcastLvl() const {
    int cpt = 0;
    for (int i = size - 1; i >= 0 && vals[i] == 0xff; --i, ++cpt);
    return cpt;
}

bool Addr::accept(Addr const & a) const {
    bool result = this->size == a.size;
    std::size_t const bcLvl = a.broadcastLvl(), addrLvl = a.size - bcLvl;

    for (std::size_t i = 0; result && i < addrLvl; ++i)
        result = (*this)[i] == a[i];

    for (std::size_t i = addrLvl; result && i < a.size; ++i)
        result = ((*this)[i] | a[i]) == a[i];

    return result;
}

bool sdc::net::operator ==(Addr const & a, Addr const & b) {
    bool result = a.size == b.size;
    for (std::size_t i = 0; result && i < a.size; ++i)
        result = a[i] == b[i];
    return result;
}


bool sdc::net::operator !=(Addr const & a, Addr const & b) {
    return !(a == b);
}

