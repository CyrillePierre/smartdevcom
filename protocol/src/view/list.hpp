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

private:
    std::vector<Elem> _elems;

public:
    List(net::NetStream &);
};

} // view
} // sdc

#endif // ACTIONLIST_HPP
