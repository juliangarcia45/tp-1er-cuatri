/*
 * kernelConfig.c
 *
 *  Created on: 16 abr. 2022
 *      Author: utnso
 */

#include "kernelConfig.h"

int configValida(t_config* fd_configuracion) {
	return (config_has_property(fd_configuracion, "IP_MEMORIA")
		&& config_has_property(fd_configuracion, "PUERTO_MEMORIA")
		&& config_has_property(fd_configuracion, "IP_CPU")
		&& config_has_property(fd_configuracion, "PUERTO_CPU_DISPATCH")
		&& config_has_property(fd_configuracion, "PUERTO_CPU_INTERRUPT")
		&& config_has_property(fd_configuracion, "PUERTO_ESCUCHA")
		&& config_has_property(fd_configuracion, "ALGORITMO_PLANIFICACION")
		&& config_has_property(fd_configuracion, "ESTIMACION_INICIAL")
		&& config_has_property(fd_configuracion, "ALFA")
		&& config_has_property(fd_configuracion, "GRADO_MULTIPROGRAMACION")
		&& config_has_property(fd_configuracion, "TIEMPO_MAXIMO_BLOQUEADO"));
}

int cargarConfiguracion() {
	logger = log_create("LogKernel", "Kernel", 1, LOG_LEVEL_INFO);
	configuracion = malloc(sizeof(t_config_kernel));

	fd_configuracion = config_create("kernel.conf");
	if (fd_configuracion == NULL) {
		fd_configuracion = config_create("kernel.conf");
	}

	if (fd_configuracion == NULL || !configValida(fd_configuracion)) {
		log_error(logger,"Archivo de configuración inválido.");
		return -1;
	}

	configuracion->IP_MEMORIA = config_get_string_value(fd_configuracion, "IP_MEMORIA");
	configuracion->PUERTO_MEMORIA = config_get_int_value(fd_configuracion, "PUERTO_MEMORIA");
	configuracion->IP_CPU = config_get_string_value(fd_configuracion, "IP_CPU");
	configuracion->PUERTO_CPU_DISPATCH = config_get_int_value(fd_configuracion, "PUERTO_CPU_DISPATCH");
	configuracion->PUERTO_CPU_INTERRUPT = config_get_int_value(fd_configuracion, "PUERTO_CPU_INTERRUPT");
	configuracion->PUERTO_ESCUCHA = config_get_int_value(fd_configuracion, "PUERTO_ESCUCHA");
	configuracion->ALGORITMO_PLANIFICACION = config_get_string_value(fd_configuracion, "ALGORITMO_PLANIFICACION");
	configuracion->ESTIMACION_INICIAL = config_get_int_value(fd_configuracion, "ESTIMACION_INICIAL");
	configuracion->ALFA = config_get_int_value(fd_configuracion, "ALFA");
	configuracion->GRADO_MULTIPROGRAMACION = config_get_int_value(fd_configuracion, "GRADO_MULTIPROGRAMACION");
	configuracion->TIEMPO_MAXIMO_BLOQUEADO = config_get_int_value(fd_configuracion, "TIEMPO_MAXIMO_BLOQUEADO");




	log_info(logger,
		"\nIP_MEMORIA: %s\n"
		"PUERTO_MEMORIA: %d\n"
		"IP_CPU: %s\n"
		"PUERTO_CPU_DISPATCH: %d\n"
		"PUERTO_CPU_INTERRUPT: %d\n"
	    "PUERTO_ESCUCHA: %d\n"
		"ALGORITMO_PLANIFICACION: %s\n"
		"ESTIMACION_INICIAL: %d\n"
		"ALFA: %d\n"
		"GRADO_MULTIPROGRAMACION: %d\n"
		"TIEMPO_MAXIMO_BLOQUEADO: %d\n",
		configuracion->IP_MEMORIA,
		configuracion->PUERTO_MEMORIA,
		configuracion->IP_CPU,
		configuracion->PUERTO_CPU_DISPATCH,
		configuracion->PUERTO_CPU_INTERRUPT,
		configuracion->PUERTO_ESCUCHA,
		configuracion->ALGORITMO_PLANIFICACION,
		configuracion->ESTIMACION_INICIAL,
		configuracion->ALFA,
		configuracion->GRADO_MULTIPROGRAMACION,
		configuracion->TIEMPO_MAXIMO_BLOQUEADO);
	return 0;
}

void limpiarConfiguracion() {
	free(configuracion);
	config_destroy(fd_configuracion);
	log_destroy(logger);

}
