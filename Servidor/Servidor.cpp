//
// Created by Esteban Agüero Pérez  on 4/19/18.
//

#include "Servidor.h"

/**
 * Inicializa el servidor
 */
void Servidor::iniciar() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        printf("Error: No se puede crear el socket");
    }
    servidor.sin_family = AF_INET;
    servidor.sin_addr.s_addr = INADDR_ANY;
    servidor.sin_port = htons(9090);
    if (bind(sock, (struct sockaddr *) &servidor, sizeof(servidor)) < 0) {
        std::cout << "Error: No se pudo iniciar el servidor" << std::endl;
    }
    listen(sock, 3);
    c = sizeof(struct sockaddr_in);
    std::cout << "Esperando nuevas conexiones" << std::endl;
    while ((sockCliente = accept(sock, (struct sockaddr *) &cliente, (socklen_t *) &c))) {
        std::cout << "Nueva conexion aceptada" << std::endl;

        pthread_t sniffer_thread;
        sockTemp = new int;
        *sockTemp = sockCliente;

        if (pthread_create(&sniffer_thread, NULL, hiloConexion, (void *) sockTemp) < 0) {
            std::cout << "Error: No se pudo inicializar el hilo" << std::endl;
        }

    }
}

/**
 * Elimina posibles ruidos en los mensajes y recorta el mensaje utiizando el delimitador
 * @param men
 * @return
 */
std::string Servidor::cleanMensaje(char* men) {
    std::string temp;
    for (unsigned int i = 0; i < strlen(men); i++) {
        if (men[i] == delimitador) {
            break;
        } else {
            temp += men[i];
        }
    }
    return temp;
}

/**
 * Se encarga de manejar individualmente cada cliente conectado
 * @param socket
 * @return
 */
void *Servidor::hiloConexion(void *socket) {
    int sockPtr = *(int *) socket;
    int read_size;
    char client_message[1000];
    std::string limpio;

    //Forma correcta de enviar datos
    std::string dato = "Bienvenido" + delimitador; //delimitador
    int io = write(sockPtr, dato.c_str(), dato.length());
    if (io < 0) {
        std::cout << "Error: No se pudo enviar el dato" << std::endl;
    }

    while ((read_size = recv(sockPtr, client_message, 1000, 0)) > 0) {
        limpio = cleanMensaje(client_message);
        std::cout << limpio << std::endl;

        //Repetidor de mensajes
        limpio += delimitador;
        write(sockPtr, limpio.c_str(), limpio.length());

        //Colocar logica para tratar mensajes recibidoa
    }

    if (read_size == 0) {
        std::cout << "Error: Cliente desconectado" << std::endl;
        fflush(stdout);
    } else if (read_size == -1) {
        std::cout << "Error: No se recibio un dato valido" << std::endl;
    }
}