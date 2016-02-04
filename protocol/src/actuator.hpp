#ifndef ACTUATOR_HPP
#define ACTUATOR_HPP

#include "element.hpp"

namespace sdc {


/**
 * Cette classe contient les informations et les méthodes permettant de
 * controler un actionneur d'un objet connecté.
 */
struct Actuator : public Element {
    using Element::Element;

    enum ActuatorType : type::Word {
        SERVO
    };

};

} // sdc

#endif // ACTUATOR_HPP
