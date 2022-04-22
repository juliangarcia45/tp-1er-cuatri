/*
 * kernelConfig.h
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */

#ifndef KERNELCONFIG_H_
#define KERNELCONFIG_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "commons/log.h"
#include "commons/config.h"

typedef struct {
	char* IP_MEMORIA;
	uint32_t PUERTO_MEMORIA;
	char* IP_CPU;
	uint32_t PUERTO_CPU_DISPATCH;
    uint32_t PUERTO_CPU_INTERRUPT;
	uint32_t PUERTO_ESCUCHA;
	char* ALGORITMO_PLANIFICACION;
	uint32_t ESTIMACION_INICIAL;
	uint32_t ALFA;
	uint32_t GRADO_MULTIPROGRAMACION;
	uint32_t TIEMPO_MAXIMO_BLOQUEADO;
} t_config_kernel;

t_config_kernel * configuracion;
t_config * fd_configuracion;
t_log * logger;

int cargarConfiguracion();


#endif /* KERNELCONFIG_H_ */
