/*
 * consolaConfig.h
 *
 *  Created on: 19 abr. 2022
 *      Author: utnso
 */

#ifndef CONSOLACONFIG_H_
#define CONSOLACONFIG_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "commons/log.h"
#include "commons/config.h"

typedef struct {
	char* IP_KERNEL;
	uint32_t PUERTO_KERNEL;
} t_config_consola;

t_config_consola * configuracion;
t_config * fd_configuracion;
t_log * logger;

int cargarConfiguracion();



#endif /* CONSOLACONFIG_H_ */
