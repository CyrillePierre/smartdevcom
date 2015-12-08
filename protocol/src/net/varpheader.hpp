#ifndef VARPHEADER_HPP
#define VARPHEADER_HPP

#include "netstream.hpp"
#include "types.hpp"
#include <vector>

namespace sdc {
namespace net {

/**
 * Header de la trame VARP. La classe est template sur la taille de l'adresse
 * du support de communication
 */
struct VARPHeader
{
    unsigned 			version:3; 		// Version du procotol VARP
    unsigned 			op:3;			// Opération réalisée
    unsigned 			scal:5;			// Taille de l'adresse du support de com (en octet)
    type::Byte 			*sc_addr_src;	// Adresse du support de com de l'objet source
    type::Byte 			addr_src[3];	// Adresse de l'objet source
    type::Byte 			*sc_addr_dest;	// Adresse du support de com de l'objet destinataire
    type::Byte          addr_dest[3];	// Adresse de l'objet destinataire

    /**
     * @param scAddrSize la taille (en octets) de l'addresse du support de
     * communication
     */
    VARPHeader(uint8_t);
};

}
}


#endif // VARPHEADER_HPP
