/*
 * cpuConfig.c
 *
 *  Created on: 23 abr. 2022
 *      Author: utnso
 */

#include "cpuConfig.h"

int configValida(t_config* fd_configuracion) {
	return (config_has_property(fd_configuracion, "ENTRADAS_TLB")
		&& config_has_property(fd_configuracion, "REEMPLAZO_TLB")
		&& config_has_property(fd_configuracion, "RETARDO_NOOP")
		&& config_has_property(fd_configuracion, "IP_MEMORIA")
		&& config_has_property(fd_configuracion, "PUERTO_MEMORIA")
		&& config_has_property(fd_configuracion, "PUERTO_ESCUCHA_DISPATCH")
		&& config_has_property(fd_configuracion, "PUERTO_ESCUCHA_INTERRUPT"));
}

int cargarConfiguracion() {
	logger = log_create("LogCpu", "Cpu", 1, LOG_LEVEL_INFO);
	configuracion = malloc(sizeof(t_config_cpu));

	fd_configuracion = config_create("cpu.conf");
	if (fd_configuracion == NULL) {
		fd_configuracion = config_create("cpu.conf");
	}

	if (fd_configuracion == NULL || !configValida(fd_configuracion)) {
		log_error(logger,"Archivo de configuración inválido.");
		return -1;
	}

	configuracion->ENTRADAS_TLB = config_get_int_value(fd_configuracion, "ENTRADAS_TLB");
	configuracion->REEMPLAZO_TLB = config_get_string_value(fd_configuracion, "REEMPLAZO_TLB");
	configuracion->RETARDO_NOOP = config_get_int_value(fd_configuracion, "RETARDO_NOOP");
	configuracion->IP_MEMORIA = config_get_string_value(fd_configuracion, "IP_MEMORIA");
	configuracion->PUERTO_MEMORIA = config_get_int_value(fd_configuracion, "PUERTO_MEMORIA");
	configuracion->PUERTO_ESCUCHA_DISPATCH = config_get_int_value(fd_configuracion, "PUERTO_ESCUCHA_DISPATCH");
	configuracion->PUERTO_ESCUCHA_INTERRUPT = config_get_int_value(fd_configuracion, "PUERTO_ESCUCHA_INTERRUPT");


	log_info(logger,
		"\nENTRADAS_TLB: %d\n"
		"REEMPLAZO_TLB: %s\n"
		"RETARDO_NOOP: %d\n"
		"IP_MEMORIA: %s\n"
		"PUERTO_MEMORIA: %d\n"
	    "PUERTO_ESCUCHA_DISPATCH: %d\n"
		"PUERTO_ESCUCHA_INTERRUPT: %d\n",
		configuracion->ENTRADAS_TLB,
		configuracion->REEMPLAZO_TLB,
		configuracion->RETARDO_NOOP,
		configuracion->IP_MEMORIA,
		configuracion->PUERTO_MEMORIA,
		configuracion->PUERTO_ESCUCHA_DISPATCH,
		configuracion->PUERTO_ESCUCHA_INTERRUPT
		);
	return 0;
}

void limpiarConfiguracion() {
	free(configuracion);
	config_destroy(fd_configuracion);
	log_destroy(logger);

}

