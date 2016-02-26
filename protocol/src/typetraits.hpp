#ifndef TYPETRAITS_HPP
#define TYPETRAITS_HPP

namespace sdc {

/** Calcul de la taille (en octets) d'un pack */
template <class...>
struct Sizeof;

template <class Arg, class... Args>
struct Sizeof<Arg, Args...> {
    static constexpr std::size_t val = sizeof(Arg) + Sizeof<Args...>::val;
    constexpr operator std::size_t() { return val; }
};

template <>
struct Sizeof<> {
    static constexpr std::size_t val = 0;
    constexpr operator std::size_t() { return val; }
};

}

#endif // TYPETRAITS_HPP
