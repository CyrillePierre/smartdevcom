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
    /** Singleton */
    static Device & get() { static Device d; return d; }

private:
    /**
     * Le constructeur prend en paramètre des tailles pour les conteneurs afin
     * d'éviter d'allouer trop de mémoire.
     * @param nbSensors le nombre de capteur que va posséder l'objet connecté
     * @param nbActuators le nombre d'actionneur
     */
    explicit Device(Sensors::size_type = 2, Actuators::size_type = 2);

public:
    /** Le destructeur s'occupe de la destruction des éléments contenus */
    ~Device();

    /**
     * Ajout d'un capteur
     * @param s le capteur à ajouter
     */
    void operator +=(Sensor * s) { _sensors.push_back(s); }

    /**
     * Ajout d'un actionneur
     * @param a l'actionneur à ajouter
     */
    void operator +=(Actuator * a) { _actuators.push_back(a); }

    /** @return la liste des capteurs */
    Sensors const & sensors() const { return _sensors; }

    /** @return la liste des actionneurs */
    Actuators const & actuators() const { return _actuators; }
};

} // sdc

#endif // DEVICE_HPP
