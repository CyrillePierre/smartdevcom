#ifndef VIPINTERPRETER_H
#define VIPINTERPRETER_H

#include "net/netstream.hpp"

namespace sdc {
namespace vnet {

struct VIPInterpreter
{
    static constexpr int VIRTUAL_SIZE = 3;

    VIPInterpreter();

    void operator() (net::NetStream &ns) const;
};

}
}

#endif // VIPINTERPRETER_H
