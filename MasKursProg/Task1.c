#define _CRT_SECURE_NO_WARNINGS
#define M_PI 3.14159265358979323846
#include <stdio.h>
#include <locale.h>
#include <math.h>
double Q(double x);
int check_control(double q);
int main() {
	setlocale(LC_ALL, "RUS");
	double x;
	double q_val;
	int status;
	printf("Введите X: ");
	scanf("%lf", &x);
	q_val = Q(x);
	printf("Q(%.4lf) = %.4lf\n", x, q_val);
	status = check_control(q_val);
	if (status == 1) {
		printf("Состояние: Норма\n");
	}
	else {
		printf("Состояние: Отклонение\n");
	}
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
int check_control(double q) {
	double Q0 = 45.0;               
	double tolerance = Q0 * 0.08;   
	double lower_bound = Q0 - tolerance; 
	double upper_bound = Q0 + tolerance; 
	printf("Допустимый диапазон: [%.2lf; %.2lf]\n", lower_bound, upper_bound);
	if (q >= lower_bound && q <= upper_bound) {
		return 1; 
	}
	else {
		return 0; 
	}
}