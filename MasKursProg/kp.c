#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "kp.h"

int read_x_from_file(FILE* file, double* x) {
    if (fscanf(file, "%lf", x) != 1) {
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