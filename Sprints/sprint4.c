#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXL 2

int main() {

    char stand[100];
    char *p,*sig;
    int i=0;
    long l[MAXL];
    int contador;
    

    while(i<MAXL){

    
        printf("introduza um valor pelo sensor , se desejar sair ,digita -1 :\n ");
    
        fgets(stand,100,stdin);

        l[i] =strtol(stand, &p,10);

        if (l[i]==-1){

          break;

        }
    
        else {

        i=i+1;

        }

        contador=contador+1;

    }
    

    float temp[contador];
    


    for(int j=0;j<=contador;j++){

    
    
        temp[j] = (260.0 * l[j] ) / 1023.0 - 20.0;
    

        if ((temp[j] > -10.0) && (temp[j]< 190.0)) {

        printf("o valor de tempratura é %.2f \n ", temp[j]);

    
        }
        
        else {

        printf("valor fora de gama \n ");
        temp[j]=0;

        }

    }

    float minimo=temp[0];
    float maximo=temp[0];
    float media;
    float desvio;
    float soma,sd,varianca;

for(int m=0;m<=contador;m++){

    soma=soma+temp[i];

    if(temp[i]<minimo){

        minimo=temp[i];
    }

    if(temp[i]>maximo){

        maximo=temp[i];
    }
    
   }

   media = soma / contador;

    
    for (int i = 0; i < contador; i++) {
        double difer = temp[i] - media;
        sd=sd+(difer*difer);
    }

    
    varianca = sd/contador; 

    
    desvio = varianca*varianca;

    printf("\n--- Resultados ---\n");
    printf("minimo: %.5f\n", minimo);
    printf("Maximo: %.2f\n", maximo);
    printf("Media: %.2f\n", media);
    printf("Desvio Padrao: %.2f\n", desvio);

   
    printf("fim de programa \n");

    return 0;
}