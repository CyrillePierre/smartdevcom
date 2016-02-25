#ifndef SDC_BUTTON_HPP
#define SDC_BUTTON_HPP

#include "mbed/InterruptIn.h"
#include "net/addr.hpp"
#include "net/netinterpreter.hpp"

namespace sdc {

class Button {
    net::NetInterpreter & _net;
    net::Addr const     & _addr;
    mbed::InterruptIn     _btn;

public:
    Button(net::NetInterpreter & net, net::Addr const & addr, PinName pn)
        : _net{net}, _addr{addr}, _btn{pn} { _btn.rise(this, &Button::onRise); }

private:
    void onRise();
};

} // namespace sdc

#endif // SDC_BUTTON_HPP
