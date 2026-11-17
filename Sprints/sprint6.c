#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LEITURAS 100
#define TAM_LINHA 100
#define TAM_NOME 20
#define T_MIN -10.0
#define T_MAX 190.0

/* ---------- Calibração: ÚNICO sítio a alterar para mudar/acrescentar um sensor ----------
 * A posição i descreve o sensor i nos três vetores.
 * Para acrescentar um sensor: somar 1 a N_SENSORES e acrescentar uma entrada em cada vetor. */
#define N_SENSORES 3
static const char *NOMES[N_SENSORES]   = {"TEMP1", "TEMP2", "TEMP3"};
static const double GANHOS[N_SENSORES] = {260.0, 250.0, 240.0};
static const double DESVIOS[N_SENSORES] = {-20.0, -15.0, -10.0};

/* Protótipos */
int procurarSensor(const char nome[]);
double converterTemperatura(long valor, int s);
int temperaturaValida(double temp);
int lerValores(int sensor[], long instante[], long valor[], double temp[]);
int contarLeituras(const int sensor[], int contador, int s);
double calcularMinimo(const int sensor[], const double temp[], int contador, int s);
double calcularMaximo(const int sensor[], const double temp[], int contador, int s);
double calcularMedia(const int sensor[], const double temp[], int contador, int s);
double calcularDesvioPadrao(const int sensor[], const double temp[], int contador, int s);
void apresentarResultados(const int sensor[], const long instante[], const long valor[],
                          const double temp[], int contador);

int main(void)
{
    int sensor[MAX_LEITURAS];     /* índice do sensor de cada leitura (0, 1, 2) */
    long instante[MAX_LEITURAS];
    long valor[MAX_LEITURAS];     /* valor lido diretamente do sensor */
    double temp[MAX_LEITURAS];    /* temperatura já convertida */

    int contador = lerValores(sensor, instante, valor, temp);

    if (contador > 0) {
        apresentarResultados(sensor, instante, valor, temp, contador);
    }

    return 0;
}

/* Devolve o índice do sensor com este nome, ou -1 se não existir. */
int procurarSensor(const char nome[])
{
    for (int s = 0; s < N_SENSORES; s++) {
        if (strcmp(nome, NOMES[s]) == 0) {
            return s;
        }
    }
    return -1;
}

/* temp = ganho * x / 1023 + desvio, com os dados do sensor s */
double converterTemperatura(long valor, int s)
{
    return GANHOS[s] * valor / 1023.0 + DESVIOS[s];
}

int temperaturaValida(double temp)
{
    return temp >= T_MIN && temp <= T_MAX;
}

/* Lê linhas "SENSOR INSTANTE VALOR" até FIM ou até o vetor estar cheio.
 * Só as leituras válidas são guardadas. Devolve quantas foram guardadas. */
int lerValores(int sensor[], long instante[], long valor[], double temp[])
{
    char linha[TAM_LINHA];
    char nome[TAM_NOME];
    char extra;
    long inst, val;
    int contador = 0;

    while (contador < MAX_LEITURAS) {
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break;                                   /* fim da entrada (Ctrl+D) */
        }

        /* o 4.º campo (%c) só é lido se sobrar texto depois do valor: n == 4 -> lixo no fim */
        int n = sscanf(linha, "%19s %ld %ld %c", nome, &inst, &val, &extra);

        if (n == EOF) {
            continue;                                /* linha em branco: ignorar */
        }

        if (strcmp(nome, "FIM") == 0) {
            break;
        }

        int s = procurarSensor(nome);                /* 1.º: o sensor existe? */
        if (s < 0) {
            printf("Sensor desconhecido\n");
            continue;
        }

        if (n != 3) {                                /* 2.º: a linha tem o formato certo? */
            printf("Linha inválida\n");
            continue;
        }

        double t = converterTemperatura(val, s);     /* 3.º: a temperatura está na gama? */
        if (!temperaturaValida(t)) {
            printf("Valor fora da gama\n");
            continue;
        }

        sensor[contador] = s;
        instante[contador] = inst;
        valor[contador] = val;
        temp[contador] = t;
        contador++;

        printf("%.2f\n", t);
    }

    return contador;
}

/* Número de leituras do sensor s */
int contarLeituras(const int sensor[], int contador, int s)
{
    int n = 0;
    for (int i = 0; i < contador; i++) {
        if (sensor[i] == s) {
            n++;
        }
    }
    return n;
}

/* Só considera as leituras do sensor s; o mínimo começa na 1.ª leitura DESSE sensor.
 * Pré-condição: o sensor tem pelo menos uma leitura. */
double calcularMinimo(const int sensor[], const double temp[], int contador, int s)
{
    double minimo = 0.0;
    int primeira = 1;

    for (int i = 0; i < contador; i++) {
        if (sensor[i] != s) {
            continue;
        }
        if (primeira || temp[i] < minimo) {
            minimo = temp[i];
            primeira = 0;
        }
    }
    return minimo;
}

double calcularMaximo(const int sensor[], const double temp[], int contador, int s)
{
    double maximo = 0.0;
    int primeira = 1;

    for (int i = 0; i < contador; i++) {
        if (sensor[i] != s) {
            continue;
        }
        if (primeira || temp[i] > maximo) {
            maximo = temp[i];
            primeira = 0;
        }
    }
    return maximo;
}

double calcularMedia(const int sensor[], const double temp[], int contador, int s)
{
    double soma = 0.0;
    int n = 0;

    for (int i = 0; i < contador; i++) {
        if (sensor[i] == s) {
            soma += temp[i];
            n++;
        }
    }
    return soma / n;
}

/* desvio-padrão da população (divide por N) */
double calcularDesvioPadrao(const int sensor[], const double temp[], int contador, int s)
{
    double media = calcularMedia(sensor, temp, contador, s);
    double somaQuadrados = 0.0;
    int n = 0;

    for (int i = 0; i < contador; i++) {
        if (sensor[i] == s) {
            double dif = temp[i] - media;
            somaQuadrados += dif * dif;
            n++;
        }
    }
    return sqrt(somaQuadrados / n);
}

void apresentarResultados(const int sensor[], const long instante[], const long valor[],
                          const double temp[], int contador)
{
    printf("\nLeituras registadas (sensor instante: valor -> temperatura):\n");
    for (int i = 0; i < contador; i++) {
        printf("%s %ld: %3ld -> %6.2f\n", NOMES[sensor[i]], instante[i], valor[i], temp[i]);
    }

    for (int s = 0; s < N_SENSORES; s++) {
        int n = contarLeituras(sensor, contador, s);
        if (n == 0) {
            continue;                                /* só sensores com leituras */
        }
        printf("\nSensor %s\n", NOMES[s]);
        printf("Número de valores lidos: %d\n", n);
        printf("Temperatura mínima:    %6.2f\n", calcularMinimo(sensor, temp, contador, s));
        printf("Temperatura máxima:    %6.2f\n", calcularMaximo(sensor, temp, contador, s));
        printf("Temperatura média:     %6.2f\n", calcularMedia(sensor, temp, contador, s));
        printf("Desvio-padrão:         %6.2f\n", calcularDesvioPadrao(sensor, temp, contador, s));
    }
}