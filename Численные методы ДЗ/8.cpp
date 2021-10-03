#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

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

double lagrange(double** vals, unsigned size, double param) {
	double res = 0;
	int n = size;
	double tmp = 0;
	for (int i = 0; i < n; ++i)
    {
		tmp = vals[1][i];
		for (int j = 0; j < n; ++j) 
        {
			if (i == j) continue; 
			tmp *= (param - vals[0][j]);
		}
		for (int j = 0; j < n; ++j) 
        {
			if (i == j) continue;
			tmp /= (vals[0][i] - vals[0][j]);
			if (j != n - 1) {
			}
		}
		res += tmp;
	}

	return res;
}
double Derivative(double** data, unsigned size, double x) {
	double min_x = data[0][0];
	double max_x = data[0][size -1];
	double h = data[0][1] - data[0][0];
	double y = lagrange(data, size, x);
	if (x+h<=max_x) 
    {
		return (lagrange(data, size, x+h)-y) / h;
	}
	else 
    {
		return (y - lagrange(data, size, x - h)) / h;
	}
}
double Second_Derivative(double** data, unsigned size, double x) {
	double min_x = data[0][0];
	double max_x = data[0][size - 1];
	double h = data[0][1] - data[0][0];
	double y = lagrange(data, size, x);
	return ((lagrange(data, size, x + h) - 2 * y + lagrange(data, size, x - h))) /( h * h);
}

int main()
{
	unsigned size;
	double** vals = F_Input("data.dat", size);
	double param1 = 0.1272;
	double param2 = 1.2600;
	cout << "f'(" << param1 << ") =" << Derivative(vals, size, param1) << endl;
	cout << "f''(" << param1 << ") =" << Second_Derivative(vals, size, param1) << endl;
	cout << "f'(" << param2 << ") =" << Derivative(vals, size, param2) << endl;
	cout << "f''(" << param2 << ") =" << Second_Derivative(vals, size, param2) << endl;
}