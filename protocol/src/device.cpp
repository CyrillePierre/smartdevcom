#include "device.hpp"

using sdc::Device;

Device::Device(Sensors::size_type nbSensors,  Actuators::size_type nbActuators)
    : _sensors(nbSensors), _actuators(nbActuators)
{
}
