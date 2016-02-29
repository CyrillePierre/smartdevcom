#ifndef ACTIONLIST_HPP
#define ACTIONLIST_HPP

#include <vector>
#include "view/view.hpp"
#include "net/netstream.hpp"

namespace sdc {
namespace view {

/**
 * Cette classe permet de parcourrir une liste d'éléments reçu d'une requête.
 */
struct List : public View {
    struct Elem {
        type::Word id;
        type::Word type;
    };

    using Elems         = std::vector<Elem>;
    using Iterator      = Elems::iterator;
    using ConstIterator = Elems::const_iterator;
    using SizeType      = Elems::size_type;

private:
    Elems _elems;

public:
    List(net::NetStream &);

    Iterator      begin()       noexcept { return _elems.begin(); }
    ConstIterator begin() const noexcept { return _elems.begin(); }
    Iterator      end()         noexcept { return _elems.end(); }
    ConstIterator end()   const noexcept { return _elems.end(); }
    SizeType      size()  const noexcept { return _elems.size(); }
};

} // view
} // sdc

#endif // ACTIONLIST_HPP
