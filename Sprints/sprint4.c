
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


int main() {

    char stand[100];
    char *p;
    int i = 0;
    int contador = 0;
    char namostras[100];
    char *n;
    
    printf("digita o número de amostras que deseja verificar para iniciar o programa:\n");
    fgets(namostras, 100, stdin);
    
    long maxi=strtol(namostras ,&n,10);
    
    long l[maxi];


    while (i < maxi) {

        printf("Introduza um valor pelo sensor; para sair, digite -1:\n");
        fgets(stand, 100, stdin);
        

        l[i] = strtol(stand, &p, 10);

        if (l[i] == -1) {
            break;
        }

        i=i+1;
        contador=contador+1;
    }

   

    float temp[maxi];

    for (int j = 0; j < contador; j++) {

        temp[j] = (260.0 * l[j]) / 1023.0 - 20.0;

        if ((temp[j] > -10.0) && (temp[j] < 190.0)) {
            printf("O valor da temperatura e %.2f\n", temp[j]);
        }
        else {
            printf("Valor fora de gama\n");
            temp[j] = 0;
        }
    }

    float minimo = temp[0];
    float maximo = temp[0];
    float media;
    float desvio;
    float soma = 0;
    float somaquadrado= 0;
    float varianca;

    for (int m = 0; m < contador; m++) {

        soma = soma + temp[m];

        if (temp[m] < minimo) {
            minimo = temp[m];
        }

        if (temp[m] > maximo) {
            maximo = temp[m];
        }
    }

    media = soma / contador;

    for (int m = 0; m < contador; m++) {

        float difer = temp[m] - media;
        somaquadrado = somaquadrado + (difer * difer);
    }

    varianca = somaquadrado / contador;

    desvio = sqrt(varianca);

    printf("\n--- Resultados ---\n");
    printf("Minimo: %.2f\n", minimo);
    printf("Maximo: %.2f\n", maximo);
    printf("Media: %.2f\n", media);
    printf("Desvio Padrao: %.2f\n", desvio);

    printf("Fim de programa\n");

    return 0;
}
