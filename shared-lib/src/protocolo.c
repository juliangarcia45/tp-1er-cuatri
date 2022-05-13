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
	free(a_enviar);

}

t_mensaje* recibir_instrucciones(int socket_fd)
{
	t_buffer* buffer=malloc(sizeof(t_buffer));

	recv(socket_fd, &(buffer->size), sizeof(int), 0);
	buffer->stream=malloc(buffer->size);
	recv(socket_fd, buffer->stream, buffer->size, 0);

	t_mensaje* mensaje = deserializar_instrucciones(buffer);

	//free(buffer);

	return mensaje;
}

void* serializar_instrucciones_tam(int size, t_list* lista, int tamanioProceso) {

    t_list_iterator* listaIns = list_iterator_create(lista);
    INSTRUCCIONES* aux = list_get(lista, 0);

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

    free(listaIns);
    free(aux);
    return stream;
}

t_mensaje* deserializar_instrucciones(t_buffer* buffer){
    int i=0;
	t_mensaje* mensaje=malloc(sizeof(t_mensaje));

	void* stream = buffer->stream;

	memcpy(&(mensaje->elementosLista), stream, sizeof(int));
	stream += sizeof(int);

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
