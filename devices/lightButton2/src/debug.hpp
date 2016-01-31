#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <mbed.h>

namespace dbg {

/** @brief Durée pendant laquelle la led reste allumée (en us) */
constexpr timestamp_t LED_DELAY = 30000;

/** @brief la led présente sur la NUCLEO */
extern DigitalOut led;

/** @brief Allume la led présente sur la NUCLEO pendant un cour instant */
void ledSignal();

}

#endif // DEBUG_HPP
