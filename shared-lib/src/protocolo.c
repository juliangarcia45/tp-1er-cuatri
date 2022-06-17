/*
 * protocolo.c
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */
#include "protocolo.h"

// DEBUG
bool send_debug(int fd) {
    op_code cop = DEBUG;
    if (send(fd, &cop, sizeof(op_code), 0) != sizeof(op_code)){
        return false;
    }
    return true;
}

/*bool send_debug_interrupt(int fd) {
    op_code cop = DEBUGDOS;
    if (send(fd, &cop, sizeof(op_code), 0) != sizeof(op_code)){
        return false;
    }
    return true;
}

bool validarOpCode(op_code cod) {
	return (cod == DEBUGDOS || cod == I_O || cod == EXIT);
}*/

//INSTRUCCIONES CONSOLA A KERNEL
void enviar_instrucciones(int socket_fd, int size, t_list* lista, int tamanioProceso ){

	size = calcular_buffer_size(lista);
	void* stream = serializar_instrucciones_tam(size, lista, tamanioProceso);
	t_buffer* buffer=malloc(size);
	buffer->size=size;
	buffer->stream=stream;

	void* a_enviar=malloc(buffer->size+sizeof(int));
	int offset=0;

	memcpy(a_enviar + offset, &(buffer->size), sizeof(int));
	offset += sizeof(int);
	memcpy(a_enviar + offset, buffer->stream, buffer->size);

	send(socket_fd, a_enviar,buffer->size+sizeof(int) ,0);

    free(buffer);
    //free(stream);
	free(a_enviar);

}

t_mensaje* recibir_instrucciones(int socket_fd)
{
	t_buffer* buffer=malloc(sizeof(t_buffer));

	recv(socket_fd, &(buffer->size), sizeof(int), 0);
	buffer->stream=malloc(buffer->size);
	recv(socket_fd, buffer->stream, buffer->size, 0);

	t_mensaje* mensaje = deserializar_instrucciones(buffer);

	//free(buffer->stream);


	return mensaje;
}

void* serializar_instrucciones_tam(int size, t_list* lista, int tamanioProceso) {

    INSTRUCCIONES* aux;

    aux = list_get(lista,0);
    int elementosLista= list_size(lista);

    int offset = 0;
    void* stream = malloc(size);

    memcpy(stream + offset, &elementosLista, sizeof(int));
    offset+= sizeof(int);

    t_link_element* aux1 = lista->head;

    //TODO
    // UNICO ERROR ==> En el comando COPY llega con basura y se pasa bien con esa basura
   while( aux1!=NULL )
	{
		INSTRUCCIONES* auxl2 = aux1->data;
		printf("Verificamos la lista:\n");
		printf("Comando: %s | Par1: %d | Par2: %d \n\n", auxl2->comando, auxl2->parametro, auxl2->parametro2 );

		memcpy(stream + offset, &auxl2->comando, sizeof(aux->comando));
		offset += sizeof(aux->comando);
		memcpy(stream + offset, &auxl2->parametro, sizeof(int));
		offset += sizeof(int);
		memcpy(stream + offset, &auxl2->parametro2, sizeof(int));
		offset += sizeof(int);
		aux1 = aux1->next;
	}
    memcpy(stream + offset, &tamanioProceso, sizeof(int));

    free(aux);
    return stream;
}

t_mensaje* deserializar_instrucciones(t_buffer* buffer){
    int i=0;
	t_mensaje* mensaje=malloc(sizeof(t_mensaje));


	void* stream = buffer->stream;

	memcpy(&(mensaje->elementosLista), stream, sizeof(int));
	stream += sizeof(int);

	mensaje->listaInstrucciones=malloc(mensaje->elementosLista*sizeof(char[32]));
	while(i!=mensaje->elementosLista)
	{
		INSTRUCCIONES* aux=malloc(sizeof(INSTRUCCIONES));
		memcpy(&(aux->comando), stream, sizeof(aux->comando));
	    stream += sizeof(aux->comando);
	    memcpy(&(aux->parametro),stream , sizeof(int));
	    stream += sizeof(int);
	    memcpy(&(aux->parametro2), stream, sizeof(int));
	    stream += sizeof(int);

	    list_add(mensaje->listaInstrucciones,aux);
	    i++;
	}

	memcpy(&(mensaje->tamanioProceso), stream, sizeof(int));

	free(buffer);

	return mensaje;
}

int calcular_buffer_size(t_list* lista){
	int size;
	t_list_iterator* listaIns = list_iterator_create(lista);
	INSTRUCCIONES* aux = list_get(lista, 0);

	while(list_iterator_has_next(listaIns)){
		size += 2*sizeof(int) + strlen(aux->comando) + 1;
		aux = list_iterator_next(listaIns);
		list_iterator_next(listaIns);
	}
	size += 2*sizeof(int);
	free(listaIns);
	free(aux);
	return size;
}

//SERIALIZAR PCB
void enviar_pcb(int socket_fd, PCB* pcb ){

	int size=calcular_pcb_size(pcb);
	int sizeBuffer=size+sizeof(int);
	int sizePaquete=sizeBuffer+sizeof(int);
	void* stream = serializar_pcb(pcb, size);
	t_buffer* buffer=malloc(sizeBuffer); //ROMPE ACA EL MALLOC
	t_paquete* paquete_pcb= malloc(sizePaquete);
	buffer->size=size;
	buffer->stream=stream;

	paquete_pcb->buffer=buffer;
    paquete_pcb->op_code=DISPATCH;

	void* a_enviar=malloc(sizePaquete);
	int offset=0;

	memcpy(a_enviar + offset, &(paquete_pcb->op_code), sizeof(int));
	offset += sizeof(int);
	memcpy(a_enviar + offset, &(paquete_pcb->buffer->size), sizeof(int));
	offset += sizeof(int);
	memcpy(a_enviar + offset, paquete_pcb->buffer->stream, paquete_pcb->buffer->size);


	send(socket_fd, a_enviar,sizePaquete ,0);

	free(a_enviar);
	free(paquete_pcb->buffer->stream);
	free(paquete_pcb->buffer);
	free(paquete_pcb);

}

PCB* recibir_pcb(int socket_fd)
{
	t_buffer* paquete_pcb = malloc(sizeof(t_buffer));


	//recv(socket_fd, &(paquete_pcb->op_code), sizeof(int), 0);

	recv(socket_fd, &(paquete_pcb->size), sizeof(int), 0);
	paquete_pcb->stream = malloc(paquete_pcb->size);
	recv(socket_fd, paquete_pcb->stream, paquete_pcb->size, 0);

	PCB* pcb = deserializar_pcb(paquete_pcb);

	//free(buffer);

	return pcb;
}

void* serializar_pcb(PCB* pcb, int size) {
    INSTRUCCIONES* aux;

    aux = list_get(pcb->instrucciones,0);
    int elementosLista= list_size(pcb->instrucciones);

    int offset = 0;
    void* stream = malloc(size);

    memcpy(stream + offset, &elementosLista, sizeof(int));
    offset+= sizeof(int);
    memcpy(stream + offset, &pcb->id_pcb, sizeof(int));
    offset+= sizeof(int);
    memcpy(stream + offset, &pcb->size, sizeof(int));
    offset+= sizeof(int);

    t_link_element* aux1 = pcb->instrucciones->head;
    //TODO
    // UNICO ERROR ==> En el comando COPY llega con basura y se pasa bien con esa basura
   while( aux1!=NULL )
	{
		INSTRUCCIONES* auxl2 = aux1->data;
		printf("Verificamos la lista:\n");
		printf("Comando: %s | Par1: %d | Par2: %d \n\n", auxl2->comando, auxl2->parametro, auxl2->parametro2 );

		memcpy(stream + offset, &auxl2->comando, 32);
		offset += 32;
		memcpy(stream + offset, &auxl2->parametro, sizeof(int));
		offset += sizeof(int);
		memcpy(stream + offset, &auxl2->parametro2, sizeof(int));
		offset += sizeof(int);
		aux1 = aux1->next;
	}
    memcpy(stream + offset, &pcb->program_counter, sizeof(int));
    offset+= sizeof(int);
    memcpy(stream + offset, &pcb->tabla_paginas, sizeof(int));
    offset+= sizeof(int);
    memcpy(stream + offset, &pcb->estimacion_rafaga, sizeof(float));

    free(aux);
    free(aux1);
    return stream;
}

PCB* deserializar_pcb(t_buffer* buffer){
    int i=0;
	PCB* pcb=malloc(sizeof(PCB));
	int* elementosLista=malloc(sizeof(int));

	void* stream = buffer->stream;

	memcpy(elementosLista, stream, sizeof(int));
	stream += sizeof(int);

	memcpy(&(pcb->id_pcb), stream, sizeof(int));
	stream += sizeof(int);
	memcpy(&(pcb->size), stream, sizeof(int));
	stream += sizeof(int);

	pcb->instrucciones=list_create();
	while(i!=(*elementosLista))
	{
		INSTRUCCIONES* aux=malloc(sizeof(INSTRUCCIONES));
		memcpy(&(aux->comando), stream, sizeof(aux->comando));
	    stream += sizeof(aux->comando);
	    memcpy(&(aux->parametro),stream , sizeof(int));
	    stream += sizeof(int);
	    memcpy(&(aux->parametro2), stream, sizeof(int));
	    stream += sizeof(int);

	    list_add(pcb->instrucciones,aux);
	    i++;
	}

	memcpy(&(pcb->program_counter), stream, sizeof(int));
	stream += sizeof(int);
	memcpy(&(pcb->tabla_paginas), stream, sizeof(int));
	stream += sizeof(int);
	memcpy(&(pcb->estimacion_rafaga), stream, sizeof(float));

	free(buffer);

	return pcb;
}

int calcular_pcb_size(PCB* pcb){
	int size=0;
	int i =0;

	while(i!=pcb->instrucciones->elements_count){
		size += 2*sizeof(int) + 32;
		i++;
	}
	size += 5*sizeof(int)+sizeof(float);

	return size;
}

