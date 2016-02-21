#ifndef ADDR_HPP
#define ADDR_HPP

#include "types.hpp"
#include <initializer_list>
#include <utility>

namespace sdc {
namespace net {

/**
 * Cette classe sert à définir quelques opérateurs pour manipuler plus
 * des adresses. La taille de celle-ci n'a pas d'importance. Elle doivent
 * juste être composée de bloc de 8 bits.
 */
struct Addr {
    std::size_t        const size;
    type::Byte const * const vals;

    /** @param vals liste des valeurs de chaque octets de l'adresse */
    constexpr Addr(type::Byte const * vals, std::size_t const size)
        : size{size}, vals{vals} {}

    /** Pas de copie */
    Addr(Addr const &) = delete;

    constexpr Addr(Addr && addr)
        : size{std::move(addr.size)}, vals{std::move(addr.vals)} {}

    /**
     * Calcul le niveau de broadcast de l'adresse. Il peut être nul si ce n'est
     * pas une adresse de broadcast ou valoir size si l'adresse est complètement
     * broadcast.
     * @return le niveau de broadcast de l'adresse
     */
    int broadcastLvl() const;

    /** @return l'octets correspondant à l'indice dans vals */
    type::Byte operator[](std::size_t i) const { return vals[i]; }
};

namespace _addr {
    template <std::size_t size>
    struct AddrHelper {
        type::Byte data[size];
    };

    template <type::Byte... bytes>
    struct AddrBuilder {
        static constexpr type::Byte const data[]{bytes...};
    };

    template <type::Byte... bytes>
    constexpr type::Byte const AddrBuilder<bytes...>::data[];
}

/**
 * Cette fonction permet de générer facilement une adresse à la compilation.
 * La taille est calculée automatiquement. Un tableau statique sera également
 * généré pour contenir les données de l'adresse.
 */
template <type::Byte... bytes>
constexpr Addr makeAddr() {
//    return Addr{_addr::AddrHelper<sizeof...(bytes)>{bytes...}.data, sizeof...(bytes)};
    return Addr{_addr::AddrBuilder<bytes...>::data, sizeof...(bytes)};
}

/**
 * Opérateur de comparaison
 * @return true si les adresses sont identiques
 */
bool operator ==(Addr const &, Addr const &);

/** Inverse de l'operateur de comparaison */
bool operator !=(Addr const &, Addr const &);

}	// sdc
}	// net

#endif // ADDR_HPP
