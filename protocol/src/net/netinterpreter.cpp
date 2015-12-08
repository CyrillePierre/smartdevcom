#include "net/netinterpreter.hpp"
#include "net/varpheader.hpp"
#include "types.hpp"

using namespace sdc::net;
namespace type = sdc::type;

void NetInterpreter::operator ()(NetStream &ns) const {
    // Lecture du protocole (5 bits)
    type::Byte protocol;
    ns.read(protocol, 5);

    switch (protocol) {
        case Proto::VIP: break;
        case Proto::VARP: manageVARP(ns); break;
    }
}

void NetInterpreter::manageVARP(NetStream &ns) const {
    // TODO Déterminer la taille de l'adresse du support de communication
    // en utilisant une méthode de la classe NetStream
    // Elle n'est donc pas constante.
    constexpr uint16_t SIZE = 4;

    VARPHeader  varp(SIZE);
    type::Byte  byte;
    type::DWord dword;

    ns.read(byte, 3);
    varp.version = byte;

    ns.read(byte, 5);
    varp.scal = byte;

    ns.read(varp.sc_addr_src,  SIZE);
    ns.read(varp.addr_src,     3);
    ns.read(varp.sc_addr_dest, SIZE);
    ns.read(varp.addr_dest,    3);

    // TODO Cette méthode est cours d'écriture
}
