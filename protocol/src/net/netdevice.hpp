#ifndef NETDEVICE_HPP
#define NETDEVICE_HPP

#include "types.hpp"
#include "addr.hpp"

namespace sdc {
namespace net {

/**
 * Cette classe permet d'écrire et de lire des données depuis un support de
 * communication. Les différents support vont donc avoir leur propre
 * implémentation de cette classe abstraite.
 * @brief Support de communication
 */
struct NetDevice {
    static type::Byte const BROADCAST[];
    static constexpr std::size_t virtualAddrSize = 3;

private :
    Addr const _cAddr;	 // adresse dans le support de com
    Addr const _vAddr;	 // adresse dans le réseau virtuel
    Addr const _netAddr; // adresse de réseau

public :
    /**
     * @param comAddr l'adresse sur le support de communication
     * @param virtualAddr l'adresse sur le réseau virtuelle
     * @param comAddrSize la taille de l'adresse du support de com en octets
     * @param netAddr l'adresse de réseau
     */
    NetDevice(Addr const & comAddr,
              Addr const & virtualAddr,
              Addr const & netAddr)
        : _cAddr{comAddr}, _vAddr{virtualAddr}, _netAddr{netAddr} {}

    virtual ~NetDevice() {}

    /**
     * Cette méthode permet de récupérer un ensemble de données et de les
     * stocker dans un buffer. Il faut cependant avoir allouer l'espace mémoire
     * suffisant pour que la totalité des données demandées tiennent dans le
     * buffer.
     * @brief Lecture de données
     * @param buf : le buffer servant à stocker les données lues
     * @param size : le nombre d'octets à lire
     */
    virtual std::size_t read(type::Byte *, std::size_t) = 0;

    /**
     * Elle permet d'envoyer un buffer de données sur le support de
     * communication.
     * @brief Écriture de données
     * @param buf : le buffer contenant les données à envoyer
     * @param size : la taille du buffer
     */
    virtual std::size_t write(type::Byte const *, std::size_t) = 0;

    Addr const & comAddr()     const { return _cAddr; }
    Addr const & virtualAddr() const { return _vAddr; }
    Addr const & netAddr()     const { return _netAddr; }

    /** @return la taille de l'adresse du support de com en octets */
    std::size_t comAddrSize() const { return _cAddr.size; }

};

} // net
} // sdc

#endif // SOCKET_HPP
