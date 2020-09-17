#include <stdio.h>

int QTD = 3;

int main()
{
    int processos[3][4] = {
        {0, 3, 7, 20},
        {1, 2, 4, 5},
        {2, 2, 8, 10}
    };
    
    edf(processos);

    return 0;
}

int hiper_periodo(int processos[QTD][4]) {
    int temp = 0;
    
    for (int i = 0; i < QTD; i++) {
        if(processos[i][3] > 3) {
            temp = processos[i][3];
        }
    }
    
    return temp;
}

int escolher_menor_deadline(int processos[QTD][4], int deadlines[QTD]) {
    int menor_deadline = 10000;
    int escolhido = -1;

    for (int i = 0; i < QTD; i++) {
        if (deadlines[i] < menor_deadline) {
            menor_deadline = deadlines[i];
            escolhido = i;
        }
    }

    return escolhido;
}

void edf(int processos[QTD][4]) {
    int relogio = 0;

    int deadlines[QTD];
    for (int i = 0; i < QTD; i++) {
        deadlines[i] = processos[i][2];
    }

    int periodos[QTD];
    for (int i = 0; i< QTD; i++) {
        periodos[i] = processos[i][3];
    }

    int contador[QTD];

    for (;;) {
        int escolhido = escolher_menor_deadline(processos, deadlines);
        printf("Processo escolhido: %d\n", escolhido);

        if (periodos[escolhido] >= relogio) {
            relogio += processos[escolhido][1];
            printf("Processo: P%d executando...\n", escolhido);
            printf("Relogio: %d\n", relogio);
            printf("Burst time do processo P%d: %d\n", escolhido, processos[escolhido][1]);

            printf("Deadline ANTERIOR do processo: %d\n", deadlines[escolhido]);
            deadlines[escolhido] += processos[escolhido][3];
            printf("Deadline do processo P%d atualizado: %d\n", escolhido, deadlines[escolhido]);

            printf("Periodo ANTERIOR do processo: %d\n", periodos[escolhido]);
            periodos[escolhido] += processos[escolhido][3];
            printf("Periodo do processo P%d atualizo: %d\n", escolhido, periodos[escolhido]);

            contador[escolhido]++;
        }

        if (relogio >= 20) {
            break;
        }
    }

    for (int i = 0; i < QTD; i++) {
        printf("O processo P%d executou %d vezes\n", i, contador[i]);
    }
}