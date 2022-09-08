/* Para compilar: gcc -c -o ejercicio1.o ejercicio1.c -Wall
 * Para linkear: gcc -o ejercicio1 ejercicio1.o -Wall
 * Para correr: ./ejercicio1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum ESTADOS{                                                                           // Asignar nombres a los estados del autómata
    INICIO = 0,
    CONSTANTE_OCTAL1,
    CONSTANTE_OCTAL2,
    CONSTANTE_HEXADECIMAL1,
    CONSTANTE_HEXADECIMAL2,
    CONSTANTE_DECIMAL,
    DESCONOCIDO                                                                         // DESCONOCIDO actúa como estado de rechazo
};

void reconocer(char* valor, FILE* archSalida, int* cant_oct, int* cant_deci, int* cant_hexa);
void separar_y_reconocer (char*, FILE* salida);
void ingreso_por_archivo (char*, char*);

int main(){

    int menu;
    char archivo [20];
    char vector_palabras [1000];
    FILE *f_salida = fopen ("salida.txt", "w");    

    printf("\n\n..:BIENVENIDE AL PROGRAMA DE AUTOMATAS:..\n");
    printf(" 1) si quiere ingresar la cadena por linea de comandos\n 2) si lo que deasea es ingresar la cadena a traves de un archivo txt \n");
    
    printf("Escriba una opcion: ");
    scanf ("%d", &menu);
    system("clear");

    switch (menu){
        case 1 :
            printf("Ingrese la cadena de caracteres numericos (Hexadecimales, Ocatales o Decimales): ");
            scanf ("%s", vector_palabras);
            break;
        case 2 : 
            printf("Ingrese el nombre del archivo (ej: entrada.txt): ");
            scanf ("%s", archivo);
            ingreso_por_archivo(archivo, vector_palabras);
            break;
        default:
            printf ("No ingreso una opcion valida \n");
    }
    
    separar_y_reconocer(vector_palabras, f_salida);                           // PASO EL ARRAY CON LAS PALABRAS A RECONOCER
    printf("Archivo creado exitosamente. Para visiualizarlo escriba: ´cat salida.txt´\n");
    
    fclose (f_salida);
    return 0;
}


void ingreso_por_archivo (char* archivo, char* vector_palabras) {
    int i = 0;
    FILE *f_entrada = fopen(archivo,"r");

    if(f_entrada == NULL){   
        printf("Error en la apertura del archivo.\n");
    }

    else {
        fread(&vector_palabras[i], sizeof(char), 1, f_entrada);   //primer elemento

        while(!feof(f_entrada)) {
            i++;
            fread(&vector_palabras[i], sizeof(char), 1, f_entrada);      //LECTURA DEL ARCHIVO, GUARDO ELEMENTOS DE ENTRADA EN EL VECTOR.
        }
    }

    fclose (f_entrada);
}


//SEPARA CADA ELEMENTO POR ´&´, EVALUA CON EL AUTOMATA Y LO GUARDA JUNTO A SU TIPO EN EL ARCH SALIDA.
void separar_y_reconocer (char* vector, FILE* f_salida){ 
    int cant_oct = 0, cant_deci = 0, cant_hexa = 0;
    char* str = NULL;
    const char* sentinela = "&";

    fprintf(f_salida, "Numero                 Cant   Tipo\n");

    str = strtok(vector, sentinela);                           // strtok separa el contenido de un vector en palabras 
    while (str != NULL){                                       // usando el caracter '&' como sentinela. Cada vez que encuentra
        reconocer(str, f_salida, &cant_oct, &cant_deci, &cant_hexa);                              // un '&' envía a reconocer la cadena que estaba detrás de ese caracter
        str = strtok(NULL, sentinela);
    }
} 

//EVALUA ELEMENTO EN EL AUTOMATA Y LO GUARDA EN EL ARCHIVO SALIDA.
void reconocer(char* valor, FILE* f_salida, int* cant_oct, int* cant_deci, int* cant_hexa){
    int estado = INICIO, i = 0;
    while(1){
        switch(estado){
            case INICIO:
                if(valor[i] == '0')                                                     // ¿El primer caracter es un 0?
                    estado = CONSTANTE_OCTAL1;                                          
                else if(isdigit(valor[i]))                           // isdigit evalua si es un caracter numerico.
                    estado = CONSTANTE_DECIMAL;               
                else if (valor[i] == '-'){
                    estado = CONSTANTE_DECIMAL;
                }
                else
                    estado = DESCONOCIDO;                                               // Si es un primer caracter no numerico es no reconocido.
                i++;                    
                break;
            
            case CONSTANTE_OCTAL1:
                if(valor[i] == '\0'){                                                   // ¿FIN (caracter vacio)? 
                    (*cant_oct)++;
                    fprintf(f_salida, "%-20s\t %d OCTAL\n", valor, *cant_oct);
                    return;
                }
                else if(valor[i] == 'x' || valor[i] == 'X')                             // ¿LE SIGUE UNA X? ES HEXADECIMAL
                    estado = CONSTANTE_HEXADECIMAL1;
                else if(isdigit(valor[i]) && valor[i] - '0' < 8)                        // ¿EL CHAR NUMERAL ES MENOR QUE 8?
                    estado = CONSTANTE_OCTAL2;
                else
                    estado = DESCONOCIDO;
                i++;
                break;
            
            case CONSTANTE_OCTAL2:
                if(valor[i] == '\0'){                                                  // ¿FIN? 
                    (*cant_oct)++;
                    fprintf(f_salida, "%-20s\t %d OCTAL\n", valor, *cant_oct);
                    return;
                }
                else if(isdigit(valor[i]) && valor[i] - '0' < 8)
                    estado = CONSTANTE_OCTAL2;
                else
                    estado = DESCONOCIDO;
                i++;
                break;

            case CONSTANTE_HEXADECIMAL1:
                if(isxdigit(valor[i]))
                    estado = CONSTANTE_HEXADECIMAL2;
                else
                    estado = DESCONOCIDO;
                i++;
                break;
            
            case CONSTANTE_HEXADECIMAL2:
                if(valor[i] == '\0'){
                    (*cant_hexa)++;
                    fprintf(f_salida, "%-20s\t %d HEXADECIMAL\n", valor, *cant_hexa);               // ¿FIN? 
                    return;
                }
                else if(isxdigit(valor[i]))
                    estado = CONSTANTE_HEXADECIMAL2;
                else
                    estado = DESCONOCIDO;
                i++;
                break;

            case CONSTANTE_DECIMAL:
                if(valor[i] == '\0'){
                    (*cant_deci)++;
                    fprintf(f_salida, "%-20s\t %d DECIMAL\n", valor, *cant_deci);                 // ¿FIN? 
                    return;
                }
                else if(isdigit(valor[i]))
                    estado = CONSTANTE_DECIMAL;
                else
                    estado = DESCONOCIDO;
                i++;
                break;

            case DESCONOCIDO:                                                       // La cadena no es reconocida por el automata.
                fprintf(f_salida, "%-20s\tNO RECONOCIDA\n", valor);              
                return;
        }
    }
}
