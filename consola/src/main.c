/*
 * main.c
 *
 *  Created on: 19 abr. 2022
 *      Author: utnso
 */
#include "main.h"

int main(){
	int kernel_fd;
	cargarConfiguracion();
	generar_conexion(&kernel_fd, configuracion);

	int a;

    scanf("%d", &a);
	send_debug(kernel_fd);

	scanf("%d", &a);
	limpiarConfiguracion();



}


