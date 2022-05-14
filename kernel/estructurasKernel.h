/*
 * estructurasKernel.h
 *
 *  Created on: 13 may. 2022
 *      Author: utnso
 */

#ifndef ESTRUCTURASKERNEL_H_
#define ESTRUCTURASKERNEL_H_

#include <stdint.h>
#include <string.h>
#include <pthread.h>
#include <inttypes.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>
#include "protocolo.h"
#include "socket.h"
#include "estructuras.h"
#include "kernelConfig.h"

void crear_pcb(t_mensaje* mensaje);



#endif /* ESTRUCTURASKERNEL_H_ */
