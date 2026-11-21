#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include "kp.h"

int main(void)
{
    setlocale(LC_ALL, "Russian");

    double q_array[N_MEASUREMENTS];
    double x = 0.0;
    int i = 0;

    printf("**********************************************************\n");
    printf("*        СИСТЕМА МОНИТОРИНГА СКОРОСТИ ПЕРЕМЕШИВАНИЯ      *\n");
    printf("**********************************************************\n");
    printf("*     Автор: Маслов А.Е., группа бИЦТ-262                *\n");
    printf("*     Тема: Обработка потока данных из файла             *\n");
    printf("* Условие: Расчет Q(X), контроль состояния и статистика  *\n");
    printf("**********************************************************\n\n");

    printf("Проверка контрольного примера: X = 425.0 -> Q = %.2lf\n",
        calculate_q(425.0));
    printf("Ожидается: 2857.50\n\n");

    printf("Попытка открыть файл с данными: %s\n", DATA_FILENAME);

    FILE* file = fopen(DATA_FILENAME, "r");
    if (!file) {
        printf("ОШИБКА: Не удалось открыть файл %s.\n", DATA_FILENAME);
        printf("Убедитесь, что файл существует в папке с программой.\n");
        return 1;
    }

    printf("Файл успешно открыт. Начинаем обработку...\n");
    printf("----------------------------------------------------------\n");

    while (i < N_MEASUREMENTS) {
        int rc = read_double(file, &x);

        if (rc == READ_EOF) {
            printf("\n[Конец файла. Прочитано %d значений из %d]\n",
                i, N_MEASUREMENTS);
            break;
        }
        if (rc == READ_DATA_ERR) {
            printf("\n[ОШИБКА: строка %d не является числом]\n", i + 1);
            break;
        }

        if (!validate_x(x)) {
            printf("\n[ОШИБКА: X = %.2f вне диапазона [%.0f; %.0f] на строке %d]\n",
                x, X_MIN, X_MAX, i + 1);
            break;
        }

        double q_val = calculate_q(x);
        q_array[i] = q_val;

        double deviation_percent = 0.0;
        int state_code = get_state_code(q_val, &deviation_percent);

        printf("Замер %2d: X = %6.1lf -> Q = %8.4lf | Откл: %5.2lf%% | ",
            i + 1, x, q_val, deviation_percent);

        switch (state_code) {
        case STATE_NORMAL:  printf("Норма\n");           break;
        case STATE_WARNING: printf("ПРЕДУПРЕЖДЕНИЕ\n");  break;
        case STATE_ALARM:   printf("ТРЕВОГА\n");         break;
        }
        i++;
    }

    fclose(file);
    printf("----------------------------------------------------------\n");

    int analyze_count = (i < N_ANALYZE) ? i : N_ANALYZE;
    if (analyze_count > 0) {
        printf("Статистический анализ (на основе первых %d значений):\n",
            analyze_count);
        Statistics s = compute_statistics(q_array, analyze_count);
        printf("  Количество значений Q < Q0 (%.1f): %d\n", Q0, s.count_below);
        printf("  Среднее отклонение от Q0: %.4lf\n", s.avg_dev);
    }
    else {
        printf("Недостаточно данных для статистического анализа.\n");
    }

    printf("**********************************************************\n");
    return 0;
}