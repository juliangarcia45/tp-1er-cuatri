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
    char* puertoDispatch = string_itoa(configuracion->PUERTO_ESCUCHA_DISPATCH);
	//INICIO SERVIDORES
	cpuServerInterrupt = iniciar_servidor(logger,"interrupt server","127.0.0.1",puertoInterrupt);
    cpuServerDispatch = iniciar_servidor(logger,"dispatch server","127.0.0.1",puertoDispatch);
	free(puertoInterrupt);
    free(puertoDispatch);
	while (servers_escuchar("INTERRUPT_SV", cpuServerInterrupt,"DISPATCH_SV", cpuServerDispatch));

	limpiarConfiguracion();
	return 0;

}
