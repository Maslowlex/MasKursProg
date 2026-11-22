#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "kp.h"

ReadStatus read_double(FILE* file, double* x)
{
    if (fscanf(file, "%lf", x) != 1) {
        if (feof(file)) return READ_EOF;
        return READ_BAD_VALUE;
    }
    return READ_OK;
}

ReadStatus read_manual(double* x)
{
    if (scanf("%lf", x) != 1) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return READ_BAD_VALUE;
    }
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    return READ_OK;
}

int validate_x(double x)
{
    return (x >= X_MIN && x <= X_MAX) ? 1 : 0;
}

double calculate_q(double x)
{
    if (x < 350.0) {
        return 2.0 * (x - 350.0) + 5.0;
    }
    else if (x <= 650.0) {
        return 0.5 * (x - 500.0) * (x - 500.0) + 45.0;
    }
    else {
        return 2.0 * log(x - 650.0 + 2.0) + 60.0;
    }
}

int get_state_code(double q_val, double* deviation_percent_out)
{
    double tolerance = Q0 * (TOLERANCE_PERCENT / 100.0);
    double lower_bound = Q0 - tolerance;
    double upper_bound = Q0 + tolerance;

    double diff = fabs(q_val - Q0);
    if (deviation_percent_out) {
        *deviation_percent_out = (diff / Q0) * 100.0;
    }

    if (q_val >= lower_bound && q_val <= upper_bound) {
        return STATE_NORMAL;
    }
    if (diff / Q0 * 100.0 <= WARN_PERCENT) {
        return STATE_WARNING;
    }
    return STATE_ALARM;
}

Statistics compute_statistics(const double q_values[], int count)
{
    Statistics s = { 0, 0.0 };
    if (count <= 0) return s;

    double sum = 0.0;
    for (int i = 0; i < count; i++) {
        if (q_values[i] < Q0) s.count_below++;
        sum += fabs(q_values[i] - Q0);
    }
    s.avg_dev = sum / count;
    return s;
}
void print_state(int state_code) {
    switch (state_code) {
    case STATE_NORMAL:  printf("Норма\n");           break;
    case STATE_WARNING: printf("ПРЕДУПРЕЖДЕНИЕ\n");  break;
    case STATE_ALARM:   printf("ТРЕВОГА\n");         break;
    }
}