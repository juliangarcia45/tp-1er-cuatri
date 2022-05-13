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

typedef enum {
    DEBUG = 69,
	NO_OP,
    I_O,
    READ,
    WRITE,
    COPY,
    EXIT
} op_code;

bool send_debug(int fd);
//bool send_debug_interrupt(int fd);
//bool validarOpCode(op_code cod);


#endif /* SRC_PROTOCOLO_H_ */
