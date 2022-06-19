/*
 * manejoPcb.c
 *
 *  Created on: 19 jun. 2022
 *      Author: utnso
 */

#include "manejoPcb.h"

void procesar_pcb(PCB* pcb) {
 while(pcb->program_counter<=pcb->instrucciones->elements_count){
	 INSTRUCCIONES* instruccion=list_get(pcb->instrucciones,pcb->program_counter);
	 if(strcmp(instruccion->comando,"NO_OP")){
		uint32_t i=0;
		while(i<instruccion->parametro){
	 	sleep(configuracion->RETARDO_NOOP);
	 	i++;
		}
	 }
	 else if(strcmp(instruccion->comando,"I/O")){
		 envio_io(pcb,instruccion);
	 }
	 else if(strcmp(instruccion->comando,"EXIT")){
		 enviar_pcb(cliente_socket,pcb);
	 }
	 else{log_info(logger,"xd");}
	 pcb->program_counter++;
 }
}

void envio_io(PCB*pcb,INSTRUCCIONES* instruccion){
	enviar_pcb(cliente_socket,pcb);
	enviar_tiempo_bloqueo(cliente_socket,instruccion->parametro);
}
