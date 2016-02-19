#ifndef BOLUTEKCC41_HPP
#define BOLUTEKCC41_HPP

#include <cstring>
#include "net/uart.hpp"
#include "mbed/DigitalOut.h"

namespace sdc {

namespace ble {
    struct StaticString {
        type::Byte const * buf;
        std::size_t  size;

        constexpr StaticString(char const * buf)
            : buf{(type::Byte *) buf}, size{std::strlen(buf)} {}
    };

    constexpr StaticString END   {"\r\n"};
    constexpr StaticString OK    {"OK\r\n"};
    constexpr StaticString ERR   {"ERROR="};

    // Liste des commandes AT utilisées
    constexpr StaticString AT    {"AT"};
    constexpr StaticString NAME  {"AT+NAME"};
    constexpr StaticString BAUD  {"AT+BAUD"};
    constexpr StaticString ADDR  {"AT+ADDR"};
    constexpr StaticString ROLE  {"AT+ROLE"};
    constexpr StaticString SLEEP {"AT+SLEEP"};
    constexpr StaticString START {"AT+START"};
    constexpr StaticString STOP  {"AT+STOP"};
};

/**
 * Cette classe permet de communiquer avec le firmware AT des BLE de chez
 * Bolutek. Elle possède aussi des fonctionnalités de déconnexion du BLE qui
 * font intervenir une modification hardware du module CC41 (la déconnexion).
 */
class BolutekCC41 {
    net::Uart & _uart;
    mbed::DigitalOut _disconnect;

public:
    /**
     * Constructeur
     * @param uart          le port série utilisé pour la communication
     * @param disconnectPin la pin de déconnexion du BLE
     */
    BolutekCC41(net::Uart & uart, PinName disconnectPin);

    /** @brief bascule le BLE en mode AT (déconnecte ou réveille le module) */
    void setATMode();

    /**
     * @brief changement du role du BLE
     * @param state true pour passer le BLE en maitre, false pour esclave.
     */
    void setMaster(bool);

    /**
     * @brief récupération du role du BLE
     * @return true si le BLE est maitre, false si il est esclave.
     */
    bool isMaster();

private:
    /** @brief Attente de la réponse (message "OK") */
    bool waitResponse();

    /** @brief Lecture du code de réponse à une requête */
    type::Byte readCode();
};

} // sdc

#endif // BOLUTEKCC41_HPP
