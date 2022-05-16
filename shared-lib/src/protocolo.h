/*
 * protocolo.h
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */

#ifndef SRC_PROTOCOLO_H_
#define SRC_PROTOCOLO_H_

#include <inttypes.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <commons/collections/list.h>
#include "estructuras.h"

typedef enum {
    DEBUG = 69,
	NO_OP,
    I_O,
    READ,
    WRITE,
    COPY,
    EXIT,
    DISPATCH,
    INTERRUPT
} op_code;

typedef struct{
	int elementosLista;
	t_list* listaInstrucciones;
	int tamanioProceso;
} t_mensaje;

typedef struct {
    int size; // Tamaño del payload
    void* stream; // Payload
} t_buffer;

typedef struct {
    int op_code;
    t_buffer* buffer;
} t_paquete;



bool send_debug(int fd);
//INSTRUCCIONES CONSOLA-KERNEL
static void* serializar_instrucciones_tam(int size, t_list* lista, int tamanioProceso);
t_mensaje* deserializar_instrucciones(t_buffer* buffer);
void enviar_instrucciones(int socket_fd, int size, t_list* lista, int tamanioProceso );
t_mensaje* recibir_instrucciones(int socket_fd);
int calcular_buffer_size(t_list* lista);
//PCB KERNEL-CPU
void* serializar_pcb(PCB* pcb);
PCB* deserializar_pcb(t_paquete* paquete_pcb);
void enviar_pcb(int socket_fd, PCB* pcb );
PCB* recibir_pcb(int socket_fd);
int calcular_pcb_size(PCB* pcb);
//bool send_debug_interrupt(int fd);
//bool validarOpCode(op_code cod);

#endif /* SRC_PROTOCOLO_H_ */
