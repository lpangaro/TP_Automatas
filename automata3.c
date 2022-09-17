#include<stdio.h>
#include<ctype.h>

enum ESTADOS {
	INICIO = 0,
	NUMERO,
	NUMERO_O_OPERADOR,
	RECHAZO
};


int validar_vector(char* cadena);
int isoperator (char c);


int main() 
{
	char cadena [1000];

	printf("Ingrese una cadena: " );
	scanf("%s", cadena);

	if (validar_vector(cadena)){
		printf("VECTOR VALIDO \n ");
	}
	else
		printf("VECTOR INVALIDO \n");

	return 0;
}

 int isoperator (char c){
    if (c == '+' || c == '-' || c == '*' )
        return 1;
    return 0;
}


int validar_vector(char* cadena) {
	int estado = INICIO, i=0;
	while(1){
		switch(estado){
			case INICIO: //Q1
				if(isdigit(cadena[i]))
					estado = NUMERO_O_OPERADOR;
				else
					estado = RECHAZO;
				i++;
				break;

			case NUMERO_O_OPERADOR: //Q2
				if (cadena[i] == '\0')
					return 1; //valido
				else if(isdigit(cadena[i]))
					estado = NUMERO_O_OPERADOR;
				else if(isoperator(cadena[i]))
					estado = NUMERO; //Despues de un operador viene si o si un numero
				else 
					estado = RECHAZO;
				i++;
				break;

			case NUMERO: //Q3
				if(isdigit(cadena[i]))
						estado = NUMERO_O_OPERADOR;
					else
						estado = RECHAZO;
				i++;
				break;

			case RECHAZO:
				return 0; //invalido
		}
	}
}


/*
int validar_vector(char* cadena) {
    int i=0;

    while (cadena[i] != '\0') {
        if(isdigit(cadena[i])) { // isdigit devuelve un valor no nulo si es un digito
            i++;
        }
        else if (isoperator(cadena[i]) && isdigit(cadena[i - 1]) && isdigit(cadena[i + 1])) {
            // SI el caracter leido es un operador tambien verifico que en la posicion siguiente y anterior haya un numero
            i++;
        }
        else 
            return 0; //invalido
    }
    return 1; //valido
}
*/