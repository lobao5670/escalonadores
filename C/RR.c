#include <stdio.h>

int QTD;

int main() {
    printf("Qnt de processos: ");
    scanf("%d", &QTD);
    int processos[QTD][2];
    int quantum;
    
    for (int i = 0; i < QTD;  i++) {
        printf("Arrival Time: ");
        scanf("%d", &processos[i][0]);
        printf("Burst Time: ");
        scanf("%d", &processos[i][1]);
    }

    printf("Quantum: ");
    scanf("%d", &quantum);

    int wt[QTD];
    int tat[QTD];
    for (int i = 0; i < QTD; i++) {
        wt[i] = 0;
        tat[i] = 0;
    }

    round_robin(processos, quantum, wt);
    turn_around_time(processos, tat, wt);

    printf("Process\tBurst Time\tArrival Time\tWaiting Time\tTurn-Around Time\n\n");

    for (int i = 0; i < QTD; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i, processos[i][1], processos[i][0], wt[i], tat[i]);
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

void round_robin(int processos[QTD][2], int quantum, int wt[QTD]) {
    int bt_restante[QTD];

    for (int i = 0; i < QTD; i++) {
        bt_restante[i] = processos[i][1];
    }

    int tempo = 0;
    int overhead = 1;

    for (;;) {
        int finalizados = 1;

        for (int i = 0; i < QTD; i++) {
            tempo += overhead;

            if (bt_restante[i] > 0) {
                finalizados = 0;

                if (bt_restante[i] > quantum) {
                    tempo += quantum;

                    bt_restante[i] -= quantum;
                } else {
                    tempo += bt_restante[i];
                    wt[i] = tempo - processos[i][1];
                    bt_restante[i] = 0;
                }
            }
        }

        if (finalizados == 1) {
            break;
        }
    }
}

void turn_around_time(int processos[QTD][2], int tat[QTD], int wt[QTD]) {
    for (int i = 0; i < QTD; i++) {
        tat[i] = processos[i][1] + wt[i];
    }
}
