#ifndef SDC_NET_READABLENETDEVICE_HPP
#define SDC_NET_READABLENETDEVICE_HPP

#include <net/netdevice.hpp>

namespace sdc {
namespace net {

/**
 * Cette classe ajoute des fonctionalitées spécifiques aux caractéristiques des
 * microcontrôleurs comme la NUCLEO. La lecture n'étant pas bloquante, il est
 * nécessaire d'avoir une méthode pour déterminer quand le bus possède des
 * données.
 */
struct ReadableNetDevice : public NetDevice {
    template <class... Args>
    ReadableNetDevice(Args... args) : NetDevice(args...) {}

    virtual ~ReadableNetDevice() {}

    /** @return true quand des données sont disponible à la lecture */
    virtual bool readable() = 0;

    /** @return true quand le périphérique est prêt à écrire */
    virtual bool writeable() = 0;
};

} // namespace net
} // namespace sdc

#endif // SDC_NET_READABLENETDEVICE_HPP
