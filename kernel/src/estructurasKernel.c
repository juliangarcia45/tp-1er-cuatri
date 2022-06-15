/*
 * estructurasKernel.c
 *
 *  Created on: 13 may. 2022
 *      Author: utnso
 */
#include "estructurasKernel.h"


static int PID = 1;

PCB* crear_pcb(t_mensaje* mensaje){
	PCB* pcb=malloc(sizeof(PCB));
	pcb->id_pcb=PID;
	PID++;
	pcb->size=mensaje->tamanioProceso;
	t_link_element* aux1 = mensaje->listaInstrucciones->head;
	pcb->instrucciones=malloc(mensaje->elementosLista*sizeof(INSTRUCCIONES));
	while(aux1!=NULL)
		{
		    INSTRUCCIONES* auxl2 = aux1->data;
		    list_add(pcb->instrucciones,auxl2);
		    //t_link_element* auxsad = pcb->instrucciones->head;
		    //INSTRUCCIONES* auxl3 = auxsad->data;
		    //printf("Comando de pcb: %s | Par1: %d | Par2: %d \n\n",auxl3->comando , auxl3->parametro, auxl3->parametro2 );
		    aux1 = aux1->next;
		    //auxsad=auxsad->next;
		}
	pcb->estimacion_rafaga=0;
	pcb->program_counter=0;
	pcb->tabla_paginas=0;
	return pcb;
}
