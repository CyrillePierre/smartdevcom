#ifndef NETSTREAM_HPP
#define NETSTREAM_HPP

#include <iostream>
#include <functional>

/**
 * @brief Lecture et écriture sur le réseau
 *
 * Cette classe permet de se passer de la technologie utilisé pour le support
 * de communication et d"envoyer les données sur le réseau comme un simple flux.
 */
class NetStream {
    std::function<void()> _eventFn;
    bool                  _listenerEnabled;

public:
    NetStream() : _listenerEnabled(true) {}

    /**
     * @brief Envoi d'un tableau de données sur le réseau
     * @param t : variable contenant les données à écrire
     * @param size : la taille en octets des données à écrire
     * @return une référence sur lui même.
     */
    template <typename Buffer>
    void write(Buffer const &, int);

    /**
     * @brief Récupération de données simples venant du réseau
     * @param t : variable à remplir avec les données lues
     * @return une référence sur lui même
     */
    template <typename Buffer>
    void read(Buffer const &, int);

    /**
     * @brief Méthode à appeler quand il y a des données à lire
     * @param fn fonction ou méthode à appeler
     * @param args les arguments de la fonction
     */
    template<typename Fn, typename... Args>
    void setListener(Fn &&, Args &&...);

    /**
     * @brief Activation/Désactivation du listener
     * @param state vaut true si le listener est activer, false sinon.
     */
    void enableListener(bool state) { _listenerEnabled = state; }

    /**
     * @return true si le listener est activé.
     */
    bool listenerEnabled() { return _listenerEnabled; }
};

/**
 * @brief Envoi de donnée simples sur le réseau
 * @param t : variable contenant les données à écrire
 * @param size : la taille en octets des données à écrire
 * @return une référence sur lui même.
 */
template <typename T>
NetStream & operator <<(NetStream & ns, T && t) {
    std::cout << std::forward<T>(t);
    return ns;
}

/**
 * @brief Récupération de données simples venant du réseau
 * @param t : variable à remplir avec les données lues
 * @return une référence sur lui même
 */
template <typename T>
NetStream & operator >>(NetStream & ns, T &t) {
    std::cin >> t;
    return ns;
}

template <typename Buffer>
void NetStream::write(Buffer const & buf, int size) {
    std::cout.write(buf, size);
}

template <typename Buffer>
void NetStream::read(Buffer const & buf, int size) {
    std::cin.read(buf, size);
}

template<typename Fn, typename... Args>
void NetStream::setListener(Fn && fn, Args &&... args) {
    _eventFn = std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...);
}

#endif // NETSTREAM_HPP





