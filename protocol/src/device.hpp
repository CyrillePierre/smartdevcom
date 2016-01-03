#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vector>

namespace sdc {

class Sensor;
class Actuator;

/**
 * Cette classe représente un objet connecté. Elle possède une liste de
 * capteurs, d'actionneurs et d'actions. Chaque objet connecté aura sa propre
 * version spécialisé de cette classe.
 */
struct Device {
    using Sensors   = std::vector<Sensor *>;
    using Actuators = std::vector<Actuator *>;

private:
    Sensors   _sensors;
    Actuators _actuators;

public:
    /**
     * Le constructeur prend en paramètre des tailles pour les conteneurs afin
     * d'éviter d'allouer trop de mémoire.
     * @param nbSensors le nombre de capteur que va posséder l'objet connecté
     * @param nbActuators le nombre d'actionneur
     */
    explicit Device(Sensors::size_type = 2, Actuators::size_type = 2);
};

} // sdc

#endif // DEVICE_HPP
