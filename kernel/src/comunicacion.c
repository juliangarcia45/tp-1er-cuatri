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
        //recibir_mensaje(int socket_fd, void* a_enviar );

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
                log_info(logger, "Cop: %s", cop);

                return;
        }
    }

    log_warning(logger, "El cliente se desconecto de %s server", server_name);
    return;
}

int server_escuchar(char* server_name, int server_socket) {
    int cliente_socket = esperar_cliente(logger, server_name, server_socket);

    if (cliente_socket != -1) {
    	t_mensaje* mensaje=malloc(sizeof(t_mensaje));
    	mensaje=recibir_instrucciones(cliente_socket);
    	/// PRINTS DE PRUEBAS ==> aca deberia de poder imprimirse bien la lista
    	//log_info(logger,mensaje->tamanioProceso);
    	printf("Cant Elementos: %d\n ", mensaje->elementosLista); //--> ok
    	printf("Tam de proceso: %d\n ", mensaje->tamanioProceso); //--> ok
    	//printf("-------LISTA------\n");
    	//
    	// Pruebas de impresion de la lista
    	/* t_link_element* auxl1 = mensaje->listaInstrucciones->head;
    	 printf("Contenido lista:\n");
		while( auxl1!=NULL )
			{
				INSTRUCCIONES* auxl2 = auxl1->data;
				printf("Comando: %s | Par1: %d | Par2: %d \n\n", auxl2->comando, auxl2->parametro, auxl2->parametro2 );
				auxl1 = auxl1->next;
			}*/
    	//-------------------------------------

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
