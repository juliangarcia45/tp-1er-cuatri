/*
 * estructurasKernel.c
 *
 *  Created on: 13 may. 2022
 *      Author: utnso
 */
#include "estructurasKernel.h"


static int PID = 1;

PCB* crear_pcb(t_mensaje* mensaje){
	PCB* pcb= malloc(sizeof(PCB));
	pcb->instrucciones=list_create();
	pcb->instrucciones=malloc(sizeof(mensaje->listaInstrucciones));
	pcb->id_pcb=PID;
	PID++;
	pcb->size=mensaje->tamanioProceso;
	list_add_all(pcb->instrucciones,mensaje->listaInstrucciones);
	pcb->estimacion_rafaga=0;
	pcb->program_counter=0;
	pcb->tabla_paginas=0;
	return pcb;
}
