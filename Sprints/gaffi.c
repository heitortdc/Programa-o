#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

int main() {

    char stand[100];
    float temp;
    char *p;
    int i=0;

    while(i<5){

    
        printf("introduza um valor pelo sensor \n ");
    
        fgets(stand,100,stdin);

    
        long l =strtol(stand, &p,10);

    
        temp = (260.0 * l ) / 1023.0 - 20.0;
    

         
        if (l==-1){

          break;

        }
        else if ((temp > -10.0) && (temp < 190.0)) {

        printf("o valor de tempratura é %.2f \n ", temp);
    
        }
        
        
        else {

        printf("valor fora de gama \n ");
        }

}



printf("fim de programa \n");

    return 0;
}