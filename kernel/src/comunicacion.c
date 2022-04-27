/*
 * comunicacion.c
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */

#include "comunicacion.h"
typedef struct {
    int fd;
    char* server_name;
} t_procesar_conexion_args;

static void procesar_conexion(void* void_args) {
    t_procesar_conexion_args* args = (t_procesar_conexion_args*) void_args;
    int cliente_socket = args->fd;
    char* server_name = args->server_name;
    free(args);

    op_code cop;
    while (cliente_socket != -1) {

        if (recv(cliente_socket, &cop, sizeof(op_code), 0) != sizeof(op_code)) {
            log_info(logger, "Se ha finalizado la conexion");
            return;
        }

        switch (cop) {
            case DEBUG:
                log_info(logger, "debug");
                break;
            // Errores
            case -1:
                log_error(logger, "Cliente desconectado de %s...", server_name);
                return;
            default:
                log_error(logger, "Algo anduvo mal en el server de %s", server_name);
                log_info(logger, "Cop: %d", cop);
                return;
        }
    }

    log_warning(logger, "El cliente se desconecto de %s server", server_name);
    return;
}

int server_escuchar(char* server_name, int server_socket) {
    int cliente_socket = esperar_cliente(logger, server_name, server_socket);

    if (cliente_socket != -1) {
        pthread_t hilo;
        t_procesar_conexion_args* args = malloc(sizeof(t_procesar_conexion_args));
        args->fd = cliente_socket;
        args->server_name = server_name;
        pthread_create(&hilo, NULL, (void*) procesar_conexion, (void*) args);
        pthread_detach(hilo);
        return 1;
    }
    return 0;
}

//CLIENTE
int generar_conexiones(int* interrupt_fd, int* dispatch_fd, t_config_kernel* configuracion) {
    char* port_dispatch = string_itoa(configuracion->PUERTO_CPU_DISPATCH);
    char* port_interrupt = string_itoa(configuracion->PUERTO_CPU_INTERRUPT);

    *dispatch_fd = crear_conexion(
            logger,
            "CPU DISPATCH",
            configuracion->IP_CPU,
            port_dispatch
    );

    free(port_dispatch);

    *interrupt_fd = crear_conexion(
            logger,
            "CPU INTERRUPT",
            configuracion->IP_CPU,
            port_interrupt
    );

    free(port_interrupt);

    return *interrupt_fd != 0 && *dispatch_fd != 0;
}
