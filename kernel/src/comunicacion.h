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
#include "protocolo.h"
#include "socket.h"
#include "kernelConfig.h"

int server_escuchar(char* server_name, int server_socket);

#endif /* COMUNICACION_H_ */
