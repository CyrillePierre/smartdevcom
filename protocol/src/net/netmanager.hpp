#ifndef NETMANAGER_HPP
#define NETMANAGER_HPP

#include <functional>

namespace sdc {
namespace net {

class NetManager
{
    std::function<void (/* à completer */)> _eventFn;

public:
    template <typename Fn, typename... Args>
    void setInterpreter(Fn &&fn, Args &&...args);
};

/**
 * @brief Méthode à appeler quand il y a des données à lire
 * @param fn fonction ou méthode à appeler
 * @param args les arguments de la fonction
 */
template <typename Fn, typename... Args>
void NetManager::setInterpreter(Fn &&fn, Args &&...args) {
    using std::placeholders::_1;
    _eventFn = std::bind(std::forward<Fn>(fn), std::forward<Args>(args)..., _1);
}

} // net
} // sdc

#endif // NETMANAGER_HPP
