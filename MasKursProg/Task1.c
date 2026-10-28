#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
double Q(double x);
int check_control(double q_val, double x_val);
int statistical_analysis();
int main() {
    setlocale(LC_ALL, "RUS");
    double x;

    printf("Проверка контрольного примера \n");
    double test_x = 425.0;
    printf("X = %.2lf -> Q = %.2lf (Ожидается 2857.50)\n", test_x, Q(test_x));

    printf("\nРучной ввод \n");
    printf("Введите X (от 100 до 900): ");
    if (scanf("%lf", &x) != 1 || x < 100 || x > 900) {
        printf("Ошибка: X должен быть числом в диапазоне от 100 до 900!\n");
        return 1;
    }
    double q_val = Q(x);
    printf("Q(%.2lf) = %.4lf\n", x, q_val);
    check_control(q_val, x);
    statistical_analysis();
    return 0;
}
double Q(double x) {
    if (x < 350) {
        return 2 * (x - 350) + 5;
    }
    else if (x >= 350 && x <= 650) {
        return 0.5 * pow(x - 500, 2) + 45;
    }
    else {
        return 2 * log(x - 650 + 2) + 60;
    }
}
int check_control(double q_val, double x_val) {
    double Q0 = 45.0;
    double tolerance = Q0 * 0.08; 
    double lower_bound = Q0 - tolerance;
    double upper_bound = Q0 + tolerance;

    printf("Допустимый диапазон Q: [%.2lf; %.2lf]\n", lower_bound, upper_bound);

    double diff = fabs(q_val - Q0);
    double percent_diff = (diff / Q0) * 100.0;

    if (q_val >= lower_bound && q_val <= upper_bound) {
        printf("Состояние: НОРМА (отклонение %.2f%%)\n", percent_diff);
    }
    else if (percent_diff <= 20.0) { 
        printf("Состояние: ПРЕДУПРЕЖДЕНИЕ (отклонение %.2f%%)\n", percent_diff);
    }
    else {
        printf("Состояние: ТРЕВОГА (отклонение %.2f%%)\n", percent_diff);
    }
}
int statistical_analysis() {
    printf("\n Статистический анализ \n");
    int N = 70;
    double q_values[70];
    double Q0 = 45.0;

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        double x = 100.0 + (rand() % 801);
        q_values[i] = Q(x);
    }

    int count_below_Q0 = 0;
    double sum_deviation = 0.0;
    int count_to_analyze = 30; 

    for (int i = 0; i < count_to_analyze; i++) {
        if (q_values[i] < Q0) {
            count_below_Q0++;
        }
        sum_deviation += fabs(q_values[i] - Q0);
    }
    double avg_deviation = sum_deviation / count_to_analyze;
    printf("Количество значений Q < Q0 %d\n", count_below_Q0);
    printf("Среднее отклонение от Q0 = %.4lf\n", avg_deviation);
}