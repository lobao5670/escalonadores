#include <stdio.h>

int QTD;

int main() {
    printf("Qnt de processos: ");
    scanf("%d", &QTD);
    int processos[QTD][2];

    for (int i = 0; i < QTD;  i++) {
        printf("Arrival Time: ");
        scanf("%d", &processos[i][0]);
        printf("Burst Time: ");
        scanf("%d", &processos[i][1]);
    }

    int wt[QTD];
    int tat[QTD];
    for (int i = 0; i < QTD; i++) {
        wt[i] = 0;
        tat[i] = 0;
    }

    waiting_time(processos, wt);
    turn_around_time(processos, tat, wt);

    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\tCompletion Time\n\n");

    for (int i = 0; i < QTD; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, processos[i][1], processos[i][0], wt[i], tat[i], tat[i] + processos[i][0]);
    }

    float sum_wt = 0;
    float sum_tat = 0;

    for (int i = 0; i < QTD; i++) {
        sum_wt += wt[i];
        sum_tat += tat[i];
    }

    printf("Average waiting time: %.2f\n", sum_wt / QTD);
    printf("Average turn-around time: %.2f\n", sum_tat / QTD);

    return 0;
}

void waiting_time(int processos[QTD][2], int wt[QTD]) {
    int tempo_servico[QTD];
    tempo_servico[0] = 0;

    for (int i = 1; i < QTD; i++) {
        tempo_servico[i] = tempo_servico[i-1] + processos[i-1][1];
        wt[i] = tempo_servico[i] - processos[i][0];

        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

void turn_around_time(int processos[QTD][2], int tat[QTD], int wt[QTD]) {
    for (int i = 0; i < QTD; i++) {
        tat[i] = processos[i][1] + wt[i];
    }
}
