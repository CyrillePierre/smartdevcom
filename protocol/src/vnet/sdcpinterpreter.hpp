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
                     type::Word,
                     type::Byte = FrameType::response);
};

} // vnet
} // sdc

#endif // SDCPINTERPRETER_HPP
