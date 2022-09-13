/* Para compilar: gcc -c -o ejercicio3.o ejercicio3.c -Wall
 * Para linkear: gcc -o ejercicio3 ejercicio3.o -Wall
 * Para correr: ./ejercicio3
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

#define diferenciaASCII 48
 

 //PROTOTIPOS DE FUNCIONES
int isoperator(char);
int validar_vector (char *);
int my_atoi(char* string);
void ingreso_por_archivo (char* archivo, char* cadena);
void separar_numeros_de_operadores(char* cadena, char* v_ope, int* v_num, int* largo);
int calcular (char* v_ope, int* v_num, int largo);


int main(){

    int menu, resultado;
    char name_file [20];
    char cadena [1000], v_ope[1000];
    int v_num [1000];
    int largo;

    printf("\n\n..:BIENVENIDE AL PROGRAMA DE AUTOMATAS:..\n");
    printf(" 1) si quiere ingresar la cadena por linea de comandos\n 2) si lo que deasea es ingresar la cadena a traves de un archivo txt \n");
    
    printf("Escriba una opcion: ");
    scanf ("%d", &menu);
    system("clear");

    switch (menu){
        case 1 :
            printf("Ingrese la cadena de caracteres numericos (Hexadecimales, Ocatales o Decimales): ");
            scanf ("%s", cadena);
            break;

        case 2 : 
            printf("Ingrese el nombre del archivo (ej: entrada.txt): ");
            scanf ("%s", name_file);
            ingreso_por_archivo(name_file, cadena);
            break;

        default:
            printf ("No ingreso una opcion valida \n");
            return 1;
    }
    
    if (validar_vector(cadena)){

        separar_numeros_de_operadores(cadena, v_ope, v_num, &largo); // largo es la cantidad de elementos ocupados en v_num
        resultado = calcular(v_ope, v_num, largo);
        printf("El Resultado es: %d \n", resultado);
    }

    return 0;
}


//FUNCIONES
void separar_numeros_de_operadores(char* cadena, char* v_ope, int* v_num, int* largo){

    char copy_cadena [1000]; // Cuando uso strtok pierdo el string
    char *token;
    int i=0, j=0;

    memset(v_num, 0, 1000); // LIMPIO EL VECTOR 
    memset(v_ope, 0, 1000); // LIMPIO EL VECTOR 

    strcpy(copy_cadena, cadena);

    //GUARDO LOS NUMEROS EN v_num
    token = strtok(copy_cadena, "*+-");
    while (token != NULL){

        v_num[i] = my_atoi(token); //Convierto el string a int y lo guardo en v_num
        token = strtok(NULL, "*+-");
        i++;
    }
    (*largo) = i; //Necesito saber cuantas posiciones del vector ocupé

    //GUARDO LOS OPERADORES EN v_ope
    for(i=0; i < (strlen(cadena)); i++){
        if(isoperator(cadena[i])==0){
            v_ope[j] = cadena[i];
            j++;
        }
    }
}

int calcular (char* v_ope, int* v_num, int largo) {
    int i, resultado = 0;

    for(i=(strlen(v_ope) - 1); i >= 0; i--){                // recorro de atras para adelante por si tengo multeples productos no multiplicar pot 0
        if(v_ope[i] == '*'){                                //Primero resuelvo el * para respetar precedencia
            v_num[i] = v_num[i] * v_num[i+1];
            v_num[i+1] = 0;
        }
    }

    for(i=0; i < strlen(v_ope); i++){
        if(v_ope[i] == '+'){
            v_num[i] = v_num[i] + v_num[i+1];
            v_num[i+1] = 0;
        }
        if(v_ope[i] == '-'){
            v_num[i] = v_num[i] - v_num[i+1];
            v_num[i+1] = 0;
        }
    }

    for(i=0; i < largo; i++){
        resultado += v_num[i];
    }
    
    return resultado;
}


int validar_vector(char* cadena) {

    int i = 0;

    while (cadena[i] != '\0') {
        if(isdigit(cadena[i])) {
            i++;
        }
        else if (isoperator(cadena[i]) && isdigit(cadena[i - 1]) && isdigit(cadena[i + 1])) {
            // SI el caracter leido es un operador tambien verifico que en la posicion siguiente y anterior haya un numero
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

void ingreso_por_archivo (char* archivo, char* cadena) {
    int i = 0;
    FILE *f_entrada = fopen(archivo,"r");

    if(f_entrada == NULL){   
        printf("Error en la apertura del archivo.\n");
    }

    else {
        fread(&cadena[i], sizeof(char), 1, f_entrada);   //primer elemento

        while(!feof(f_entrada)) {
            i++;
            fread(&cadena[i], sizeof(char), 1, f_entrada);      //LECTURA DEL ARCHIVO, GUARDO ELEMENTOS DE ENTRADA EN EL VECTOR.
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