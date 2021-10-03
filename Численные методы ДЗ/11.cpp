#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;
double h = 0.1, a = 0.5 , b = 1.1;

void Finite_difference_method();
double c_F(double X);
double c_L(double X);
vector<double> output(int n, vector<vector<double>> A, vector<double> d);

int main() 
{
    setlocale(LC_ALL, "rus");
    cout << endl << "Решить краевую задачу y'' + y'/x - 4*y = x^2; y(0.5) = 0.5, y(1.1) - 3 * y'(1,1) = 1.3" << endl;
    h = 0.1;
    Finite_difference_method();
    return 0;
    }
    double c_F(double X)
    {
        double F = pow(X, 2);
        return F;
    }
    double c_L(double X)
    {
        double L = 1 / X;
        return L;
    }
    double coefM(double X)
    {
        double M = 1 / X;
        return M;
    }

void Finite_difference_method()
{
    cout << endl << "Метод конечных разностей." << endl;
    int n = 1 + (b - a) / h;
    vector<double> x(n);
    x[0] = a;
    for (int i = 1; i < n - 1; i++) 
    {
        x[i] = x[i - 1] + h;
    }
    x[n - 1] = b;
    vector<vector<double>> matr(n, vector<double>(n));
    vector<double> d(n);
    for (int i = 1; i < n - 1; i++) 
    {
        d[i] = c_F(x[i]);
    }
    d[0] = 0.5;
    d[n - 1] = -3;
    double K = 1, R = 0, S = 1, W = 1, V = -3; //Поменять
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j) 
            {
                double b;
                if (i == 0) 
                {
                    b = -R / h + S;
                }
                    else if (i == n - 1) 
                {
                    b = -V / h - W;
                }
                else 
                {
                    b = -2 * K / pow(h, 2) + coefM(x[i]);
                }
                    matr[i][j] = b;
            }
                else if (j - i == 1) 
            {
                double c;
                if (i == 0) 
                {
                    c = R / h;
                }
                else 
                {
                    c = K / pow(h, 2) + 0.5 * c_L(x[i]) / h;
                }
                    matr[i][j] = c;
            }
            else if (i - j == 1) 
            {
                double a;
                if (i == n - 1) 
                {
                    a = V / h;
                }
                else 
                {
                    a = K / pow(h, 2) - 0.5 * c_L(x[i]) / h;
                }
                    matr[i][j] = a;
            }
        }
    }
vector<double> y = output(n, matr, d);
    for (int i = 0; i < x.size(); i++) 
    {
        cout << "x[" << i + 1 << "] = " << x[i] << "\t" << "y[" << i + 1 << "] = " <<y[i] << endl;
    }
}
vector<double> output(int n, vector<vector<double>> A, vector<double> d) 
{
    vector<double> X(n);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if ((j != i && j != i - 1 && j != i + 1) && A[i][j] != 0) 
            {
                cout << "\n Данная матрица не является трёхдиагональной!\n";
                return X;
            }   
        }
    }
    double* P, * Q;
    double a = 0, b, c;
    P = new double[n + 1];
    Q = new double[n + 1];
    P[0] = 0; // прямой ход метода прогонки
    Q[0] = 0;
    for (int i = 1; i <= n; i++) 
    {
        b = A[i - 1][i - 1];
        if (i != 1) 
        {
            a = A[i - 1][i - 2];
        }
        c = 0;
        if (i < n) 
        {
            c = A[i - 1][i];
        }
        P[i] = -c / (b + a * P[i - 1]);
        Q[i] = (d[i - 1] - a * Q[i - 1]) / (b + a * P[i - 1]);
    }
    X[n - 1] = Q[n];
    for (int i = n - 2; i >= 0; i--) 
    { // обратный ход
        X[i] = Q[i + 1] + P[i + 1] * X[i + 1];
    }
    delete[] P;
    delete[] Q;
    return X;
}