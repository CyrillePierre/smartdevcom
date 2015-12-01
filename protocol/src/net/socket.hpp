#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "types.hpp"

namespace sdc {
namespace net {

/**
 * Cette classe permet d'écrire et de lire des données depuis un support de
 * communication. Les différents support vont donc avoir leur propre
 * implémentation de cette classe abstraite.
 * @brief Support de communication
 */
struct Socket
{
    /**
     * Cette méthode permet de récupérer un ensemble de données et de les
     * stocker dnas un buffer. Il faut cependant avoir allouer l'espace mémoire
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
};

} // net
} // sdc

#endif // SOCKET_HPP
