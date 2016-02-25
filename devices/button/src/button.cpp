#include "button.hpp"
#include <iostream>

using sdc::net::Addr;

void sdc::Button::onRise() {
    bool vipReq = _addr.size != 3;
    _net.asyncRequest(_addr, vipReq, [] (Addr const & com, Addr const & vip) {
        std::cout << "com = " << com.str() << std::endl;
        std::cout << "vip = " << vip.str() << std::endl;
    });
}
