#ifndef SDC_LIGHTBUTTON_HPP
#define SDC_LIGHTBUTTON_HPP

#include "mbed/DigitalOut.h"
#include "actuator.hpp"

namespace sdc {

class LightButton : public Actuator {
    mbed::DigitalOut _light;

public:
    LightButton(PinName pn) : Actuator(ActuatorType::SERVO), _light(pn) {}
};

} // namespace sdc

#endif // SDC_LIGHTBUTTON_HPP
