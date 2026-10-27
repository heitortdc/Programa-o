#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAXL 5

float converter(int valor);
float verificar(float valor);
//int lerValores();
//float resultados();

char stand[100];
char *p;
int i = 0;
long Vsensores[MAXL];
int contador = 0;

int main()
{
    while (i < MAXL)
    {
        printf("Introduza um valor pelo sensor; para sair, digite -1:\n");
        fgets(stand, 100, stdin);

        Vsensores[i] = strtol(stand, &p, 10);

        if (Vsensores[i] == -1)
        {
            break;
        }

        i =+ 1;
        contador =+ 1;
    }

    printf("fim do programa");
}

float converter(int valor)
{
    return (260.0 * valor) / 1023.0 - 20.0;
}

float verificar(float valor){
    
    if ((valor > -10.0) && (valor < 190.0))
    {
        printf("O valor da temperatura e %.2f\n", valor);
        return valor;
    }
    else
    {
        printf("Valor fora de gama\n");
        return 0;
    }
}




