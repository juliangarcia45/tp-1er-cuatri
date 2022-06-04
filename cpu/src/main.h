/*
 * main.h
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <commons/log.h>
#include <commons/config.h>
#include "socket.h"
#include "cpuConfig.h"
#include "protocolo.h"

int cpuServerInterrupt;
int cpuServerDispatch;

void dispatchCpu (void);
void interruptCpu (void);


#endif /* MAIN_H_ */
