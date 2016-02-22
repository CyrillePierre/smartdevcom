#ifndef VARPHEADER_HPP
#define VARPHEADER_HPP

#include "netstream.hpp"
#include "types.hpp"

namespace sdc {
namespace net {

/**
 * Header de la trame VARP. La classe est template sur la taille de l'adresse
 * du support de communication
 */
struct VARPHeader {
    unsigned 			version:3; 		// Version du procotol VARP
    unsigned 			op:3;			// Opération réalisée
    unsigned 			scale:5;		// Taille de l'adresse du support de com (en octet)

    type::Byte 			*scAddrSrc;  // Adresse du support de com de l'objet source
    type::Byte 			addrSrc[3];            // Adresse de l'objet source
    type::Byte 			*scAddrDest; // Adresse du support de com de l'objet destinataire
    type::Byte          addrDest[3];	       // Adresse de l'objet destinataire

    /**
     * @param scAddrSize la taille (en octets) de l'addresse du support de
     * communication
     */
    VARPHeader(std::size_t comAddrSize);

    VARPHeader(VARPHeader &&) = delete;
    VARPHeader(VARPHeader const &) = delete;
};

inline VARPHeader::VARPHeader(std::size_t comAddrSize)
    : version{0}, op{0}, scale{0},
      scAddrSrc{new type::Byte[comAddrSize]},
      scAddrDest{new type::Byte[comAddrSize]}
{}


}
}


#endif // VARPHEADER_HPP
