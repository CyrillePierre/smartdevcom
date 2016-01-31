#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include "types.hpp"

namespace sdc {

/**
 * Cette classe représente un élément que peut posséder un objet connecté.
 * Il peut s'agir d'un actionneur ou d'un capteur.
 */
class Element {
protected:
    type::Word const _type;

public:
    explicit Element(type::Word type) : _type{type} {}
    virtual ~Element() {}

    /** @return le type de l'élément */
    type::Word type() const { return _type; }
};

} // sdc

#endif // ELEMENT_HPP
