/*
 * consolaConfig.c
 *
 *  Created on: 19 abr. 2022
 *      Author: utnso
 */
#include "consolaConfig.h"

int configValida(t_config* fd_configuracion) {
	return (config_has_property(fd_configuracion, "IP_KERNEL")
		&& config_has_property(fd_configuracion, "PUERTO_KERNEL"));
}

int cargarConfiguracion() {
	logger = log_create("LogConsola", "Consola", 1, LOG_LEVEL_INFO);
	configuracion = malloc(sizeof(t_config_consola));

	fd_configuracion = config_create("consola.conf");
	if (fd_configuracion == NULL) {
		fd_configuracion = config_create("consola.conf");
	}

	if (fd_configuracion == NULL || !configValida(fd_configuracion)) {
		log_error(logger,"Archivo de configuración inválido.");
		return -1;
	}

	configuracion->IP_KERNEL = config_get_string_value(fd_configuracion, "IP_KERNEL");
	configuracion->PUERTO_KERNEL = config_get_int_value(fd_configuracion, "PUERTO_KERNEL");

	log_info(logger,
		"\nIP_KERNEL: %s\n"
		"PUERTO_KERNEL: %d\n",
		configuracion->IP_KERNEL,
		configuracion->PUERTO_KERNEL);
	return 0;
}

void limpiarConfiguracion() {
	free(configuracion);
	config_destroy(fd_configuracion);
	log_destroy(logger);

}

