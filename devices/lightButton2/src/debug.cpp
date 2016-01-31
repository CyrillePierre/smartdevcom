#include "debug.hpp"

DigitalOut dbg::led{LED1};
static Timeout ledTimeout;

static void ledOff() {
    dbg::led = 0;
}

void dbg::ledSignal() {
    dbg::led = 1;
    ledTimeout.attach_us(&ledOff, LED_DELAY);
}
