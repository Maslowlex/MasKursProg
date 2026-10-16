#define _CRT_SECURE_NO_WARNINGS
#define M_PI 3.14159265358979323846
#include <stdio.h>
#include <locale.h>
#include <math.h>
double Q(double x);
int main() {
	setlocale(LC_ALL, "RUS");
	double x;
	printf("Введите X: ");
	scanf("%lf", &x);
	printf("Q(%.4lf) = %.4lf\n", x, Q(x));
}
double Q(double x) {
	if (x < 350) {
		return 2 * (x - 350) + 5;
	}
	else if (x >= 350 && x <= 650) {
		return 0.5 * pow(x - 500, 2) + 45;
	}
	else {
		return 2 * log(x - 650 * 2) + 60;
	}
}