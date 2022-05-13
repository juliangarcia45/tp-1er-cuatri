/*
 * protocolo.c
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */
#include "protocolo.h"

// DEBUG
bool send_debug(int fd) {
    op_code cop = DEBUG;
    if (send(fd, &cop, sizeof(op_code), 0) != sizeof(op_code)){
        return false;
    }
    return true;
}

/*bool send_debug_interrupt(int fd) {
    op_code cop = DEBUGDOS;
    if (send(fd, &cop, sizeof(op_code), 0) != sizeof(op_code)){
        return false;
    }
    return true;
}

bool validarOpCode(op_code cod) {
	return (cod == DEBUGDOS || cod == I_O || cod == EXIT);
}*/
