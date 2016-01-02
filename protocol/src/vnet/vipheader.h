#ifndef VIPHEADER_H
#define VIPHEADER_H

#include "types.hpp"

namespace sdc {
namespace vnet {

struct VIPHeader
{
    static const uint8_t TTL_LIFE;

    unsigned    version:3;    ///< Version du procotol VIP
    uint8_t     ttl;          ///< Durée de vie du paquet

    type::Byte 	addrSrc[3];     ///< Adresse de l'objet source
    type::Byte 	addrDest[3];    ///< Adresse de l'objet destinataire

    VIPHeader();
};

}
}

#endif // VIPHEADER_H
