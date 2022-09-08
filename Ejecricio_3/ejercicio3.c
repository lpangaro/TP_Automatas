/* Para compilar: gcc -c -o ejercicio3.o ejercicio3.c -Wall
 * Para linkear: gcc -o ejercicio3 ejercicio3.o -Wall
 * Para correr: ./ejercicio3
 */

#include<stdio.h>
#include<string.h>


int isoperator(char);
int validar_vector (char *);
void separo_operadores (char *);

int main(){

    int menu;
    char archivo [20];
    char vector_operacion [1000];
    FILE *f_salida = fopen ("salida.txt", "w");    

    printf("\n\n..:BIENVENIDE AL PROGRAMA DE AUTOMATAS:..\n");
    printf(" 1) si quiere ingresar la cadena por linea de comandos\n 2) si lo que deasea es ingresar la cadena a traves de un archivo txt \n");
    
    printf("Escriba una opcion: ");
    scanf ("%d", &menu);
    system("clear");

    switch (menu){
        case 1 :
            printf("Ingrese la cadena de caracteres numericos (Hexadecimales, Ocatales o Decimales): ");
            scanf ("%s", vector_operacion);
            break;
        case 2 : 
            printf("Ingrese el nombre del archivo (ej: entrada.txt): ");
            scanf ("%s", archivo);
            ingreso_por_archivo(archivo, vector_operacion);
            break;
        default:
            printf ("No ingreso una opcion valida \n");
    }
    
    if (validar_vector(vector_operacion)){


        separo_operadores(vector_operacion);


    }
    
    fclose (f_salida);
    return 0;
}


int validar_vector(char* vector_operacion) {

    int i = 0;

    while (vector_operacion[i] != '\0') {
        if(isdigit(vector_operacion[i]) || isoperator(vector_operacion[i])) {
            i++;
        }
        else 
             return 1;
    }
    return 0;

}

bool isoperator (char c){
    if (strcmp(c, "+") == 0 || strcmp(c, "-") == 0 || strcmp(c, "*") == 0)
        return 0;
    return 1;
}

void ingreso_por_archivo (char* archivo, char* vector_operacion) {
    int i = 0;
    FILE *f_entrada = fopen(archivo,"r");

    if(f_entrada == NULL){   
        printf("Error en la apertura del archivo.\n");
    }

    else {
        fread(&vector_operacion[i], sizeof(char), 1, f_entrada);   //primer elemento

        while(!feof(f_entrada)) {
            i++;
            fread(&vector_operacion[i], sizeof(char), 1, f_entrada);      //LECTURA DEL ARCHIVO, GUARDO ELEMENTOS DE ENTRADA EN EL VECTOR.
        }
    }

    fclose (f_entrada);
}