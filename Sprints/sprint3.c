#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

int main() {

    char sigma[100];
    char stand[100];
    float temp;
    char *p,*sig;
    int i=0;
    
    
    printf("quantas vezes pretenda executar o cálculode temperatura ? ");
    fgets(sigma,100,stdin); 

    long maxi=strtol(sigma,&sig,10);



    while(i<maxi){

    
        printf("introduza um valor pelo sensor  :\n ");
    
        fgets(stand,100,stdin);

    
        long l =strtol(stand, &p,10);

    
        temp = (260.0 * l ) / 1023.0 - 20.0;
    

         
        if (l==-1){

          break;

        }
        else if ((temp > -10.0) && (temp < 190.0)) {

        printf("o valor de tempratura é %.2f \n ", temp);

        i=i+1;
    
        }
        
        else {

        printf("valor fora de gama \n ");
        i=i+1;
        }

}



printf("fim de programa \n");

    return 0;
}