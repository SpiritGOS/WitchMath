#define _USE_MATH_DEFINES
#include <iostream>
#include <vector>
#include <math.h>


using namespace std;

double f(double x) 
{
	return exp(-pow(x,3));
	//return (sin(x));
}

double calc_simpson(double func(double), double a, double b, int n) {
	double h, res = 0.0, sum = 0.0, x;
	h = (b - a) / n;
	res += func(a);
	res += func(b);
	for (int i = 1; i <= n - 1; i += 2) {

		x = a + i * h;
		sum += func(x);
	}

	sum *= 4;
	res += sum;
	sum = 0;
	for (int i = 2; i <= n - 2; i += 2) {
		x = a + i * h;
		sum += func(x);
	}
	sum *= 2;
	res += sum;
	sum = 0;

	res *= (h / 3);

	//cout << "S_" << n << "=" << res << endl;
	return res;
}

double simpson_method(double func(double), double a, double b, int n, double prec) {

	double T1, T2;
	T1 = calc_simpson(func, a, b, n);
	T2 = calc_simpson(func, a, b, 2 * n);
	if (abs(T1 - T2) < prec) {
		return T2;
	}
	else {
		return simpson_method(func, a, b, 2 * n, prec);
	}
}


double calc_trapec(double func(double), double a, double b, int n) {
	double h = (b - a) / n; 
	double T = 0;



	for (int i = 0; i < n + 1; i++) {
		double x1 = a + h * i;
		double x2 = a + h * (i + 1);
		T += 0.5 * (x2 - x1) * (func(x1) + func(x2));
	}
	return T;
}

double  trapec(double func(double), double a, double b, int n, double prec) {
	double T_n = calc_trapec(func, a, b, n);
	double T_2n = calc_trapec(func, a, b, 2 * n);
	if (abs(T_n - T_2n) < prec) {
		return T_2n;
	}
	else {
		return trapec(func, a, b, 2 * n, prec);
	}
}
double calc_rect(double func(double), double a, double b, int n) {
	double h = (b - a) / n;
	double T = 0;
	double sum = (func(a) + func(b)) / 2;



	for (int i = 1; i < n; i++) {
		sum += func(a + i * h);
	}
	T = h * sum;
	return T;
}

double rect(double func(double), double a, double b, int n, double prec) {
	double T_n = calc_rect(func, a, b, n);
	double T_2n = calc_rect(func, a, b, 2 * n);
	if (abs(T_n - T_2n) < prec) {
		return T_2n;
	}
	else {
		return rect(func, a, b, 2 * n, prec);
	}
}
int main()
{
	double a = 0.5;
	double b = 1.0;

	double prec = pow(10, -4);
	int n = 2;
	cout << "Simpson: " << simpson_method(f, a, b, n, prec) << endl;
	cout << "Trapecii: " << trapec(f, a, b, n, prec) << endl;
	cout << "Rectangle: " << rect(f, a, b, n, prec) << endl;
}