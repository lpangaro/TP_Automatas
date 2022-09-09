#include<stdio.h>
#include<string.h>

int separo_sumas (char* vec);
int separo_restas (char* vec, int* numero);
int my_atoi (char* vec);


#define diferenciaASCII 48

int main(){
	int resultado = 0; // si no tengo ni sumas ni restas deberia sumarle 1. el neutro del protucto es el 1 mientras que el netir de la suma y resta es el 0
	char vector[10] = {'4', '3', '+', '2', '-', '9', '+', '3', '\0'};
	printf("comienzo: %s\n", vector);

	if(strstr(vector, "+") != NULL) {
		resultado = separo_sumas(vector);
	}
	/*
	if(strstr(vector, '-') != NULL) {
		separo_restas(vector);
	}*/


	return 0;
}


int separo_sumas (char* vec) {

	char* token = NULL;
	int numero = 0;

	token = strtok(vec, "+");

	while(token != NULL){
		printf("+ Token: %s\n", token);
		

		if(strstr(token, "-") != NULL) {
			numero += separo_restas(token, &numero);
		}
		else 
			numero += my_atoi(token);

		printf("Int: %d\n", numero);

		token = strtok(NULL, "+");
	}

	return numero;
}



int separo_restas (char* vec, int* numero) {
	char* token = NULL;
	
	token = strtok(vec, "-");

	
	while(token != NULL){
		printf("- Token: %s\n", token);
		
		*numero -= my_atoi(token);
		printf("Int: %d\n", *numero);

		token = strtok(NULL, "-");
	}

	return *numero;
}

int my_atoi(char* string){ // DEL EJERCICIO 2
    
    int largo, i, numero = 0; 
    int CDU = 1;    // Clasificación Decimal Universal 1, 10, 100, 1000 ...

    largo = strlen(string);

    for (i = (largo-1) ; i >= 0 ; i--) { // uso largo-1 porque el indice del vector comienza en 0
        numero += (string[i] - diferenciaASCII) * CDU;
        CDU *= 10; // Se utiliza para calcular unidades, decenas, centenas ...
    }

    return numero;
}