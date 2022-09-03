#include <stdio.h>

void ingreso_por_archivo (char*);

int main () 
{
	int menu;
	char archivo [20];


	printf("\n\n..:BIENVENIDE AL PROGRAMA DE AUTOMATAS:..\n");
	printf(" 1) si quiere ingresar la cadena por linea de comandos\n 2) si lo que deasea es ingresar la cadena a traves de un archivo txt \n");
	
	printf("Escriba una opcion: ");
	scanf ("%d", &menu);

	switch (menu){
		case 1 :
			//logica linea de comando
			break;
		case 2 : 
			printf("Ingrese el nombre del archivo (ej: entrada.txt): ");
			scanf ("%s", archivo);

			ingreso_por_archivo(archivo);
			break;
		default:
			printf ("No ingreso una opcion valida \n");
	}
}

void ingreso_por_archivo (char* archivo) {
	printf("el nombre del archivo es: %s", archivo);
	//FILE *f_entrada = fopen(archivo,"r");
}