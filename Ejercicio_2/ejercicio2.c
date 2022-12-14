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
    #include <string.h>

    int my_atoi(char *);

    int main() 
    {
        int numero;
        char string [100];

        printf("Ingrese un string numerico: " );
        scanf("%s", string);

       numero = my_atoi(string);

        printf("El string ingresado es: ´%s´ \n", string);
        printf("La conversion se realizo exitosamente, el NUMERO (int) ingresado es: %d \n", numero);

        return 0;
    }

int my_atoi(char* string){
    
    int largo, i, numero = 0; 
    int VP = 1;    // Valos posicional 1, 10, 100, 1000 ...

    largo = strlen(string);

    for (i = (largo-1) ; i >= 0 ; i--) { // uso largo-1 porque el indice del vector comienza en 0
        numero += (string[i] - diferenciaASCII) * VP;
        VP *= 10; // Se utiliza para calcular unidades, decenas, centenas ...
    }

    return numero;
}


