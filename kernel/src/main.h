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
#include "kernelConfig.h"
#include "comunicacion.h"

int kernelServer;
int interrupt_fd, dispatch_fd;

#endif /* MAIN_H_ */
