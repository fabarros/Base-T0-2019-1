/* Módulo a cargo de la visualización del programa */
#include "../watcher/watcher.h"
/* Módulo estándar de Input / Output */
#include <stdio.h>
/* Módulo estándar de C, para uso de memoria en el Heap*/
#include <stdlib.h>
/* Módulo estándar de números enteros */
#include <stdint.h>
/* Módulo estándar de Unix, para hacer pausas en el programa */
#include <unistd.h>

int main(int argument_count, char** arguments)
{
	if (argument_count != 3)
	{
		printf("Modo de uso: %s <estado inicial> <generaciones>\n\n", arguments[0]);
		printf("\testado inicial: archivo de texto plano que contiene la descripción inicial de la comunidad bacteriana\n\n");
		printf("\tgeneraciones: número de generaciones totales que deberán simularse\n");
		return 1;
	}

	/* El primer parametro es el nombre del archivo */
	char* filename = arguments[1];

	/* El segundo parametro es la cantidad de generaciones a simular */
	uint32_t generation_count = atoi(arguments[2]);
	printf("Debemos calcular %d generaciones\n", generation_count);

	/* Abrimos el archivo y creamos el stream de lectura */
	FILE* file = fopen(filename, "r");

	/* Las variables donde guardaremos el alto y ancho */
	uint8_t height, width;
	/* Leemos el alto y el ancho */
	fscanf(file, "%hhu %hhu", &height, &width);
	/* Abrimos la ventana con las dimensiones dadas */
	watcher_open(height, width);

	/* Variable donde iremos guardando lo que leamos del archivo */
	uint8_t value;

	/* Para cada fila */
	for(uint8_t row = 0; row < height; row++)
	{
		/* Para cada columna */
		for(uint8_t col = 0; col < width; col++)
		{
			/* Leemos un valor */
			fscanf(file, "%hhu", &value);
			/* Y lo ponemos en la ventana en la posición correspondiente */
			watcher_set_cell(row, col, value);
		}
	}

	/* Cerramos el archivo una vez que lo terminamos de leer */
	fclose(file);

	/* Hacemos efectivos los cambios de la ventana, mostrando el estado inicial */
	watcher_refresh();

	/* Pausamos el programa por 5 segundos para que se pueda ver la ventana */
	// OJO: EL CÓDIGO QUE ENTREGUES NO DEBE TENER SLEEPS
	sleep(5);

	/* Este sleep es en microsegundos, util para separar las generaciones */
	usleep(5000);

	/* Cerramos la ventana */
	watcher_close();

	return 0;
}
