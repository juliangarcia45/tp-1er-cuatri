/*
 * manejoPcb.h
 *
 *  Created on: 19 jun. 2022
 *      Author: utnso
 */

#ifndef SRC_MANEJOPCB_H_
#define SRC_MANEJOPCB_H_

#include <stdint.h>
#include "comunicacion.h"
#include "protocolo.h"
#include "estructuras.h"

void procesar_pcb(PCB* pcb);
void envio_io(PCB*pcb,INSTRUCCIONES* instruccion);
#endif /* SRC_MANEJOPCB_H_ */
