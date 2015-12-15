#include <iostream>

#include "net/netinterpreter.hpp"

using namespace sdc;

int main()
{
    net::NetDevice device;
    net::NetStream ns(device);
    DynamicBitset dbs = ns.writingBitset();

    net::VARPHeader vh(4);

    vh.version          = 0x01; 		// Version du procotol VARP
    vh.op               = 0x00;			// Opération réalisée
    vh.scale            = 0x04;			// Taille de l'adresse du support de com (en octet)
    vh.scAddrSrc        = {192, 167, 28, 4};     // Adresse du support de com de l'objet source
    vh.addrSrc;     // Adresse de l'objet source
    vh.scAddrDest;	// Adresse du support de com de l'objet destinataire
    vh.addrDest;	// Adresse de l'objet destinataire

    dbs.push(0x00);
    dbs.push();
    dbs.push();
    dbs.push();
    dbs.push();

    return 0;
}

