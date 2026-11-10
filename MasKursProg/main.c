#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include "kp.h" 

int main() {
    setlocale(LC_ALL, "");

    double q_array[N_MEASUREMENTS];
    double x = 0.0;
    double q_val = 0.0;
    double deviation_percent = 0.0;
    int state_code = 0;
    int count_below = 0;
    double avg_dev = 0.0;
    printf("==========================================================\n");
    printf("|       СИСТЕМА МОНИТОРИНГА СКОРОСТИ ПЕРЕМЕШИВАНИЯ        |\n");
    printf("==========================================================\n");
    printf("Программа преобразует X (об/мин) в показатель качества Q,\n");
    printf("контролирует состояние и выполняет статистический анализ.\n\n");
    printf("Проверка контрольного примера \n");
    double test_x = 425.0;
    printf("X = %.2lf -> Q = %.2lf (Ожидается 2857.50)\n\n", test_x, calculate_q(test_x));
    printf("Ввод выборки из %d значений \n", N_MEASUREMENTS);
    printf("(Допустимый диапазон X: от %.0lf до %.0lf)\n", X_MIN, X_MAX);
    for (int i = 0; i < N_MEASUREMENTS; i++) {
        printf("Замер %d: ", i + 1);
        if (!read_x(&x)) {
            printf("  Ошибка: введено не число или X вне диапазона [%.0lf; %.0lf].\n", X_MIN, X_MAX);
            printf("Программа завершена на замере %d.\n", i + 1);
            return 1;
        }

        q_val = calculate_q(x);
        q_array[i] = q_val;

        printf("  -> Q = %.4lf\n", q_val);
        state_code = evaluate_state(q_val, &deviation_percent);
        printf("  -> Отклонение от Q0: %.2lf%%\n", deviation_percent);

        switch (state_code) {
        case STATE_NORMAL:  printf("  Состояние: НОРМА\n"); break;
        case STATE_WARNING: printf("  Состояние: ПРЕДУПРЕЖДЕНИЕ\n"); break;
        case STATE_ALARM:   printf("  Состояние: ТРЕВОГА\n"); break;
        }
    }
    printf("\n Статистический анализ (первые %d значений) \n", N_ANALYZE);
    compute_statistics(q_array, N_ANALYZE, &count_below, &avg_dev);

    printf("Количество значений Q < Q0 (45.0): %d\n", count_below);
    printf("Среднее отклонение от Q0: %.4lf\n", avg_dev);

    return 0;
}