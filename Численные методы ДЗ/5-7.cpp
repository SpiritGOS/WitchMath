#include <iostream>
#include <math.h>
#include <vector>
#include <valarray>
#include <fstream>

using namespace std;

double** Input(unsigned int& size)
{
	cout << "\nEnter size of matrix: "; cin >> size;

	double** A = new double* [2];
	for (int i = 0; i < size; i++)
		A[i] = new double[size];

	for (int i = 0; i < 2; i++)
	{

		for (int j = 0; j < size; j++)
		{
			cout << "Enter A[" << i << "][" << j << "]: "; cin >> A[i][j];
		}
		cout << endl;
	}

	return A;
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
	double **mat = new double*[2];
	for (int i = 0; i < 2; i++)
		mat[i] = new double[size];
	for (int i = 0; i < 2; i++)
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

int fact(int x)
{
	return x == 1 or 0 ? 1 : x * fact(x - 1);
}

double* gauss(double** a, int n)
{
	double* x, max;
	int k, index;
	const double eps = 0.00001;
	x = new double[n];
	k = 0;
	while (k < n)
	{
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		if (max < eps)
		{
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = a[k][2];
		a[k][2] = a[index][2];
		a[index][2] = temp;
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			a[i][2] = a[i][2] / temp;
			if (i == k)  continue;
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			a[i][2] = a[i][2] - a[k][2];
		}
		k++;
	}
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = a[k][2];
		for (int i = 0; i < k; i++)
			a[i][2] = a[i][2] - a[i][k] * x[k];
	}
	return x;
}

vector<double> Progon(vector<vector<double>> a) {
	int n = a.size();
	int new_n = a.size()-1;
	double y;
	double* new_a = new double[n];//Прогоночные коэфф
	double* new_b = new double[n]; //Прогоночные коэфф
	vector<double> res(n, 0);//Результат

	//Вычисляем для первой строки
	y = a[0][0]; //Первый элем главной диагонали
	new_a[0] = -a[0][1] / y; //Первые прогоночные коэфф.
	new_b[0] = a[0][n] / y;

	//Используем рекуррентные формулы для расчета прогоночных коэфф.
	for (int i = 1; i < new_n; i++) {
		y = a[i][i] + a[i][i - 1] * new_a[i - 1];
		new_a[i] = -a[i][i + 1] / y;
		new_b[i] = (a[i][n] - a[i][i - 1] * new_b[i - 1]) / y;
	}
	res[new_n] = (a[new_n][n] - a[new_n][new_n - 1] * new_b[new_n - 1]) / (a[new_n][new_n] + a[new_n][new_n - 1] * new_a[new_n - 1]);//Формула для последней строки матрицы
	//Обратная прогонка. Вычисляем неизвестные иксы. 
	for (int i = new_n - 1; i >= 0; i--) {
		res[i] = new_a[i] * res[i + 1] + new_b[i];
	}
	return res;
}

double Newton(double** tab, double x, unsigned size)
{
	int counter = 0;
	cout << "\nNewton interpolation polynomial =";

	for (int i = 0; i < size; i++)
	{
		if (i == 0)
			cout << " f(" << tab[0][0] << ")";
		else
		{
			cout << " + f" << i << "(";
			for (int k = 0; k < i + 1; k++)
			{
				if (k == 0)
					cout << tab[0][k];
				else
					cout << ", " << tab[0][k];
			}	cout << ")";
			for (int k = 0; k < i; k++)
				cout << " * (x - " << tab[0][k] << ")";
			if (i != size - 1)
				cout << " +";
		}
	}
	double tmp = tab[1][0];
	double A[size * 2][size + 1];
	double sum = 0;

	for (int i = 0; i < size * 2; i = i + 2)
		for (int j = 0; j < 2; j++)
		{
			if (j == 0) A[i][j] = tab[0][i / 2];
			else A[i][j] = tab[1][i / 2];
		}

	counter = 1;
	double count2;
	for (int j = 2; j < size + 1; j++, counter++)
	{
		for (int i = 0 + counter; i < size * 2 - counter; i = i + 2)
			A[i][j] = (A[i + 1][j - 1] - A[i - 1][j - 1]) / (A[i + counter][0] - A[i - counter][0]);
	}

	for (int i = 2; i < size + 1; i++)
	{
		count2 = 1;
		for (int k = 0; k < i - 1; k++)
			count2 = count2 * (x - tab[0][k]);

 		sum = sum + A[i - 1][i] * count2;
	}
	tmp += sum;
	cout << endl << "f(" << x << ") = " << tmp << endl;
	return tmp;
}

double Lagrange(double** tab, double x, unsigned size)
{
	double temp = 0, temp2 = 1;
	for (int i = 0; i < size; i++)
	{
		temp2 = 1;
		for (int j = 0; j < size; j++)
		{
			if (j != i)
			{
				temp2 *= (x - tab[0][j]) / (tab[0][i] - tab[0][j]);
			}
		}
		temp += tab[1][i] * temp2;
	}

	cout << "\nLagrange interpolation polynomial = ";
	for (int i = 0; i < size; i++)
	{
		cout << '(' << tab[1][i] << ')';
		for (int k = 0; k < size; k++)
		{
			if (k != i)
			{
				cout << "(x - " << tab[0][k] << ")/(" << tab[0][i] << " - " << tab[0][k] << ")";
				if (k != size - 1 and i != size - 1)
					cout << '*';
			}
		}
		if (i != size - 1)
			cout << '+';
	}

	cout << "\nf(" << x <<") = " << temp << endl;
	return temp;
}

void Spline_method(double **tab, int size)
{
	ofstream fl[size - 2];
	fl[0].open("Spline0.dat");
	fl[1].open("Spline1.dat");
	fl[2].open("Spline2.dat");
	fl[3].open("Spline3.dat");
    vector<double> h(size, 0);
    vector<double> m(size, 0);
    vector<double> Y(size - 1, 0);
    vector<double> P(size, 0);
    vector<double> Q(size, 0);
    for (int i = 1; i < size; i++) 
	{         // вычисляем длины отрезков
        h[i] = tab[0][i] - tab[0][i - 1];
    }
    for (int i = 1; i < size - 1; i++) 
	{    // правые части уравнений для внутренних точек отрезка
        Y[i] = (tab[1][i + 1] - tab[1][i]) / h[i + 1] - (tab[1][i] - tab[1][i - 1]) / h[i];
    }
    P[1] = 0;
    Q[1] = 0;
    for (int i = 2; i < size; i++) 
	{       // прогоночные коэффициенты
        P[i] = -h[i] / (2 * (h[i - 1] + h[i]) + P[i - 1] * h[i - 1]);
        Q[i] = (6 * Y[i - 1] - h[i - 1] * Q[i - 1]) / (2 * (h[i - 1] + h[i]) + P[i - 1] * h[i - 1]);
    }
    m[0] = 0;
    m[size -1] = 0;
    for (int i = size - 2; i > 0; i--) 
	{
        m[i - 1] = P[i] * m[i] + Q[i];
    }
    for (int i = 1; i < size - 1; i++) 
	{
        cout << endl << endl << "S" << i + 1 << "(x) = ";
        double k1 = m[i] / (6 * h[i]), k2, k3, k4, rez;
        if (k1 != 0) {
            cout << k1 << "*(x";
            if (tab[0][i - 1] >= 0) 
			{
                cout << "-" << fabs(tab[0][i - 1]) << ")^3";
            }
            else 
			{
                cout << "+" << fabs(tab[0][i - 1]) << ")^3";
            }
        }
        k2 = m[i - 1] / (6 * h[i]);
        if (k2 != 0) {
            if (k2 < 0) {
                cout << " - ";
            }
            else if (k1 != 0) 
			{
                cout << " + ";
            }
            cout << fabs(k2) << "*(" << tab[0][i] << "-x)^3";
        }
        k3 = (tab[1][i] - m[i] * pow(h[i], 2) / 6) / h[i];
        k4 = (tab[1][i - 1] - m[i - 1] * pow(h[i], 2) / 6) / h[i];
        double pr, prx;
        pr = -k3 * tab[0][i - 1] + k4 * tab[0][i];
        prx = k3 - k4;
        if (prx < 0) 
		{
            cout << " - " << fabs(prx) << "*x";
        }
        else if (prx > 0) 
		{
            cout << " + " << fabs(prx) << "*x";
        }
        if (pr < 0) 
		{
            cout << " - " << fabs(pr);
        }
        else if (pr > 0) 
		{
            cout << " + " << fabs(pr);
        }
		for (double g = tab[0][i-1]; g <= tab[0][i]; g+=0.00001)
		{
			rez = k1 * pow((g - tab[0][i - 1]), 3) + k2 * pow((tab[0][i] - g), 3) + k3 * (g - tab[0][i - 1]) + k4 * (tab[0][i] - g);
			fl[i-1] << g << '\t' << rez << '\n';
		}
    }
	cout << endl;
	fl[0].close();
	fl[1].close();
	fl[2].close();
	fl[3].close();
}

void Linear_approximation(double** tab, unsigned size, double xx)
{
	double x = 0, x2 = 0, y = 0, xy = 0;
	for (int i = 0; i < size; i++)
	{
		x += tab[0][i];
		x2 += tab[0][i] * tab[0][i];
		y += tab[1][i];
		xy += tab[0][i] * tab[1][i];
	}

	double **syst = new double* [2];
	for (int i = 0; i < 2; i++)
		syst[i] = new double [3];

	syst[0][0] = x2;
	syst[0][1] = x;
	syst[0][2] = xy;
	syst[1][0] = x;
	syst[1][1] = size;
	syst[1][2] = y;

	double *ans = gauss(syst, 2);
	cout << "\nLinear approximation:\n";
	cout << "Coefs are:\n";
	cout << "b = " << ans[0] << endl;
	cout << "c = " << ans[1] << endl;

	cout << "Answer = " << ans[0] * xx + ans[1] << endl;
}

void Square_approximation(double **tab, unsigned size, double xx)
{
	vector<double> coef(7, 0);
	vector<double> res(3, 0);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < size; j++)
			coef[i]+=pow(tab[0][j], i+1);
	for (int i = 4; i < 7; i++)
		for(int j = 0; j < size; j++)
			coef[i] += tab[1][j]*pow(tab[0][j], i - 4);
	vector<vector<double>> syst(3);
	for (int i = 0; i < 3; i++)
	{
		syst[i].resize(4);
		for (int j = 0; j < 3; j++)
		{
			if(j==2 && i==2)
			{
				syst[i][j] = size;
			}
			else
			{
				syst[i][j] = coef[3-j-i];
			}
		}
		syst[i][3] = coef[6 - i];
	}
	res = Progon(syst);
	cout << "\nSquare approximation:\n";
	cout << "Coefs are:\n";
	cout << "a = " << res[0] << endl;
	cout << "b = " << res[1] << endl;
	cout << "x = " << res[2] << endl;
	cout << "Answer =" << res[0] * pow(xx, 2) + res[1] * xx + res[2] << endl;
}

int main()
{
	unsigned size;
	double x;

	double** a = F_Input("data.dat", size);

	ofstream fl;
	fl.open("Newton.dat");
	if(fl.is_open())
		cout << "\nIt's finally open!\n";
	for (double x = a[0][0]; x <= a[0][size-1]; x+=0.001)
	{
		double y = Newton(a, x, size);
		fl << x <<"\t" << y << "\n";
	}
	fl.close();

	fl.open("Lagrange.dat");
	if(fl.is_open())
		cout << "\nIt's finally open!\n";
	for (double x = a[0][0]; x <= a[0][size-1]; x+=0.001)
	{
		double y = Lagrange(a, x, size);
		fl << x <<"\t" << y << "\n";
	}
	fl.close();
	system("gnuplot --persist -e 'plot \"Newton.dat\" u 1:2 w l title \"Newton\", \"Lagrange.dat\" u 1:2 w l title \"Lagrange\"'");

	cout << endl << Lagrange(a, 1.27200, size) - Newton(a, 1.27201, size); 

	cout << "\n\nSpline method:";

	Spline_method(a, size);
	system("gnuplot --persist -e 'plot \"Spline0.dat\" u 1:2 w l title \"Spline2\", \"Spline1.dat\" u 1:2 w l title \"Spline3\", \"Spline2.dat\" u 1:2 w l title \"Spline4\", \"Spline3.dat\" u 1:2 w l title \"Spline5\"'");
	
	a = F_Input("data7.dat" ,size);
	Linear_approximation(a, size, 1);

	Square_approximation(a, size, 1);

	return 0;
}