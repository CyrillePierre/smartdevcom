#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <vector>
#include "types.hpp"

namespace sdc {

class Sensor;
class Actuator;
class Action;

/**
 * Cette classe représente un objet connecté. Elle possède une liste de
 * capteurs, d'actionneurs et d'actions. Chaque objet connecté aura sa propre
 * version spécialisé de cette classe.
 */
struct Device {
    using Sensors   = std::vector<Sensor *>;
    using Actuators = std::vector<Actuator *>;
    using Actions   = std::vector<Action *>;

private:
    Sensors   _sensors;
    Actuators _actuators;
    Actions   _actions;

public:
    /** Singleton */
    static Device & get() { static Device d; return d; }

private:
    Device()               = default;
    Device(Device const &) = delete;
    Device(Device &&)      = delete;

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

    /**
     * Ajout d'une action
     * @param a l'action à ajouter
     */
    void operator +=(Action * a) { _actions.push_back(a); }

    /** @return la liste des capteurs */
    Sensors const & sensors() const { return _sensors; }

    /** @return la liste des actionneurs */
    Actuators const & actuators() const { return _actuators; }

    /** @return la liste des actions */
    Actions const & actions() const { return _actions; }

    /**
     * Récupération d'une action par son identifiant
     * @param id l'identifiant de l'action à récupérer
     * @return l'action correspondante ou null si elle n'existe pas
     */
    Action * action(type::Word id) const
    { return (id < _actions.size()) ? _actions[id] : nullptr; }

    /** @return le nombre de capteurs */
    Sensors::size_type nbSensors() const noexcept { return _sensors.size(); }

    /** @return le nombre d'actionneurs */
    Actuators::size_type nbActuators() const noexcept
    { return _actuators.size(); }

    /** @return le nombre d'actions */
    Actions::size_type nbActions() const noexcept { return _actions.size(); }
};

} // sdc

#endif // DEVICE_HPP
