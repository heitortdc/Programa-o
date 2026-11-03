#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Protótipos das funções

long lerAmostras();
int lerValores(long l[], long maxi);
float converterTemperatura(long l);
int temperaturaValida(float temp);
void calcularTemperaturas(long l[], float temp[], int valida[], int contador);
float calcularMinimo(float temp[], int contador);
float calcularMaximo(float temp[], int contador);
float calcularMedia(float temp[], int contador);
float calcularDesvioPadrao(float temp[], int contador);
void apresentarResultados(long l[], float temp[], int valida[], int contador,
float minimo, float maximo, float media, float desvio);

// MAIN

int main()
{

    long maxi;
    int contador;

    float minimo;
    float maximo;
    float media;
    float desvio;

    maxi = lerAmostras();

    long l[maxi];
    float temp[maxi];
    int valida[maxi];

    contador = lerValores(l, maxi);

    if (contador > 0)
    {

        calcularTemperaturas(l, temp, valida, contador);

        minimo = calcularMinimo(temp, contador);

        maximo = calcularMaximo(temp, contador);

        media = calcularMedia(temp, contador);

        desvio = calcularDesvioPadrao(temp, contador);

        apresentarResultados(l, temp, valida, contador,
                             minimo, maximo, media, desvio);
    }

    printf("Fim de programa\n");

    return 0;
}

// FUNÇÃO PARA LER O NÚMERO DE AMOSTRAS

long lerAmostras()
{

    char namostras[100];
    char *n;

    printf("digita o número de amostras que deseja verificar para iniciar o programa:\n");

    fgets(namostras, 100, stdin);

    long maxi = strtol(namostras, &n, 10);

    return maxi;
}

// FUNÇÃO PARA LER OS VALORES DO SENSOR

int lerValores(long l[], long maxi)
{

    char stand[100];
    char *p;

    int i = 0;
    int contador = 0;

    while (i < maxi)
    {

        printf("Introduza um valor pelo sensor; para sair, digite -1:\n");

        fgets(stand, 100, stdin);

        l[i] = strtol(stand, &p, 10);

        if (l[i] == -1)
        {
            break;
        }

        i = i + 1;
        contador = contador + 1;
    }

    return contador;
}

// FUNÇÃO PARA CONVERTER O VALOR DO SENSOR EM TEMPERATURA

float converterTemperatura(long l)
{

    float temp;

    temp = (260.0 * l) / 1023.0 - 20.0;

    return temp;
}

// FUNÇÃO PARA VERIFICAR SE A TEMPERATURA É VÁLIDA

int temperaturaValida(float temp)
{

    if ((temp > -10.0) && (temp < 190.0))
    {
        return 1;
    }

    return 0;
}

// FUNÇÃO PARA CALCULAR AS TEMPERATURAS E VERIFICAR A SUA VALIDADE

void calcularTemperaturas(long l[], float temp[], int valida[], int contador)
{

    for (int j = 0; j < contador; j++)
    {

        temp[j] = converterTemperatura(l[j]);

        valida[j] = temperaturaValida(temp[j]);

        if (valida[j] == 0)
        {
            temp[j] = 0;
        }
    }
}

// FUNÇÃO PARA CALCULAR A TEMPERATURA MÍNIMA

float calcularMinimo(float temp[], int contador)
{

    float minimo = temp[0];

    for (int m = 1; m < contador; m++)
    {

        if (temp[m] < minimo)
        {
            minimo = temp[m];
        }
    }

    return minimo;
}

// FUNÇÃO PARA CALCULAR A TEMPERATURA MÁXIMA

float calcularMaximo(float temp[], int contador)
{

    float maximo = temp[0];

    for (int m = 1; m < contador; m++)
    {

        if (temp[m] > maximo)
        {
            maximo = temp[m];
        }
    }

    return maximo;
}

// FUNÇÃO PARA CALCULAR A MÉDIA

float calcularMedia(float temp[], int contador)
{

    float soma = 0;
    float media;

    for (int m = 0; m < contador; m++)
    {

        soma = soma + temp[m];
    }

    media = soma / contador;

    return media;
}

// FUNÇÃO PARA CALCULAR O DESVIO-PADRÃO

float calcularDesvioPadrao(float temp[], int contador)
{

    float somaquadrado = 0;
    float varianca;
    float desvio;

    float media = calcularMedia(temp, contador);

    for (int m = 0; m < contador; m++)
    {

        float difer = temp[m] - media;

        somaquadrado = somaquadrado + (difer * difer);
    }

    varianca = somaquadrado / contador;

    desvio = sqrt(varianca);

    return desvio;
}

// FUNÇÃO PARA APRESENTAR OS VALORES E AS ESTATÍSTICAS

void apresentarResultados(long l[], float temp[], int valida[], int contador,
                          float minimo, float maximo, float media, float desvio)
{

    printf("\nValores lidos (sensor -> temperatura):\n");

    for (int j = 0; j < contador; j++)
    {

        if (valida[j] == 1)
        {
            printf("%ld -> %6.2f\n", l[j], temp[j]);
        }
        else
        {
            printf("%ld -> Valor fora de gama\n", l[j]);
        }
    }

    printf("\nNúmero de valores lidos: %d\n", contador);

    printf("Temperatura mínima:    %6.2f\n", minimo);

    printf("Temperatura máxima:    %6.2f\n", maximo);

    printf("Temperatura média:     %6.2f\n", media);

    printf("Desvio-padrão:         %6.2f\n", desvio);
}