#ifndef ADDR_HPP
#define ADDR_HPP

#include "types.hpp"
#include <string>
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
    Addr(Addr const & addr) : size{addr.size}, vals{addr.vals} {}

    constexpr Addr(Addr && addr)
        : size{std::move(addr.size)}, vals{std::move(addr.vals)} {}

    /**
     * Calcul le niveau de broadcast de l'adresse. Il peut être nul si ce n'est
     * pas une adresse de broadcast ou valoir size si l'adresse est complètement
     * broadcast.
     * @return le niveau de broadcast de l'adresse
     */
    int broadcastLvl() const;

    /**
     * Cette méthode permet de comparer une adresse à celle-ci et de savoir
     * si elle sont compatible. L'adresse à comparer est soit l'adresse elle
     * même ou une adresse de broadcast incluant cette adresse.
     * @return true si les adresses matchent
     */
    bool accept(Addr const &) const;

    /**
     * @return true si l'adresse appartient à l'adresse de résau passé en
     * paramètre
     */
    bool isInNet(Addr const &) const;

    /** @return l'octets correspondant à l'indice dans vals */
    type::Byte operator[](std::size_t i) const { return vals[i]; }

    /** Conversion en chaine de caractère */
    std::string str() const;
};

namespace _addr {
    template <type::Byte... bytes>
    struct AddrHelper {
        static constexpr type::Byte const data[]{bytes...};
    };

    template <type::Byte... bytes>
    constexpr type::Byte const AddrHelper<bytes...>::data[];
}

/**
 * Cette fonction permet de générer facilement une adresse à la compilation.
 * La taille est calculée automatiquement. Un tableau statique sera également
 * généré pour contenir les données de l'adresse.
 */
template <type::Byte... bytes>
constexpr Addr makeAddr() {
    return Addr{_addr::AddrHelper<bytes...>::data, sizeof...(bytes)};
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
