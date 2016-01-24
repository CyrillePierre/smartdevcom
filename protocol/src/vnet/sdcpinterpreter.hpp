#ifndef SDCPINTERPRETER_HPP
#define SDCPINTERPRETER_HPP

#include "types.hpp"

namespace sdc {

class DynamicBitset;
class Device;

namespace net { class NetStream; }

namespace vnet {

class VIPHeader;


/**
 * @brief Structure servant à stocker un code d'erreur
 */
struct ActionErrorCode {
    enum Error : uint8_t {
        success,	///< tout s'est bien passé
        unknown,	///< identifiant de l'action inconnu
        format,
        prms_nb,
        exec
    };

    unsigned error:4;
    unsigned param:4;
};


/**
 * @brief Liste des types de trames
 */
enum FrameType : type::Byte {
    request,	///< La trame est une demande
    response,	///< La trame est une réponse
    event		///< La trame est un évènement
};


/**
 * @brief Identifiant des types de requêtes
 */
enum ReqID : type::Byte {
    test = 0,		///< test de présence
    getSensors,		///< récupération de la liste des capteurs
    getActuators,	///< récupération de la liste des actionneurs
    getActions,		///< récupération de la liste des actions
    getActionDef,	///< récupération du prototype d'une action
    execAction		///< exécution d'un action
};


/**
 * Cette classe s'occupe du parsage et de l'interpretation des données d'une
 * trame possédant une couche SDCP. En fonction de l'identifiant de la requête,
 * elle va pouvoir interagir avec les classes décrivant les différentes
 * fonctionnalité que propose l'objet.
 */
struct SDCPInterpreter {
    /**
     * Cette méthode permet d'interpreter une requête SDCP
     * @param ns le stream permettant de lire et d'écrire les données sur
     *           le réseau
     * @param header les informations provenant de la couche VIP
     */
    void operator ()(net::NetStream &, VIPHeader const &);

private:
    void test        (net::NetStream &, VIPHeader const &, type::Byte);
    void getSensors  (net::NetStream &, VIPHeader const &, type::Byte);
    void getActuators(net::NetStream &, VIPHeader const &, type::Byte);
    void getActions  (net::NetStream &, VIPHeader const &, type::Byte);
    void getActionDef(net::NetStream &, VIPHeader const &, type::Byte);
    void execAction  (net::NetStream &, VIPHeader const &, type::Byte);

    /**
     * Construction de l'header SDCP. La méthode s'occupe également de la
     * construction des couches du dessus
     * @param ns le netstream lié à l'émetteur
     * @param id l'identifiant de la requête
     * @param reqType le type de requête
     */
    void buildHeader(net::NetStream &,
                     VIPHeader const &,
                     type::Byte,
                     type::Byte = FrameType::response);
};

} // vnet
} // sdc

#endif // SDCPINTERPRETER_HPP
