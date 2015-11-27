#ifndef NETSTREAM_HPP
#define NETSTREAM_HPP

#include <iostream>
#include <functional>

namespace sdc {
namespace net {

class Socket;

/**
 * @brief Lecture et écriture sur le réseau
 *
 * Cette classe permet de se passer de la technologie utilisé pour le support
 * de communication et d"envoyer les données sur le réseau comme un simple flux
 * de bits.
 */
struct NetStream {
    using Byte = unsigned char;

private:
    Socket &_socket;	///< La socket sur laquelle ce flux travaille
    int     _sockId;	///< Identifiant de la socket

public:
    NetStream(Socket &s) : _socket(s) {}

    /**
     * @brief Envoi d'un tableau de données sur le réseau
     * @param buf : variable contenant les données à écrire
     * @param size : la taille en bits des données à écrire
     * @return une référence sur lui même.
     */
    void write(Byte const *, int);

    /**
     * @brief Récupération de données simples venant du réseau
     * @param buf : variable à remplir avec les données lues
     * @return une référence sur lui même
     */
    void read(Byte *, int);

    /**
     * @brief getter de sockId
     * @return l'identifiant de la socket
     */
    int sockId() const { return _sockId; }
};

/**
 * @brief Ajout d'un bit dans le buffer à envoyer sur le réseau.
 * @param bit : le bit à ajouter
 */
NetStream & operator <<(NetStream &, bool);

/**
 * @brief Ajout d'un octet dans le buffer à envoyer sur le réseau.
 * @param byte : l'octet à ajouter.
 */
NetStream & operator <<(NetStream &, NetStream::Byte);

} // net
} // sdc

#endif // NETSTREAM_HPP





