#include <iostream>
#include "uart.h"

int main(int argc, char ** argv) {
    if (argc != 2) {
        std::cerr << "Syntaxe : \n    " << argv[0] << " <deviceFile>"
                  << std::endl;
        return 1;
    }

    Uart uart(argv[1]);
    if (!uart.open(B9600)) {
        std::cerr << "Erreur d'ouverture du fichier" << std::endl;
        return 2;
    }



    return 0;
}
