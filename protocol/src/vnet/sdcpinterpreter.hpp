#ifndef SDCPINTERPRETER_HPP
#define SDCPINTERPRETER_HPP

#include <functional>
#include "types.hpp"
#include "net/routingtable.hpp"
#include "net/netstream.hpp"
#include "typetraits.hpp"

namespace sdc {
    class Device;

    namespace net {
        class Addr;
    }

    namespace view { class View; }
    namespace vnet { class VIPHeader; }
}

namespace sdc {
namespace vnet {

/**
 * @brief Structure servant à stocker un code d'erreur
 */
struct ActionErrorCode {
    enum Error : uint8_t {
        success  = 0,	///< tout s'est bien passé
        unknown  = 1,	///< identifiant de l'action inconnu
        format   = 2,
        prms_nb  = 3,
        exec     = 4
    };

    unsigned error:4;
    unsigned param:4;
};


/**
 * @brief Liste des types de trames
 */
enum FrameType : type::Byte {
    request  = 0,	///< La trame est une demande
    response = 1,	///< La trame est une réponse
    event    = 2	///< La trame est un évènement
};


/**
 * @brief Identifiant des types de requêtes
 */
enum ReqID : type::Byte {
    test         = 0,	///< test de présence
    getSensors   = 1,	///< récupération de la liste des capteurs
    getActuators = 2,	///< récupération de la liste des actionneurs
    getActions   = 3,	///< récupération de la liste des actions
    getActionDef = 4,	///< récupération du prototype d'une action
    execAction   = 5	///< exécution d'un action
};


/**
 * Cette classe s'occupe du parsage et de l'interpretation des données d'une
 * trame possédant une couche SDCP. En fonction de l'identifiant de la requête,
 * elle va pouvoir interagir avec les classes décrivant les différentes
 * fonctionnalité que propose l'objet.
 */
struct SDCPInterpreter {
    using ReqHandler = std::function<void(view::View const &)>;

private:
    ReqHandler          _reqHandler;
    net::RoutingTable & _rtable;

public:
    /**
     * @param rtable la table de routage
     */
    SDCPInterpreter(net::RoutingTable & rtable) : _rtable{rtable} {}

    /**
     * Cette méthode permet d'interpreter une requête SDCP
     * @param ns le stream permettant de lire et d'écrire les données sur
     *           le réseau
     * @param header les informations provenant de la couche VIP
     */
    void operator ()(net::NetStream &, VIPHeader const &);

    /**
     * Envoi d'une requête d'une commande SDCP. La réponse sera traitée dans
     * un callback. Les requêtes de type exec ont une méthode spécialisée.
     * @param addr addresse VIP de l'objet à qui envoyer la requête
     * @param req  l'identifiant de la requête
     * @param handler le callback appelé quand une réponse est dispo (nullptr
     *  	          est acceptée)
     * @param args... les paramètres à envoyer dans certaines requêtes
     */
    template <class... Args>
    void request(net::Addr const &, ReqID, ReqHandler const &, Args...);

private:
    void rpTest        (net::NetStream &, VIPHeader const &, type::Byte);
    void rpGetSensors  (net::NetStream &, VIPHeader const &, type::Byte);
    void rpGetActuators(net::NetStream &, VIPHeader const &, type::Byte);
    void rpGetActions  (net::NetStream &, VIPHeader const &, type::Byte);
    void rpGetActionDef(net::NetStream &, VIPHeader const &, type::Byte);
    void rpExecAction  (net::NetStream &, VIPHeader const &, type::Byte);

    /**
     * Construction de l'header SDCP. La méthode s'occupe également de la
     * construction des couches du dessus
     * @param ns le netstream lié à l'émetteur
     * @param addr l'adresse de l'émetteur
     * @param id l'identifiant de la requête
     * @param size la taille de la couche SDCP
     * @param reqType le type de requête
     */
    void buildHeader(net::NetStream &,
                     type::Byte const *,
                     type::Byte,
                     type::Word,
                     type::Byte = FrameType::response);
};



template <class... Args>
void SDCPInterpreter::request(net::Addr const &  addr,
                              ReqID              req,
                              ReqHandler const & handler,
                              Args...            args)
{
    net::NetDevice & nd = _rtable[addr];
    net::NetStream ns{nd};

    buildHeader(ns, addr.vals, req, Sizeof<Args...>{} + 1, FrameType::request);

    DynamicBitset & db = ns.writingBitset();
    using Expander = int[];
    Expander{0, (db.push(args), 0)...};

    _reqHandler = handler;
    ns.flushOut();
}

} // vnet
} // sdc

#endif // SDCPINTERPRETER_HPP
