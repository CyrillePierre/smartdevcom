#ifndef VIPINTERPRETER_H
#define VIPINTERPRETER_H

#include "types.hpp"
#include "vipheader.h"

namespace sdc {

class DynamicBitset;

namespace net { class NetStream; }

namespace vnet {

class SDCPInterpreter;


// TODO Description de la classe
struct VIPInterpreter {
    static constexpr type::Byte VIP_VERSION = 0;	// Version du procotole de cet interpreteur
    static constexpr type::Byte DEFAULT_TTL = 50;	// Valeur par défaut pour le TTL
    static constexpr int VIRTUAL_SIZE = 3;

private:
    SDCPInterpreter & _sdcp;

public:
    /**
     * Cette méhtode permet de construire l'header de la trame VIP et de stocker
     * cet header dans le bitset passé en paramètre.
     * @param bitset le bitset à remplir avec l'header créé
     * @param src l'adresse de la source (va dépendre de l'interface)
     * @param dest l'adresse du destinataire
     * @param ttl la durée de vie du paquet
     */
    static void buildHeader(DynamicBitset &    bitset,
                            type::Byte const * src,
                            type::Byte const * dest,
                            type::Byte         ttl = DEFAULT_TTL);

    /**
     * @brief VIPInterpreter
     * @param sdcp l'interpreteur de la couche SDCP
     */
    VIPInterpreter(SDCPInterpreter & sdcp) : _sdcp(sdcp) {}

    void operator() (net::NetStream &ns);
};

}
}

#endif // VIPINTERPRETER_H
