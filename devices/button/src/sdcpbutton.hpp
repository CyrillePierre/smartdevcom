#ifndef SDCPBUTTON_HPP
#define SDCPBUTTON_HPP

#include "mbed/InterruptIn.h"
#include "net/addr.hpp"
#include "vnet/sdcpinterpreter.hpp"

namespace sdc {

class SDCPButton {
    vnet::SDCPInterpreter & _sdcp;
    net::Addr const       & _addr;
    mbed::InterruptIn       _btn;

public:
    SDCPButton(vnet::SDCPInterpreter & sdcp, net::Addr const & addr, PinName pn)
        : _sdcp{sdcp}, _addr{addr}, _btn{pn}
    { _btn.rise(this, &SDCPButton::onRise); }

private:
    void onRise();
};

} // namespace sdc

#endif // SDCPBUTTON_HPP
