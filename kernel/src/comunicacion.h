/*
 * comunicacion.h
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */

#ifndef COMUNICACION_H_
#define COMUNICACION_H_

#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <inttypes.h>
#include <commons/log.h>
#include <commons/config.h>
#include "main.h"
#include "protocolo.h"
#include "socket.h"
#include "kernelConfig.h"
#include "estructurasKernel.h"

PCB* pcb;

//SERVIDOR
int server_escuchar(char* server_name, int server_socket);
//CLIENTE
int generar_conexiones(int* interrupt_fd, int* dispatch_fd, t_config_kernel* configuracion);

#endif /* COMUNICACION_H_ */
