#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define ganhox 260.0
#define ganhoy 250.0
#define ganhoz 240.0
#define desviox -20.0
#define desvioy -15.0
#define desvioz -10.0
#define max 50

void lervalores(int temp1[],int temp2[],int temp3[],float convertidos1[],float  convertidos2[],float convertidos3[]){

    int sensor,instante,valor;
    char entrada[max];
    

    int i=0;
    while(i<50){

           
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            break; 
        }

        
        entrada[strcspn(entrada, "\n")] = 0;

        if (strcmp(entrada, "FIM") == 0) {
            printf("Ciclo terminado pelo utilizador.\n");
            break;
        }

        printf("temp");

        if(sscanf(entrada,"%3d%3d%3d",&sensor,&instante,&valor)==3){
        
            if((valor>0 && valor < 1023) && (instante<50)){



            }
            if(sensor==1){
                temp1[instante]=valor;
                convertidos1[instante] = (ganhox*valor)/(1023 + desviox);
                 printf("%.2f",convertidos3[instante]);

        
            } 

            if(sensor==2){
                temp2[instante]=valor;
                convertidos2[instante] = ganhoy*valor/1023 + desvioy;
                 printf("%.2f",convertidos3[instante]);

        
            } 

            if(sensor==3){
                 temp3[instante]=valor;
                 convertidos3[instante] = ganhoz*valor/1023 + desvioz;
                 printf("%.2f",convertidos3[instante]);

        
            }


            }

    i++;
    }
}


int main(){

    int temp1[50];
    int temp2[50];
    int temp3[50];
    float convertidos1[50];
    float convertidos2[50];
    float convertidos3[50];



    lervalores(temp1,temp2,temp3,convertidos1,convertidos2,convertidos3);






}