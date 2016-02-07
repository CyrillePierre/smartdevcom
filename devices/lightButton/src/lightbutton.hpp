#ifndef SDC_LIGHTBUTTON_HPP
#define SDC_LIGHTBUTTON_HPP

#include "actuator.hpp"
#include "Servo/Servo.h"

namespace sdc {

struct LightButton : public Actuator {
    static constexpr uint32_t moveDelay = 300;	// ms

private:
    Servo _servo;
    bool  _state;

public:
    LightButton(PinName pn) : Actuator(ActuatorType::SERVO), _servo(pn) {}

    void operator =(bool state) { move((_state = state) ? 0 : 1); }
    operator bool() { return _state; }

private:
    void move(float);
};

} // namespace sdc

#endif // SDC_LIGHTBUTTON_HPP
