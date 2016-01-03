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
    type::Byte _id;
    type::Word _type;

public:
    explicit Element(type::Byte id, type::Word type) : _id(id), _type(type) {}
    virtual ~Element() {}

    /** @return l'identifiant de l'élément */
    type::Byte id()   const { return _id; }

    /** @return le type de l'élément */
    type::Word type() const { return _type; }
};

} // sdc

#endif // ELEMENT_HPP
