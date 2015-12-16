#ifndef SDCPINTERPRETER_HPP
#define SDCPINTERPRETER_HPP

#include "types.hpp"

namespace sdc {

namespace net {
    class NetStream;
}

namespace vnet {

struct ErrorCode {
    enum Error : uint8_t {
        SUCCESS,
        UNKNOWN,
        FORMAT,
        PRMS_NB,
        EXEC
    };

    unsigned error:4;
    unsigned param:4;
};


class SDCPInterpreter {
public:
    SDCPInterpreter();

    /**
     * Cette méthode permet d'interpreter une requête SDCP
     */
    void operator()(net::NetStream &);
};

}
}

#endif // SDCPINTERPRETER_HPP
