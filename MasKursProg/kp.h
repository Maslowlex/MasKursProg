#ifndef KP_H
#define KP_H

#include <stdio.h>

#define X_MIN 100.0
#define X_MAX 900.0
#define Q0 45.0
#define TOLERANCE_PERCENT 8.0
#define WARN_PERCENT 20.0
#define N_MEASUREMENTS 70
#define N_ANALYZE 30

#define DATA_FILENAME "data.txt"

#define STATE_NORMAL 0
#define STATE_WARNING 1
#define STATE_ALARM 2

typedef enum {
    READ_OK,       
    READ_EOF,      
    READ_BAD_VALUE  
} ReadStatus;

typedef struct {
    int    count_below;
    double avg_dev;
} Statistics;


ReadStatus read_double(FILE* file, double* x);

int  validate_x(double x);
double calculate_q(double x);
int    get_state_code(double q_val, double* deviation_percent_out);
Statistics compute_statistics(const double q_values[], int count);

#endif /* KP_H */