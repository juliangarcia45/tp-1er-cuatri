/*
 * estructuras.h
 *
 *  Created on: 30 abr. 2022
 *      Author: utnso
 */

#ifndef SRC_ESTRUCTURAS_H_
#define SRC_ESTRUCTURAS_H_

typedef struct instrucciones{
	char comando[32];
	int parametro;
	int parametro2;
}INSTRUCCIONES;

typedef enum{
	NEW,
	READY,
	EXEC,
	BLOCKED,
	SUSP_R,
	SUSP_B,
	FINISHED,
}t_status;

typedef struct pcb{
	int id_pcb;
	int size;
	t_list* instrucciones;
	t_status estado;
	int program_counter;
	int tabla_paginas;
	float estimacion_rafaga;
}PCB;



#endif /* SRC_ESTRUCTURAS_H_ */
