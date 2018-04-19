#include <iostream>
#include "Servidor.h"

int main() {
    std::cout << "Iniciando Servidor" << std::endl;
    Servidor servi=Servidor();
    servi.iniciar();
    return 0;
}

