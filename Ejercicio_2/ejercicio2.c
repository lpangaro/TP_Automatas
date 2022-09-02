/* Para compilar: gcc -c -o ejercicio2.o ejercicio2.c -Wall
 * Para linkear: gcc -o ejercicio2 ejercicio2.o -Wall
 * Para correr: ./ejercicio2
 */


// Las computadoras solo entienden numeros, por los que los caracteres tienen una representacion nuemrica basada en ASCII. 
// Esto quiere decir que cuando por ejemplo ingresamos el caracter ´a´ la computadora lo que recibe es "97" y es en un segundo momento que se le asigna la letra
// De igual forma sucede con los numeros. Una cosa es el CARACTER ´1´ y otra el NUMERO 1

/* TABLA ASCII DE NUMEROS
    ´0´ = 48
    ´1´ = 49
    ´2´ = 50
    ´3´ = 51
    ´4´ = 52
    ´5´ = 53
    ´6´ = 54
    ´7´ = 55
    ´8´ = 56
    ´9´ = 57

https://elcodigoascii.com.ar */


#define diferenciaASCII 48

#include <stdio.h>

int main() 
{
    int numero;
    char caracter;
    printf("Ingrese un caracter numerico: " );
    scanf("%c", &caracter);

    printf("El caracter ingresado es: ´%c´ \n", caracter);
    printf("En ASCII el ´%c´ esta representado por el valor: %d \n",caracter, caracter);

    numero = caracter - diferenciaASCII;

    printf("La conversion se realizo exitosamente, el NUMERO (int) ingresado es: %d \n", numero);

    return 0;
}