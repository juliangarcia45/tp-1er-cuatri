/*
 * main.c
 *
 *  Created on: 19 abr. 2022
 *      Author: utnso
 */
#include "main.h"

int main(int argc, char** argv[]){
	int kernel_fd;
	cargarConfiguracion();
	generar_conexion(&kernel_fd, configuracion);

	int a;
	//argv[1] = "/home/utnso/Escritorio/Tp kiss/tp-2022-1c-Grupo-52/consolaInstrucciones.txt";
	//argv[2] = "555";
	// Parseo del archivo y armado de lista
	t_list* listaInstrucciones = list_create();
	parseo_archivo(argv[1],listaInstrucciones);

	// Enviar listaInstrucciones y atoi(argv[2])
	//printf("Parametro a envia con LISTA: %d \n", atoi(argv[2]));
	// enviarLista(lista, tamanioProceso);
	int tam = atoi(argv[2]);
	printf("Parametro a envia con LISTA: %d \n", tam);

 	enviar_instrucciones(kernel_fd, listaInstrucciones,tam);


 	log_info(logger, "Se realizo el envio se desconecto del kernel");
 	limpiarConfiguracion();
}


void parseo_archivo(char** path, t_list* listaInstrucciones)
{
	int i=0;

	FILE* pseudocode;
	//printf("Path: %s \n", argv[1]);
	//printf("Parametro a envia con LISTA: %d \n", atoi(argv[2]));

	pseudocode = fopen(path,"r");   		  // ABRO MODO Lectura
	char bufer[LONGITUD_MAXIMA_LINEA];		  // Genero buffer

	if(!pseudocode){
		printf("No se pudo acceder al archivo\n");
		return ;
	}

	char **linea;
	char *separador = " ";

	//t_list* listaInstrucciones = list_create();

	while(fgets(bufer, LONGITUD_MAXIMA_LINEA, pseudocode))
	{
		// ACA IMPRIMO CONTENIDO DE CADA LINEA
		linea =  string_split(bufer, separador);

		INSTRUCCIONES *instrucs;

		instrucs = (INSTRUCCIONES*)malloc(sizeof(INSTRUCCIONES));

		if(!instrucs){
				printf("No se ha podido reservar memoria.\n");
				exit(1);
		}
		//instrucs->comando = malloc(sizeof(instrucs->comando));
		instrucs->parametro=0;
		instrucs->parametro2=0;

		for(i = 0; linea[i] != '\0'; i++)
		{
			if( i == 0  )					//==>  1ra posicion
			{
				strcpy(instrucs->comando,linea[i]);
			}

			if( i == 1  ){					//==>  2da posicion   si no es null se mete el dato en la variable
				instrucs->parametro = atoi(linea[i]);
			}
			if( i == 2  ){					//==>  2da posicion  si no es null se mete el dato en la variable
				instrucs->parametro2 = atoi(linea[i]);
			}
		}

	list_add(listaInstrucciones,instrucs);

	}
}

