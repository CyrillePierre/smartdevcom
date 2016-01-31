#include "device.hpp"
#include "actuator.hpp"
#include "sensor.hpp"
#include "action.hpp"

using sdc::Device;

Device::~Device() {
    while (!_sensors.empty()) {
        delete _sensors.back();
        _sensors.pop_back();
    }

    while (!_actuators.empty()) {
        delete _actuators.back();
        _actuators.pop_back();
    }

    while (!_actions.empty()) {
        delete _actions.back();
        _actions.pop_back();
    }
}
