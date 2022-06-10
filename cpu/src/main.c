/*
 * main.c
 *
 *  Created on: 23 abr. 2022
 *      Author: utnso
 */

#include "main.h"


int main(){
	cargarConfiguracion();
	char* puertoInterrupt = string_itoa(configuracion->PUERTO_ESCUCHA_INTERRUPT);
    char* puertoDispatch= malloc(sizeof(char));
	puertoDispatch = string_itoa(configuracion->PUERTO_ESCUCHA_DISPATCH);
	//INICIO SERVIDORES
	//cpuServerInterrupt = iniciar_servidor(logger,"interrupt server","127.0.0.1",puertoInterrupt);
    //cpuServerDispatch = iniciar_servidor(logger,"dispatch server","127.0.0.1",puertoDispatch);
	//free(puertoInterrupt);
    //free(puertoDispatch);
	//while (servers_escuchar("INTERRUPT_SV", cpuServerInterrupt,"DISPATCH_SV", cpuServerDispatch));

	pthread_t dispatch_id;
	//pthread_t interrupt_id;

	pthread_create(&dispatch_id,NULL,(void*) dispatchCpu,(void*) puertoDispatch);
	pthread_detach(dispatch_id);
	//pthread_create(&interrupt_id,NULL,(void*) interruptCpu,NULL);
	//pthread_detach(interrupt_id);


	limpiarConfiguracion();
	return 0;

}

void dispatchCpu(void* puerto) {

	//cargarConfiguracion();

	//char* puertoDispatch = string_itoa(configuracion->PUERTO_ESCUCHA_DISPATCH);

	cpuServerDispatch = iniciar_servidor(logger,"dispatch server","127.0.0.1",(char*) puerto);

	free(puerto);

	while(server_escuchar("DISPATCH_SV",cpuServerDispatch));

}

void interruptCpu() {

	//cargarConfiguracion();

	char* puertoInterrupt = string_itoa(configuracion->PUERTO_ESCUCHA_INTERRUPT);

	cpuServerInterrupt = iniciar_servidor(logger,"interrupt server","127.0.0.1",puertoInterrupt);

	free(puertoInterrupt);

	while(server_escuchar("INTERRUPT_SV",cpuServerInterrupt));
}
