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

	free(stream);
	free(buffer->stream);
	free(buffer);
	free(a_enviar);
}

void* serializar_instrucciones_tam(int size, t_list* lista, int tamanioProceso) {

    t_list_iterator* listaIns = list_iterator_create(lista);
    INSTRUCCIONES* aux = list_get(lista, 0);

    aux = list_get(lista,0);

    int offset = 0;
    void* stream = malloc(size);

    while(list_iterator_has_next(listaIns)){
    	memcpy(stream + offset, &aux->comando, sizeof(aux->comando));
    	offset += sizeof(aux->comando);
        memcpy(stream + offset, &aux->parametro, sizeof(int));
        offset += sizeof(int);
        memcpy(stream + offset, &aux->parametro2, sizeof(int));
        offset += sizeof(int);

    	aux = list_iterator_next(listaIns);
        list_iterator_next(listaIns);
    }
    memcpy(stream + offset, &tamanioProceso, sizeof(int));

    free(listaIns);
    free(aux);
    return stream;
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
	size += sizeof(int);
	free(listaIns);
	free(aux);
	return size;
}

/*
void* deserializar_instrucciones(t_mensaje mensaje, int socket_fd){
	int size = sizeof(t_mensaje);

    t_list_iterator* listaIns=list_iterator_create(mensaje.listaInstrucciones);
    INSTRUCCIONES* aux=list_get(listaIns, 0);

    aux=list_get(listaIns,0);

    int offset = 0;
    void* stream = malloc(*size);

    while(list_iterator_has_next(listaIns)){
    	memcpy(aux->comando, stream, sizeof(aux->comando));
    	stream += sizeof(aux->comando);
        memcpy(aux->parametro,stream , sizeof(int));
        stream += sizeof(int);
        memcpy(aux->parametro2, stream, sizeof(int));
        stream += sizeof(int);

    	aux = list_iterator_next(listaIns);
        list_iterator_next(listaIns);
    }
    memcpy(mensaje.tamanioProceso, stream, sizeof(int));

}*/

/* CONTINUAR ACA */
/*
void recibir_mensaje(int socket_fd, t_buffer* buffer )
{
	recv(socket_fd, &(buffer->size), sizeof(int), 0);
	recv(socket_fd, &(buffer->stream), buffer->size, 0);

	t_mensaje* mensaje = malloc(sizeof(t_mensaje));
	//mensaje->listaInstrucciones->head->data->
	void* stream = malloc(buffer->stream);

	//t_link_element* aux = listaInstrucciones->head;
	t_link_element* aux  = mensaje->listaInstrucciones->head;


	while(list_iterator_has_next(buffer->stream))
	{
		INSTRUCCIONES* aux2 = aux->data;

		memcpy(aux->comando, stream, sizeof(aux->comando));
		stream += sizeof(aux->comando);
		memcpy(aux->parametro,stream , sizeof(int));
		stream += sizeof(int);
		memcpy(aux->parametro2, stream, sizeof(int));
		stream += sizeof(int);

		aux = list_iterator_next(listaIns);
		list_iterator_next(listaIns);
	}
	memcpy(mensaje.tamanioProceso, stream, sizeof(int));


}*/

/*
static void* serializar_instrucciones_tam(size_t* size, t_list* lista, int tamanioProceso) {

	t_link_element* aux = lista->head;
	INSTRUCCIONES* aux2 = aux;

	*size = (2*sizeof(int)+strlen(aux2->))+1)*list_size(lista) + sizeof(int); // 2 uint8_t por cada elemento
    void* stream = malloc(*size);

    // serializo los elementos
    t_list_iterator* list_it = list_iterator_create(lista);
    for (int i=0; list_iterator_has_next(list_it); i+=3){
    	INSTRUCCIONES* listInstrucciones = list_iterator_next(list_it);
        memcpy(stream+(i+0)*strlen(listInstrucciones->comando)+1, &listInstrucciones->comando,  strlen(listInstrucciones->comando) + 1);
        memcpy(stream+(i+1)*sizeof(int), &listInstrucciones->parametro, sizeof(int));
        memcpy(stream+(i+3)*sizeof(int), &listInstrucciones->parametro2, sizeof(int));
    }
    memcpy(stream + sizeof(int), &tamanioProceso, sizeof(int));
    list_iterator_destroy(list_it);
    return stream;
}*/

/*
static t_list* deserializar_t_list_posiciones(void* stream, uint8_t n_elements) {
    t_list* lista = list_create();

    // De-serializo y los meto en la lista
    for (uint8_t i=0; n_elements>0; i+=2, n_elements--) {
        t_posicion* pos = malloc(sizeof(t_posicion));
        memcpy(&pos->x, stream+(i+0)*sizeof(uint8_t), sizeof(uint8_t));
        memcpy(&pos->y, stream+(i+1)*sizeof(uint8_t), sizeof(uint8_t));
        list_add(lista, pos);
    }
    return lista;
}*/
