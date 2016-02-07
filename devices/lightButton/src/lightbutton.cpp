#include "lightbutton.hpp"
#include "rtos/Thread.h"

using sdc::LightButton;

void LightButton::move(float val) {
    _servo = val;
    rtos::Thread::wait(moveDelay);
    _servo = .5;
    rtos::Thread::wait(moveDelay);
    _servo.stop();
}
