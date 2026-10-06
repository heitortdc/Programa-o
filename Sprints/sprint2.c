#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <type.h>

int x(char *stand, int size) {
    int td= 0;

    for (int i = 0; i < size; i++) {
        if (stand[i] == '\n' || stand[i] == '\0') {
            break;
        }

        if (!isdigit((unsigned char)stand[i])) {
            return 0;
        }

        td= 1;
    }

    return td;
}

int main() {
    char stand[100];
    float temp;

    if (fgets(stand, sizeof(stand), stdin) == NULL) {
        return -1;
    }

    if (!x(stand, sizeof(stand))) {
        printf("Entrada invalida!\n");
        return -1;
    }

    int valor_adc = atoi(stand);

    temp = (260.0 * valor_adc) / 1023.0 - 20.0;

    if ((temp > -10.0) && (temp < 190.0)) {
        printf("o valor de tempratura é %.2f ", temp);
    } else {
        printf("valor fora de gama ");
    }

    return 0;
}