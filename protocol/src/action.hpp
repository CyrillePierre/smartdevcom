#ifndef ACTION_HPP
#define ACTION_HPP

#include "types.hpp"

namespace sdc {

class DynamicBitset;
namespace net { class NetStream; }

enum ParamType : type::Byte {
    UINT	= 0x00,
    INT		= 0x10,
    FLOAT	= 0x20,
    BOOL	= 0x30,
    STRING	= 0x40
};

enum ErrorCode : type::Byte {
    SUCCESS,
    UNKNOWN,
    FORMAT,
    PRMS_NB,
    EXEC
};

/**
 * Cette classe contient la description d'une action que peut exécuter l'objet
 * connecté.
 */
class Action {
    type::Word const _type;
    type::Word const _protoSize;
    type::Word const _returnSize;

public:
    /**
     * @param type code décrivant le type d'action
     * @param protSize la taille en octets de la description du prototype
     * @param responseSize la taille en octets du retour de l'exécution
     */
    explicit Action(type::Word, type::Word, type::Word);
    virtual ~Action() {}

    /**
     * @brief Exécution de l'action
     * @param ns l'instance de netstream qui contient directement les paramètres
     *           de l'action et le bitset pour la réponse (pré-chargé).
     */
    virtual void operator ()(net::NetStream &) = 0;

    /**
     * Cette méthode permet d'ajouter le prototype de l'action dans le bitset
     * passé en paramètre
     * @param db le bitset à remplir avec le prototype de l'action
     */
    virtual void pushPrototype(DynamicBitset &) = 0;

    /** @return la taille du prototype en octets */
    type::Word prototypeSize() const { return _protoSize; }

    /** @return la taille en octets du retour de l'exécution */
    type::Word returnSize() const { return _returnSize; }

    type::Word type() const { return _type; }
};


inline Action::Action(type::Word type,
                      type::Word protoSize,
                      type::Word returnSize)
    : _type(type), _protoSize(protoSize), _returnSize(returnSize)
{}

} // sdc

#endif // ACTION_HPP
