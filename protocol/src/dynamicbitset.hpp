#ifndef DYNAMICBITSET_HPP
#define DYNAMICBITSET_HPP

#include <vector>
#include <iostream>
#include "types.hpp"

namespace sdc {

/**
 * Cette classe représente un conteneur permettant de travailler avec des bits.
 * Les bits sont stockés dans des blocs de données dont la taille fait 1 octet.
 */
struct DynamicBitset {
    using BlockType     = type::Byte;
    using Bits          = std::vector<BlockType>;
    using Iterator      = Bits::iterator;
    using ConstIterator = Bits::const_iterator;
    using SizeType		= uint16_t;

private:
    Bits     _bits;		// Tableau d'octets contenant les bits
    SizeType _size;		// Nombre de bits présent dans le tableau

public:
    DynamicBitset() : _size(0) {}

    /**
     * Ajout d'un tableau de données à la fin du bitset
     * @param buf : le tableau de données à ajouter
     * @param size : la taille du tableau en octets
     */
    template <typename T,
              std::enable_if_t<std::is_integral<T>{}> * = nullptr>
    void push(T *, SizeType);

    /**
     * Ajout d'une valeur à la fin du bitset
     * @param data : le valeur à ajouter
     * @param size : la taille en bits de la valeur
     */
    template <typename T,
              std::enable_if_t<std::is_integral<T>{}> * = nullptr>
    void push(T, SizeType = sizeof(T) << 3);

    /// @return un itérateur sur le début du bitset
    Iterator      begin()       noexcept { return _bits.begin(); }
    ConstIterator begin() const noexcept { return _bits.begin(); }

    /// @return un itérateur sur la fin du bitset
    Iterator      end()       noexcept { return _bits.end(); }
    ConstIterator end() const noexcept { return _bits.end(); }

    /// @return un pointeur sur le début du tableau contenant les données
    type::Byte       *data()       noexcept { return _bits.data(); }
    type::Byte const *data() const noexcept { return _bits.data(); }

    /// @brief Vide le contenu du bitset
    void clear() noexcept { _bits.clear(); _size = 0; }

    /// @return la taille du bitset (en bits)
    SizeType size() const noexcept { return _size; }

    /// @return le nombre de blocs qu'occupe le bitset
    Bits::size_type blockSize() const noexcept { return _bits.size(); }

    /// @return true si le bitset est vide
    bool empty() const noexcept { return _bits.empty(); }
};


template <typename T, std::enable_if_t<std::is_integral<T>{}> *>
void DynamicBitset::push(T * data, SizeType size) {
    for (; size; size -= sizeof(T)) push(*data++);
}

template <typename T, std::enable_if_t<std::is_integral<T>{}> *>
void DynamicBitset::push(T data, SizeType size) {
    // Fin de remplissage du dernier octet du tableau
    uint16_t lBits = 8 - (_size & 7);
    if (lBits < 8) {
        uint16_t nbBitsToAdd = lBits < size ? lBits : size;
        type::Byte b = data >> (size - nbBitsToAdd);
        _bits.back() |= (b & ~(0xff << nbBitsToAdd)) << (lBits - nbBitsToAdd);
        size  -= nbBitsToAdd;
        _size += nbBitsToAdd;
    }

    // Insertion des octets complets
    for (; size >> 3; _size += 8)
        _bits.push_back(type::Byte((data >> (size -= 8)) & 0xff));

    // Insertion des bits restants
    if (size) {
        _bits.push_back(type::Byte(data << (8 - size)));
        _size += size;
    }
}

} // sdc

#endif // DYNAMICBITSET_HPP
