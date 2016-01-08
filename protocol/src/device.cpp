#include "device.hpp"
#include "actuator.hpp"
#include "sensor.hpp"

using sdc::Device;

Device::Device(Sensors::size_type nbSensors,  Actuators::size_type nbActuators)
    : _sensors(nbSensors), _actuators(nbActuators)
{
}

Device::~Device() {
    while (!_sensors.empty()) {
        delete _sensors.back();
        _sensors.pop_back();
    }

    while (!_actuators.empty()) {
        delete _actuators.back();
        _actuators.pop_back();
    }
}
