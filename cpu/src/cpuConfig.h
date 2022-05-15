/*
 * cpuConfig.h
 *
 *  Created on: 23 abr. 2022
 *      Author: utnso
 */

#ifndef CPUCONFIG_H_
#define CPUCONFIG_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "commons/log.h"
#include "commons/config.h"

typedef struct {
	uint32_t ENTRADAS_TLB;
	char* REEMPLAZO_TLB;
	uint32_t RETARDO_NOOP;
	char* IP_MEMORIA;
	uint32_t PUERTO_MEMORIA;
	uint32_t PUERTO_ESCUCHA_DISPATCH;
	uint32_t PUERTO_ESCUCHA_INTERRUPT;
} t_config_cpu;

t_config_cpu * configuracion;
t_config * fd_configuracion;
t_log * logger;

int cargarConfiguracion();


#endif /* CPUCONFIG_H_ */
