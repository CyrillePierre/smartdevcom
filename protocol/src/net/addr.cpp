#include "addr.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

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

bool Addr::isInNet(const sdc::net::Addr & net) const {
    bool result = size == net.size;
    for (std::size_t i = 0; result && i < size; ++i)
        if (net[i]) result = (*this)[i] == net[i];
    return result;
}

std::string Addr::str() const {
    std::ostringstream oss;

    oss << std::hex;
    for (std::size_t i = 0; i < size; ++i)
        oss << (i == 0 ? "" : ":") << std::setfill('0')
            << std::setw(2) << (int) (*this)[i];

    return oss.str();
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

