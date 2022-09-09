/* Para compilar: gcc -c -o ejercicio3.o ejercicio3.c -Wall
 * Para linkear: gcc -o ejercicio3 ejercicio3.o -Wall
 * Para correr: ./ejercicio3
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

#define diferenciaASCII 48
 
typedef struct t_nodo 
{
   int info;
   struct t_nodo *sig;
} nodo;
 
typedef nodo* ptr_nodo;
 

 //Prototipos de Funciones
void Push(ptr_nodo* pila, int info);
int Pop(ptr_nodo* pila);
int isoperator(char);
int validar_vector (char *);
int my_atoi(char* string);
void ingreso_por_archivo (char* archivo, char* vector_operacion);
int calcular(char* vector_operacion);


int main(){

    int menu, resultado;
    char archivo [20];
    char vector_operacion [1000];


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


        resultado = calcular( vector_operacion);
        printf("El Resultado es: %d \n", resultado);

    }

    return 0;
}

//MAL! ACA ESTOY TRABAJANDO CON ENTEROS Y EN REALIDAD TENGO CHAR!
int calcular(char* vector_operacion) {
    int i = 0;
    ptr_nodo pila = NULL;
    int valor, aux, resultado=0;

    while(vector_operacion[i] != '\0') {

        if(vector_operacion[i] == '+'){
            valor = resultado;  
            while((aux = Pop(&pila))>0){
                valor += aux;
            }

            resultado = valor;
            printf("=%d", resultado);
        } 

        else if(vector_operacion[i] == '-'){
            valor = resultado;
            while((aux = Pop(&pila))>0){
                valor -= aux;
            }

            resultado = valor;
            printf("=%d", resultado);
        }

        else if(vector_operacion[i] == '*'){
            valor = resultado;
            while((aux = Pop(&pila))>0){
                valor *= aux;
            }

            resultado = valor;
            printf("=%d", resultado);
        }
        i++;
    }
    return resultado;
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

int isoperator (char c){
    if (c == '+' || c == '-' || c == '*' )
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

//Convierte una cadena de numeros a enteros
int my_atoi(char* string){
    
    int largo, i, numero = 0; 
    int CDU = 1;    // Clasificación Decimal Universal 1, 10, 100, 1000 ...

    largo = strlen(string);

    for (i = (largo-1) ; i >= 0 ; i--) { // uso largo-1 porque el indice del vector comienza en 0
        numero += (string[i] - diferenciaASCII) * CDU;
        CDU *= 10; // Se utiliza para calcular unidades, decenas, centenas ...
    }

    return numero;
}


void Push(ptr_nodo *pila, int info) {
   
   ptr_nodo nuevo = (ptr_nodo)malloc(sizeof(nodo));
   nuevo->info = info;
 
   nuevo->sig = *pila;
   *pila = nuevo;
}
 
int Pop(ptr_nodo *pila) {

    int info;
    ptr_nodo p = *pila;
    
    if(!p) 
        return 0;

    *pila = p->sig;
    info = p->info;

    free(p);
    return info;
}
