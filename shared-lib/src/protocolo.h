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
	NO_OP
} op_code;






bool send_debug(int fd);
static void* serializar_instrucciones_tam(size_t* size, INSTRUCCIONES* lista, int tamanioProceso);

#endif /* SRC_PROTOCOLO_H_ */
