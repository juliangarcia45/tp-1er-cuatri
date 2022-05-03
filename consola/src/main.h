/*
 * main.h
 *
 *  Created on: 19 abr. 2022
 *      Author: utnso
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/config.h>
#include <commons/string.h>
#include <commons/collections/list.h>
#include "socket.h"
#include "protocolo.h"
#include "consolaConfig.h"
#include "estructuras.h"


#define LONGITUD_MAXIMA_LINEA 30   // Para el archivo a leer

t_list* parseo_archivo(char** path);


#endif /* MAIN_H_ */
