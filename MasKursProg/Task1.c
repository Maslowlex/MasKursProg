#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>

#define X_MIN 100.0
#define X_MAX 900.0
#define Q0 45.0
#define TOLERANCE_PERCENT 8.0
#define WARN_PERCENT 20.0
#define N_MEASUREMENTS 70
#define N_ANALYZE 30

#define STATE_NORMAL 0
#define STATE_WARNING 1
#define STATE_ALARM 2

int read_x(double* x);
double calculate_q(double x);
int evaluate_state(double q_val, double* deviation_percent_out);
void compute_statistics(double q_values[], int count, int* count_below_q0, double* avg_deviation);

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

int read_x(double* x) {
    if (scanf("%lf", x) != 1) {
        return 0;
    }
    if (*x < X_MIN || *x > X_MAX) {
        return 0;
    }
    return 1;
}

double calculate_q(double x) {
    if (x < 350.0) {
        return 2 * (x - 350.0) + 5;
    }
    else if (x >= 350.0 && x <= 650.0) {
        return 0.5 * (x - 500.0) * (x - 500.0) + 45.0;
    }
    else {
        return 2 * log(x - 650.0 + 2) + 60;
    }
}

int evaluate_state(double q_val, double* deviation_percent_out) {
    double tolerance = Q0 * (TOLERANCE_PERCENT / 100.0);
    double lower_bound = Q0 - tolerance;
    double upper_bound = Q0 + tolerance;

    double diff = fabs(q_val - Q0);
    *deviation_percent_out = (diff / Q0) * 100.0;

    if (q_val >= lower_bound && q_val <= upper_bound) {
        return STATE_NORMAL;
    }
    else if (*deviation_percent_out <= WARN_PERCENT) {
        return STATE_WARNING;
    }
    else {
        return STATE_ALARM;
    }
}

void compute_statistics(double q_values[], int count, int* count_below_q0, double* avg_deviation) {
    *count_below_q0 = 0;
    double sum_deviation = 0.0;

    for (int i = 0; i < count; i++) {
        if (q_values[i] < Q0) {
            (*count_below_q0)++;
        }
        sum_deviation += fabs(q_values[i] - Q0);
    }
    *avg_deviation = sum_deviation / count;
}