#ifndef NETSTREAM_HPP
#define NETSTREAM_HPP

#include <boost/dynamic_bitset.hpp>
#include <type_traits>
#include "types.hpp"
#include "net/socket.hpp"

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
    using Bits = boost::dynamic_bitset<type::Byte>;

private:
    Socket &   _socket;		///< La socket sur laquelle ce flux travaille
    uint8_t    _sockId;		///< Identifiant de la socket
    Bits	   _bits;		///< Buffer de bits contenant le paquet à envoyer
    type::Byte _byteIn;		///< Octet servant à stocker les quelque bits non lues
    uint8_t    _nbBitsIn;	///< Nle nombre de bits contenus dans _byteIn

public:
    NetStream(Socket &s) : _socket(s) {}

    /**
     * @brief Envoi d'un tableau de données sur le réseau
     * @param buf : buffer contenant les données à écrire
     * @param size : la taille en octets du buffer
     */
    void write(type::Byte *, uint16_t);

    /**
     * Envoi d'une valeur directe
     * @param data la valeur à écrire
     * @param size le nombre de bits de la valeur
     */
    template <typename T,
              typename = std::enable_if<std::is_integral<T>::value>>
    void write(T, uint8_t);

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
              typename = std::enable_if<std::is_integral<T>::value>>
    void read(T &, uint8_t);

    /**
     * @brief getter de sockId
     * @return l'identifiant de la socket
     */
    int sockId() const { return _sockId; }

    /**
     * @brief Vide le buffer de lecture
     */
    void flushIn();

    /**
     * @brief Envoie le contenu du buffer d'écriture sur le réseau
     */
    void flushOut();

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


template <typename T, typename>
void NetStream::write(T data, uint8_t size) {
    for (uint8_t i = 0; i < size; ++i)
        _bits.push_back((type::Bit) (data & (1 << i)));
}

template <typename T, typename>
void NetStream::read(T & data, uint8_t size) {
    for (uint8_t i = 0; i < size;) {
        for (; i < size && _nbBitsIn; --_nbBitsIn, _byteIn >>= 1)
            set(data, i++, _byteIn & 1);

        _socket.read(&_byteIn, 1);
        _nbBitsIn = 8;
    }
}

template <typename T>
constexpr type::Bit NetStream::get(T const & val, uint8_t i) {
    return (val >> i) & 1;
}

template <typename T>
void NetStream::set(T & val, uint8_t i, type::Bit bit) {
    val |= bit << i;
}

} // net
} // sdc

#endif // NETSTREAM_HPP





