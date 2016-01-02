#ifndef NETSTREAM_HPP
#define NETSTREAM_HPP

#include <vector>
#include <type_traits>
#include <iostream>
#include "types.hpp"
#include "dynamicbitset.hpp"
#include "net/netdevice.hpp"

namespace sdc {
namespace net {

/**
 * @brief Lecture et écriture sur le réseau
 *
 * Cette classe permet de se passer de la technologie utilisé pour le support
 * de communication et d"envoyer les données sur le réseau comme un simple flux
 * de bits.
 */
struct NetStream {
    NetDevice &     _netDevice;	///< La socket sur laquelle ce flux travaille
    uint8_t    		_sockId;	///< Identifiant de la socket
    type::Byte 		_byteIn;	///< Octet servant à stocker les quelque bits non lues
    uint8_t    		_nbBitsIn;	///< Nle nombre de bits contenus dans _byteIn
    DynamicBitset	_bits;		///< Buffer de bits contenant le paquet à envoyer
    uint16_t         _comSize;   ///< Taille de l'adresse du support de communication

public:
    NetStream(NetDevice &nd) : _netDevice(nd), _nbBitsIn(0) {}

    DynamicBitset       &writingBitset()       { return _bits; }
    DynamicBitset const &writingBitset() const { return _bits; }

    /**
     * @brief Récupération de données simples venant du réseau
     * @param buf : buffer contenant les données à lire
     * @param size : la taille en octets du buffer
     */
    void read(type::Byte *, uint16_t);

    /**
     * @brief Lecture d'une valeur depuis le réseau
     * @param data la variable qui servira à contenir la valeur lue
     * @param size le nombre de bits à lire
     */
    template <typename T,
              std::enable_if_t<std::is_integral<T>{}> * = nullptr>
    void read(T &, uint8_t = sizeof(T) << 3);

    /**
     * @brief getter de sockId
     * @return l'identifiant de la socket
     */
    int sockId() const { return _sockId; }

    /**
     * @brief Vide le buffer de lecture
     * Actuellement, la méthode ne fait rien
     */
    void flushIn();

    /**
     * @brief Envoie le contenu du buffer d'écriture sur le réseau
     */
    void flushOut();

    /**
     * @return le netdevice
     */
    NetDevice const &device() const { return _netDevice; }

    /**
     * @return La taille de l'adresse du support de communication
     */
    uint16_t comSize() const { return _comSize; }

private:
    template <typename T>
    constexpr type::Bit get(T const &, uint8_t);

    // Le nombre à modifier doit être initialisé à 0
    template <typename T>
    void set(T &, uint8_t, type::Bit = 1);
};

/**
 * @brief Ajout d'un bit dans le buffer à envoyer sur le réseau.
 * @param bit : le bit à ajouter
 */
NetStream & operator <<(NetStream &, type::Bit);

/**
 * @brief Ajout d'un octet dans le buffer à envoyer sur le réseau.
 * @param byte : l'octet à ajouter.
 */
NetStream & operator <<(NetStream &, type::Byte);


template <typename T, std::enable_if_t<std::is_integral<T>{}> *>
void NetStream::read(T & data, uint8_t size) {
    data = 0;

    while (size) {
        if (!_nbBitsIn) {
            _netDevice.read(&_byteIn, 1);
            _nbBitsIn = 8;
        }

        int8_t minNbBits = _nbBitsIn < size ? _nbBitsIn : size;
        data = data << minNbBits | _byteIn >> (_nbBitsIn - minNbBits);
        _byteIn &= (1 << (_nbBitsIn - minNbBits)) - 1;
        _nbBitsIn -= minNbBits;
        size -= minNbBits;
    }
}

} // net
} // sdc

#endif // NETSTREAM_HPP





