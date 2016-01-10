#ifndef ACTION_HPP
#define ACTION_HPP

#include "types.hpp"

namespace sdc {

class DynamicBitset;
namespace net { class NetStream; }

/**
 * Cette classe contient la description d'une action que peut exécuter l'objet
 * connecté.
 */
class Action {
    type::Word const _id;
    type::Word const _type;
    type::Word const _protoSize;

public:
    /**
     * @param id l'identifiant de l'action
     * @param type code décrivant le type d'action
     * @param protSize la taille en octets de la description du prototype
     */
    explicit Action(type::Word, type::Word, type::Word);
    virtual ~Action();

    /**
     * @brief Exécution de l'action
     * @param ns l'instance de netstream qui contient directement les paramètres
     *           de l'action et le bitset pour la réponse (pré-chargé).
     */
    virtual void operator ()(net::NetStream & ns) = 0;

    /**
     * Cette méthode permet d'ajouter le prototype de l'action dans le bitset
     * passé en paramètre
     * @param db le bitset à remplir avec le prototype de l'action
     */
    virtual void pushPrototype(DynamicBitset & db) = 0;

    /** @return la taille du prototype en octets */
    type::Word prototypeSize() const { return _protoSize; }

    type::Word id()   const { return _id;   }
    type::Word type() const { return _type; }
};


inline Action::Action(type::Word id, type::Word type, type::Word protoSize)
    : _id(id), _type(type), _protoSize(protoSize)
{}

} // sdc

#endif // ACTION_HPP
