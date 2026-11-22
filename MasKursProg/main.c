#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include "kp.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    printf("**********************************************************\n");
    printf("*        СИСТЕМА МОНИТОРИНГА СКОРОСТИ ПЕРЕМЕШИВАНИЯ      *\n");
    printf("**********************************************************\n");
    printf("*     Автор: Маслов А.Е., группа бИЦТ-262                *\n");
    printf("*     Тема: Обработка потока данных из файла             *\n");
    printf("* Условие: Расчет Q(X), контроль состояния и статистика  *\n");
    printf("**********************************************************\n\n");

    printf("Проверка контрольного примера: X = 425.0 -> Q = %.2lf\n", calculate_q(425.0));
    printf("Ожидается: 2857.50\n\n");

    while (1) {
        printf("\n==========================================================\n");
        printf("                     ГЛАВНОЕ МЕНЮ\n");
        printf("==========================================================\n");
        printf("1. Чтение данных из файла (%s)\n", DATA_FILENAME);
        printf("2. Ручной ввод значений с клавиатуры\n");
        printf("3. Выход из программы\n");
        printf("Ваш выбор: ");

        int choice = 0;
        if (scanf("%d", &choice) != 1) {
            printf("Ошибка ввода. Введите число от 1 до 3.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choice == 3) {
            printf("Завершение работы программы. До свидания!\n");
            break;
        }
        else if (choice == 2) {
            printf("\n--- РЕЖИМ РУЧНОГО ВВОДА ---\n");
            printf("Введите значение X (от %.0f до %.0f).\n", X_MIN, X_MAX);
            printf("Для возврата в главное меню введите 0.\n\n");

            double x = 0.0;
            while (1) {
                printf("Введите X: ");
                ReadStatus status = read_manual(&x);

                if (status != READ_OK) {
                    printf("Ошибка: введено не число. Попробуйте еще раз.\n");
                    continue;
                }

                if (x == 0) {
                    printf("Возврат в главное меню.\n");
                    break;
                }

                if (!validate_x(x)) {
                    printf("Ошибка: X должен быть в диапазоне [%.0f; %.0f].\n", X_MIN, X_MAX);
                    continue;
                }

                double q_val = calculate_q(x);
                double deviation_percent = 0.0;
                int state_code = get_state_code(q_val, &deviation_percent);

                printf("  -> Q = %.4lf | Отклонение: %.2lf%% | Состояние: ", q_val, deviation_percent);
                print_state(state_code);
                printf("----------------------------------------\n");
            }
            continue;
        }
        else if (choice == 1) {
            printf("\nПопытка открыть файл с данными: %s\n", DATA_FILENAME);

            FILE* file = fopen(DATA_FILENAME, "r");
            if (!file) {
                printf("ОШИБКА: Не удалось открыть файл %s.\n", DATA_FILENAME);
                printf("Убедитесь, что файл существует в папке с программой.\n");
                continue;
            }

            printf("Файл успешно открыт. Начинаем обработку...\n");
            printf("----------------------------------------------------------\n");

            double q_array[N_MEASUREMENTS];
            double x = 0.0;
            int i = 0;

            while (i < N_MEASUREMENTS) {
                ReadStatus status = read_double(file, &x);

                if (status == READ_EOF) {
                    printf("\n[Конец файла. Прочитано %d значений из %d]\n", i, N_MEASUREMENTS);
                    break;
                }
                if (status == READ_BAD_VALUE) {
                    printf("\n[ОШИБКА: строка %d содержит некорректные данные (не число)]\n", i + 1);
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
                print_state(state_code);

                i++;
            }

            fclose(file);
            printf("----------------------------------------------------------\n");

            int analyze_count = (i < N_ANALYZE) ? i : N_ANALYZE;
            if (analyze_count > 0) {
                printf("Статистический анализ (на основе первых %d значений):\n", analyze_count);
                Statistics s = compute_statistics(q_array, analyze_count);
                printf("  Количество значений Q < Q0 (%.1f): %d\n", Q0, s.count_below);
                printf("  Среднее отклонение от Q0: %.4lf\n", s.avg_dev);
            }
            else {
                printf("Недостаточно данных для статистического анализа.\n");
            }
        }
        else {
            printf("Неверный выбор. Пожалуйста, введите 1, 2 или 3.\n");
        }
    }

    printf("**********************************************************\n");
    return 0;
}