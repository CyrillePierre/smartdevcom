#ifndef DYNAMICBITSET_HPP
#define DYNAMICBITSET_HPP

#include <vector>
#include "types.hpp"

namespace sdc {

struct DynamicBitset {
    using Bits          = std::vector<type::Byte>;
    using Iterator      = Bits::iterator;
    using ConstIterator = Bits::const_iterator;

private:
    Bits     _bits;		// Tableau d'octets contenant les bits
    uint16_t _size;		// Nombre de bits présent dans le tableau

public:
    DynamicBitset() : _size(0) {}

    /**
     * Ajout d'un tableau de données à la fin du bitset
     * @param buf : le tableau de données à ajouter
     * @param size : le nombre de bits total
     */
    template <typename T,
              typename = std::enable_if<std::is_integral<T>::value>>
    void push(T *, uint16_t);

    /**
     * Ajout d'une valeur à la fin du bitset
     * @param data : le valeur à ajouter
     * @param size : la taille en bits de la valeur
     */
    template <typename T,
              typename = std::enable_if<std::is_integral<T>::value>>
    void push(T, uint8_t);

    /// @return un itérateur sur le début du bitset
    Iterator      begin()       { return _bits.begin(); }
    ConstIterator begin() const { return _bits.begin(); }

    /// @return un itérateur sur la fin du bitset
    Iterator      end()         { return _bits.end(); }
    ConstIterator end()   const { return _bits.end(); }

    /// @return un pointeur sur le début du tableau contenant les données
    type::Byte       *data()       { return _bits.data(); }
    type::Byte const *data() const { return _bits.data(); }
};

template <typename T, typename>
void DynamicBitset::push(T * data, uint8_t size) {

}

template <typename T, typename>
void DynamicBitset::push(T data, uint8_t size) {
    // Fin de remplissage du dernier octet du tableau
    uint16_t lastBits = _size & 3;
    if (lastBits) _bits.back() |= type::Byte(data & (0xff00 >> lastBits));

    // Insertion des octets complets
    for (; size >> 3; data >>= 8, size -= 8)
        _bits.push_back(type::Byte(data & 0xff));

    // Insertion des bits restants
    if (size) _bits.push_back(type::Byte(data & (0xff >> (8 - size))));
}

} // sdc

#endif // DYNAMICBITSET_HPP
