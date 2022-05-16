/*
 * comunicacion.c
 *
 *  Created on: 23 abr. 2022
 *      Author: utnso
 */
#include "comunicacion.h"
//PROCESAR CONEXIONES SEPARADAS
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
 case DISPATCH: {
	 PCB* pcb= malloc(sizeof(PCB));
	 pcb=recibir_pcb(cliente_socket);
	 log_info(logger,"recibi pcb");
	 break;
 }
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

int servers_escuchar(char* server_interrupt_name, int server_interrupt_socket, char* server_dispatch_name, int server_dispatch_socket) {
	int cliente_interrupt_socket = esperar_cliente(logger,server_interrupt_name, server_interrupt_socket);
	int cliente_dispatch_socket = esperar_cliente(logger, server_dispatch_name, server_dispatch_socket);

	if (cliente_interrupt_socket != -1 && cliente_dispatch_socket != -1) {
		t_procesar_conexion_args* argsInt = malloc(sizeof(t_procesar_conexion_args));
		argsInt->fd = cliente_interrupt_socket;
		argsInt->server_name = server_interrupt_name;
		t_procesar_conexion_args* argsDis = malloc(sizeof(t_procesar_conexion_args));
        argsDis->fd = cliente_dispatch_socket;
		argsDis->server_name = server_dispatch_name;
		procesar_conexion(argsInt);
		procesar_conexion(argsDis);
        return 1;
	}
	return 0;
}

//HAY QUE PROCESAR LAS INTERRUPCIONES CON UN HILO
//HACER GLOBALES LOS SOCKETS

//PROCESAR CONEXIONES JUNTAS
/*typedef struct {
	int fd1;
	char* server_name1;
	int fd2;
	char* server_name2;
} t_procesar_conexiones_args;

static void procesar_conexiones(void* void_args) {
	t_procesar_conexiones_args* args = (t_procesar_conexiones_args*) void_args;
	int cliente_interrupt_socket = args->fd1;
	char* server_interrupt_name = args->server_name1;
	int cliente_dispatch_socket = args->fd2;
	char* server_dispatch_name = args->server_name2;
	free(args);

	op_code copInt;
	op_code copDis;
		while (cliente_interrupt_socket != -1 && cliente_dispatch_socket != -1) {
			if (recv(cliente_interrupt_socket, &copInt, sizeof(op_code), 0)
					!= sizeof(op_code)) {
				log_info(logger, "Se ha finalizado la conexion con Interrupt");
				return;
			}
			if (recv(cliente_dispatch_socket, &copDis, sizeof(op_code), 0)
					!= sizeof(op_code)) {
				log_info(logger, "Se ha finalizado la conexion con Dispatch");
				return;
			}

			if (validarOpCode(copInt)) {
				switch (copInt) {
									case DEBUGDOS:
										log_info(logger, "debug from interrupt");
										break;
							    	// Errores
									case -1:
										log_error(logger, "Cliente desconectado de %s...",
										server_interrupt_name);
									return;
									default:
						    			log_error(logger, "Algo anduvo mal en el server de %s",
						    					server_interrupt_name);
										log_info(logger, "Cop: %d", copInt);
									return;
								}
			}
			if (!validarOpCode(copDis)){
				switch (copDis) {
				case DEBUG:
					log_info(logger, "debug from dispatch");
					break;
					// Errores
					case -1:
						log_error(logger, "Cliente desconectado de %s...",
								server_dispatch_name);
						return;
						default:
							log_error(logger, "Algo anduvo mal en el server de %s",
									server_dispatch_name);
							log_info(logger, "Cop: %d", copDis);
							return;
				}
			}

			}
		log_warning(logger, "El cliente se desconecto de %s server DISPATCH",
				server_dispatch_name);
		log_warning(logger, "El cliente se desconecto de %s server INTERRUPT",
						server_interrupt_name);
		return;
}

int servers_escuchar(char* server_interrupt_name, int server_interrupt_socket, char* server_dispatch_name, int server_dispatch_socket) {
	int cliente_interrupt_socket = esperar_cliente(logger,server_interrupt_name, server_interrupt_socket);
	int cliente_dispatch_socket = esperar_cliente(logger, server_dispatch_name, server_dispatch_socket);

	if (cliente_interrupt_socket != -1 && cliente_dispatch_socket != -1) {
		t_procesar_conexiones_args* args = malloc(sizeof(t_procesar_conexiones_args));
		args->fd1 = cliente_interrupt_socket;
		args->server_name1 = server_interrupt_name;
        args->fd2 = cliente_dispatch_socket;
		args->server_name2 = server_dispatch_name;
		procesar_conexiones(args);
        return 1;
	}
	return 0;
}*/



/*typedef struct {
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

 *int servers_escuchar(char* server_interrupt_name, int server_interrupt_socket, char* server_dispatch_name, int server_dispatch_socket) {
 int cliente_interrupt_socket = esperar_cliente(logger, server_interrupt_name, server_interrupt_socket);
 int cliente_dispatch_socket = esperar_cliente(logger, server_dispatch_name, server_dispatch_socket);

 if (cliente_interrupt_socket != -1) {
 t_procesar_conexion_args* args = malloc(sizeof(t_procesar_conexion_args));
 args->fd = cliente_interrupt_socket;
 args->server_name = server_interrupt_name;
 procesar_conexion(args);

 }
 if (cliente_dispatch_socket != -1) {
 t_procesar_conexion_args* args = malloc(sizeof(t_procesar_conexion_args));
 args->fd = cliente_dispatch_socket;
 args->server_name = server_dispatch_name;
 procesar_conexion(args);
 return 1;
 }
 return 0;
 }*/

