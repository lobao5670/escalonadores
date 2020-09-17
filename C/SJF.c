#include <stdio.h>

int QTD;

int main() {
    printf("Qnt de processos: ");
    scanf("%d", &QTD);
    int processos[QTD][3];

    for (int i = 0; i < QTD;  i++) {
        processos[i][0] = i;
        printf("Arrival Time: ");
        scanf("%d", &processos[i][1]);
        printf("Burst Time: ");
        scanf("%d", &processos[i][2]);
    }

    int wt[QTD];
    int tat[QTD];
    for (int i = 0; i < QTD; i++) {
        wt[i] = 0;
        tat[i] = 0;
    }

    order_by_bt(processos);
    waiting_time(processos, wt);
    turn_around_time(processos, tat, wt);

    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\tCompletion Time\n\n");

    for (int i = 0; i < QTD; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processos[i][0], processos[i][2], processos[i][1], wt[i], tat[i], tat[i] + processos[i][1]);
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

void waiting_time(int processos[QTD][3], int wt[QTD]) {
    int tempo_servico[QTD];
    tempo_servico[0] = 0;

    for (int i = 1; i < QTD; i++) {
        tempo_servico[i] = tempo_servico[i-1] + processos[i-1][2];
        wt[i] = tempo_servico[i] - processos[i][1];

        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

void turn_around_time(int processos[QTD][3], int tat[QTD], int wt[QTD]) {
    for (int i = 0; i < QTD; i++) {
        tat[i] = processos[i][2] + wt[i];
    }
}

void order_by_bt(int processos[QTD][3]) {
    for (int i = 0; i < QTD; i++) {
        for (int j = 0; j < QTD-1; j++) {
            if (processos[j][2] > processos[j+1][2]) {
                int temp0 = processos[j][0];
                int temp1 = processos[j][1];
                int temp2 = processos[j][2];

                processos[j][0] = processos[j+1][0];
                processos[j][1] = processos[j+1][1];
                processos[j][2] = processos[j+1][2];

                processos[j+1][0] = temp0;
                processos[j+1][1] = temp1;
                processos[j+1][2] = temp2;
            }
        }
    }
}