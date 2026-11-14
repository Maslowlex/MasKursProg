#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
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

    FILE* file = NULL;

    printf("**********************************************************\n");
    printf("*        СИСТЕМА МОНИТОРИНГА СКОРОСТИ ПЕРЕМЕШИВАНИЯ      *\n");
    printf("**********************************************************\n");
    printf("*     Автор: Маслов А.Е., группа бИЦТ-262                *\n");
    printf("*     Тема: Обработка потока данных из файла             *\n");
    printf("* Условие: Расчет Q(X), контроль состояния и статистика  *\n");
    printf("**********************************************************\n\n");

    printf("Проверка контрольного примера: X = 425.0 -> Q = %.2lf\n", calculate_q(425.0));
    printf("Ожидается: 2857.50\n\n");

    printf("Попытка открыть файл с данными: %s\n", DATA_FILENAME);

    file = fopen(DATA_FILENAME, "r");
    if (file == NULL) {
        printf("ОШИБКА: Не удалось открыть файл %s.\n", DATA_FILENAME);
        printf("Убедитесь, что файл существует в папке с программой.\n");
        return 1;
    }

    printf("Файл успешно открыт. Начинаем обработку...\n");
    printf("------------------------------------------------\n");

    int i = 0;
    while (i < N_MEASUREMENTS) {

        if (!read_x_from_file(file, &x)) {
            if (feof(file)) {
                printf("\n[Конец файла. Прочитано %d значений из %d]\n", i, N_MEASUREMENTS);
                break; 
            }
            else {
                printf("\n[ОШИБКА: Некорректные данные или X вне диапазона [100; 900] на строке %d]\n", i + 1);
                break; 
            }
        }

        q_val = calculate_q(x);
        q_array[i] = q_val;

        state_code = evaluate_state(q_val, &deviation_percent);

        printf("Замер %2d: X = %6.1lf -> Q = %8.4lf | Откл: %5.2lf%% | ", i + 1, x, q_val, deviation_percent);

        switch (state_code) {
        case STATE_NORMAL:  printf("Норма\n"); break;
        case STATE_WARNING: printf("ПРЕДУПРЕЖДЕНИЕ\n"); break;
        case STATE_ALARM:   printf("ТРЕВОГА\n"); break;
        }

        i++; 
    }

    fclose(file); 

    printf("----------------------------------------------------------\n");

    int actual_count = i; 
    int analyze_count = (actual_count < N_ANALYZE) ? actual_count : N_ANALYZE;

    if (analyze_count > 0) {
        printf("Статистический анализ (на основе первых %d значений):\n", analyze_count);
        compute_statistics(q_array, analyze_count, &count_below, &avg_dev);
        printf("  Количество значений Q < Q0 (45.0): %d\n", count_below);
        printf("  Среднее отклонение от Q0: %.4lf\n", avg_dev);
    }
    else {
        printf("Недостаточно данных для статистического анализа.\n");
    }

    printf("**********************************************************\n");
    return 0;
}