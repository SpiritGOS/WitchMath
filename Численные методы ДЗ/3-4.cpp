#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class bad_bracket_end_points {};
class too_many_iteration {};

long root_iteration = 1000000;

bool Symmetry(double** coefficients, int numberOfEquation)
{
	bool check = true;
	int i, j;
	for (i = 0; i < numberOfEquation; i++)
	{
		for (j = i + 1; j < numberOfEquation; j++) 
		{
			if (coefficients[i][j] != coefficients[j][i]) //условие проверки на семетричность
			{
				check = false;
				break;
			}
		}
		if (!check) { break; }
	}
	return check;
}

void Rotation(double** coefficients, int numberOfEquation,double** solution, double precision)
{
	int i,j,k,maxI,maxJ;
	double max, fi;
	double** rotationmatr;
	rotationmatr = new double* [numberOfEquation];
	for (i = 0; i < numberOfEquation; i++)
	{
		rotationmatr[i] = new double[numberOfEquation];
	}
	double** temp;
	temp = new double* [numberOfEquation];
	for (i = 0; i < numberOfEquation; i++) 
	{
		temp[i] = new double[numberOfEquation];
	}
	double fault = 0.0;
	for (i = 0; i < numberOfEquation; i++) 
	{
		for (j = i + 1; j < numberOfEquation; j++) 
		{
			fault = fault + coefficients[i][j] * coefficients[i][j];
		}
	}
	fault = sqrt(2 * fault);
	while (fault > precision)//условия для соблюдения точности
	{
		max = 0.0;
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = i + 1; j < numberOfEquation; j++) 
			{
				//вычисляем макс. положительный коэф. а также макс. значения счетчиков для передвижения по матрице
				if (coefficients[i][j] > 0 && coefficients[i][j] > max) 
				{
					max = coefficients[i][j];
					maxI = i;
					maxJ = j;
				}
				//вычисляем макс. отрицательный коэф. а также макс. значения счетчиков для передвижения по матрице
				else if (coefficients[i][j] < 0 && -coefficients[i][j] > max) 
				{
					max = -coefficients[i][j];
					maxI = i;
					maxJ = j;
				}
			}
		}
		//обнуляем матрицу поворота
		for (i = 0; i < numberOfEquation; i++) 
        {
			for (j = 0; j < numberOfEquation; j++) 
            {
				rotationmatr[i][j] = 0;
			}
			rotationmatr[i][i] = 1;
		}
		if (coefficients[maxI][maxI] == coefficients[maxJ][maxJ]) 
        {
			rotationmatr[maxI][maxI] = rotationmatr[maxJ][maxJ] =
				rotationmatr[maxJ][maxI] = sqrt(2.0) / 2.0;
			rotationmatr[maxI][maxJ] = -sqrt(2.0) / 2.0;
		}
		else 
        {
			//вычисляем угол поворота ф
			fi = 0.5 * atan((2.0 * coefficients[maxI][maxJ]) /(coefficients[maxI][maxI] - coefficients[maxJ][maxJ]));
			//строим матрицу поворота H
			rotationmatr[maxI][maxI] = rotationmatr[maxJ][maxJ] = cos(fi);
			rotationmatr[maxI][maxJ] = -sin(fi);
			rotationmatr[maxJ][maxI] = sin(fi);
		}
		for (i = 0; i < numberOfEquation; i++)
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				temp[i][j] = 0.0;//массив temp нужен для вывода собственных значений векторов
			}
		} 
		//перемножение матриц
		for (i = 0; i < numberOfEquation; i++)
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				for (k = 0; k < numberOfEquation; k++)
				{
					temp[i][j] = temp[i][j] + rotationmatr[k][i] * coefficients[k][j];
				}
			}
		}
		//обнуление изначальной матрицы
		for (i = 0; i < numberOfEquation; i++) {
			for (j = 0; j < numberOfEquation; j++) {
				coefficients[i][j] = 0.0;
			}
		}
		for (i = 0; i < numberOfEquation; i++)
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				for (k = 0; k < numberOfEquation; k++)
				{
					coefficients[i][j] = coefficients[i][j] + temp[i][k] * rotationmatr[k][j];//перезапись коэф. матрицы(также исопльзуются для вывода собственных значений матрицы)
				}
			}
		}
		fault = 0.0;
		for (i = 0; i < numberOfEquation; i++) {
			for (j = i + 1; j < numberOfEquation; j++) {
				fault = fault + coefficients[i][j] * coefficients[i][j];
			}
		}
		fault = sqrt(2 * fault);
		for (i = 0; i < numberOfEquation; i++)
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				temp[i][j] = 0.0;//обнуление вспомогательного массива 
			}
		}
		for (i = 0; i < numberOfEquation; i++)
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				for (k = 0; k < numberOfEquation; k++)
				{
					temp[i][j] = temp[i][j] + solution[i][k] * rotationmatr[k][j];//перезапись в вспомогательный массив
				}
			}
		}
		for (i = 0; i < numberOfEquation; i++) 
		{
			for (j = 0; j < numberOfEquation; j++)
			{
				solution[i][j] = temp[i][j];//перезапись матрицы, которая используется для вывода собственных значенй векторов
			}
		}
	}
}

double** F_Input(const char* f, unsigned int& size)
{
	string buf;
	ifstream fl;
	fl.open((char*)f);
	if (!fl.is_open())
		cout << "\nThat's great!\n";
	getline(fl, buf ,'\n');
	size = stoi(buf);
	double **mat = new double*[size];
	for (int i = 0; i < size; i++)
		mat[i] = new double[size];
	for (int i = 0; i < size; i++)
	{

		for (int j = 0; j < size - 1; j++)
		{
			getline(fl, buf ,' ');
			mat[i][j] = stod(buf);
		}
			getline(fl, buf ,'\n');
			mat[i][size-1] = stod(buf);
	}
	fl.close();
	return mat;
}

double func(double x) 
{
    return pow(log(fabs(x)), 2) + pow(x+1, 3);
}

double func_g(double x) 
{
    return exp(-pow((x+1), 3/2));

}
bool should_continue(double xn, double xn_1, double xn_2, double f(double x),double eps) 
{
    if ((pow((xn - xn_1), 2) / abs(2 * xn_1 - xn - xn_2)) < eps) {
        if (abs(f(xn)) < eps) 
        {
            return false;
        }
    }
    return true;
}

double Derivative(double f(double x),double x) 
{
    double fc = 3 * pow(x+1, 2) + 2 * log(fabs(x))/x;
    return fc;
}

double Iterativ_method(double f(double x), double g(double x), double a, double b, double eps, vector<double>* x_vals = new vector<double>{}) 
{
    double res = 0;
    double x0 = b;
    double g_p = Derivative(g, x0);
    double next_x = 0;
    double sz = x_vals->size();
    if (g_p < 1) 
    {
        next_x = g(x0);
        x_vals->push_back(next_x);
        if (sz < 3) 
        {
            next_x=Iterativ_method(f, g, a, next_x, eps, x_vals);
        }
        else
        {
            if (should_continue(x_vals->at(sz-1), x_vals->at(sz - 2), x_vals->at(sz - 3),f,eps)) 
            { 
                next_x = Iterativ_method(f, g, a, next_x, eps, x_vals);
            }
        }
        return next_x;
    }
    else 
    {
        cout << "Impossible to calculate with set precision!\n";
        return 0;
    }
}

double Dichotomy (double f(double x), double a, double b, double eps)
{

    double c;
    while (b - a > eps)
    {
        c = (a + b) / 2;
        if(f(b) * f(c) < 0)
            a = c;
        else
            b = c;
    }
    return c;
}

double SecondDerivative(double f(double x), double x) 
{
    double f2 = 6*x+6-2*log(fabs(x))/pow(x,2) + 2*pow(x, -2);
    return f2;
}

double Newton(double f(double x), double a, double b, double eps) 
{
    double c;
    if (f(a) * SecondDerivative(f, a) > 0) {
        c = a;
    }
    else 
    {
        c = b;
    }
    do 
    {
        if (Derivative(f, c) == 0) {
            cout << "Zero division!\n";
            return 0;
        }
        c = c - f(c) / Derivative(f, c);
    } while (abs(f(c)) >= eps);

    return c;
}

int main()
{
	setlocale(LC_ALL, "rus");
	unsigned int size;
	double** solution, eps;
    double** coefficients = F_Input("data3.dat", size);
	solution = new double* [size];
	for (int i = 0; i < size; i++)
    {
		solution[i] = new double[size];
	}
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++) 
		{
			solution[i][j] = 0;
		}
		solution[i][i] = 1;
	}
	eps = 0.01;
	if (!Symmetry(coefficients, size))
	{
		cout << "The matrix is not symmetric";
	}
	else 
    {
		Rotation(coefficients, size, solution, eps);
		cout << "Solution:\n";
		for (int i = 0; i < size; i++) 
		{
			cout << "\nEigenvector №" << i + 1 << ":\n";
			for (int j = 0; j < size; j++) 
            {
				cout << solution[j][i] << "\n";
			}
		}
		cout << "\nEigenvalues:\n";
		for (int i = 0; i < size; i++)
		{
			cout << coefficients[i][i] << "\n";
		}
	}
    double a, b;
    cout << "\na: ";
    cin >> a;
    cout << "b: ";
    cin >> b;
    cout << "Eps: ";
    cin >> eps;
    cout<<"\nDichotomy: " << Dichotomy(func, a,b, eps) << endl;
    cout <<"Newton: " << Newton(func, a, b, eps) << endl;
    cout <<"Iteration: " << Iterativ_method(func,func_g, a, b, eps) << endl;
    return 0;
}