#ifndef KP_H
#define KP_H

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

#endif 