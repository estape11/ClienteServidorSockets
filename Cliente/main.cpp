//
// Created by Esteban Agüero Pérez  on 4/19/18.
//

#include "Cliente.h"

int main() {
    std::cout << "Iniciando Cliente" << std::endl;
    Cliente servi = Cliente();
    servi.iniciarConexion("192.168.100.6", "9090");
    servi.escribirServidor("Hola soy un nuevo cliente");
    std::string men="";
    while(true){
        std::cout<< servi.leerServidor()<<std::endl;
        cin>>men;
        servi.escribirServidor(men);

    }
    return 0;
}