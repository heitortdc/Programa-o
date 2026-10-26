#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h> 

int converter(int valor);
float verificar(float valor);
float valor;

int main() {

    converter(500);
    verificar(valor);

    return 0;
}

int converter(int valor){
return valor = (260.0 * valor) / 1023.0 - 20.0;
}

float verificar(float valor){
     if ((valor > -10.0) && (valor < 190.0)) {
            printf("O valor da temperatura e %.2f\n", valor);
        }
        else {
            printf("Valor fora de gama\n");
            valor = 0;
        }
    }

