/*
 * main.c
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */
#include "main.h"

int main(){
	cargarConfiguracion();
	char* puerto = string_itoa(configuracion->PUERTO_ESCUCHA);
	//CLIENTE

	generar_conexiones(&interrupt_fd, &dispatch_fd, configuracion);

	//MENSAJES DE PRUEBA A CPU
	//send_debug(interrupt_fd);
	//send_debug(dispatch_fd);


	//INICIO SERVIDOR
	kernelServer= iniciar_servidor(logger,"kernel server","127.0.0.1",puerto);
	free(puerto);
	while (server_escuchar("KERNEL_SV", kernelServer));

	limpiarConfiguracion();
	return 0;

}
