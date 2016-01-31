#ifndef SDC_LIGHTBUTTON_HPP
#define SDC_LIGHTBUTTON_HPP

#include "actuator.hpp"

namespace sdc {

struct LightButton : public Actuator {
    using Actuator::Actuator;
};

} // namespace sdc

#endif // SDC_LIGHTBUTTON_HPP
