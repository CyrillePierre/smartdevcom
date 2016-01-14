#ifndef NETDEVICE_HPP
#define NETDEVICE_HPP

#include "types.hpp"

namespace sdc {
namespace net {

/**
 * Cette classe permet d'écrire et de lire des données depuis un support de
 * communication. Les différents support vont donc avoir leur propre
 * implémentation de cette classe abstraite.
 * @brief Support de communication
 */
struct NetDevice {
    static const type::Byte BROADCAST[];

private :
    type::Byte const * const _comAddr;       // adresse dans le support de com
    type::Byte const * const _virtualAddr;   // adresse dans le réseau virtuel

public :
    /**
     * @param comAddr l'adresse sur le support de communication
     * @param virtualAddr l'adresse sur le réseau virtuelle
     */
    NetDevice(type::Byte const *, type::Byte const *);

    /**
     * Cette méthode permet de récupérer un ensemble de données et de les
     * stocker dans un buffer. Il faut cependant avoir allouer l'espace mémoire
     * suffisant pour que la totalité des données demandées tiennent dans le
     * buffer.
     * @brief Lecture de données
     * @param buf : le buffer servant à stocker les données lues
     * @param size : le nombre d'octets à lire
     */
    virtual void read(type::Byte *, int) = 0;

    /**
     * Elle permet d'envoyer un buffer de données sur le support de
     * communication.
     * @brief Écriture de données
     * @param buf : le buffer contenant les données à envoyer
     * @param size : la taille du buffer
     */
    virtual void write(type::Byte const *, int) = 0;

    const type::Byte* getComAddr()        const { return _comAddr; }
    const type::Byte* getVirtualAddr()    const { return _virtualAddr; }
};

inline NetDevice::NetDevice(type::Byte const * comAddr,
                            type::Byte const * virtualAddr)
    : _comAddr(comAddr), _virtualAddr(virtualAddr)
{
}

} // net
} // sdc

#endif // SOCKET_HPP
