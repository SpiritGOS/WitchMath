#include <iostream>
#include <vector>
#include <valarray>
#include <algorithm>
#include <cmath>
#include <string>


using namespace std;

void Gaus(vector <valarray<double>> a) {
    unsigned n = a.size();
    double coef;
    for (unsigned i = 0; i < n; ++i) {
        unsigned j;
        for (j = i; j < n && a[j][i] == 0; ++j);
        if (j == n) {
            cout << "System has no solution or their quantity is infinity" << endl;
            exit(0);
        }
        else if (i != j)
            swap(a[j], a[i]);
        for (j = 0; j < i; ++j) {
            coef = a[j][i] / a[i][i];
            a[j] -= a[i] * coef;
        }
        for (j = i + 1; j < n; ++j) {
            coef = a[j][i] / a[i][i];
            a[j] -= a[i] * coef;
        }
    }
    for (unsigned i = 0; i < n; ++i) {
        cout << "x_" << i + 1 << " = " << a[i][n] / a[i][i] << endl;
    }
}

void SimpIterations(vector <valarray<double>> a, double eps)
{
    unsigned size = a.size();
    int i, j;
    double B = 0, beta = 0, tmp, dif, E;
    vector<double> x(size,0);
    vector<double> x0(size);
    for (unsigned i = 0; i < a.size(); ++i) {
        tmp = -a[i][i];
        a[i] /= tmp;
        a[i][i] = 0;
        a[i][size] *= -1;
    }

    for (int i = 0; i < size; i++)
        x0[i] = a[i][size];
    int counter = 0;
    do
    {
        for (int i = 0; i < size; i++)
        {
            E = 0;
            x[i] = 0;
            for (int j = 0; j < size; j++)
            {
                x[i] += a[i][j] * x0[j];
                E+= fabs(a[i][j]);
            }
            B = max(B, E);
            x[i] += a[i][size];
            beta = max(beta, a[i][size]);
        }
        int i;
        for (i = 0; i < size; i++)
        {
            x0[i] = x[i];
        }
        dif = pow(B,counter) / (1 - B) * beta;
        counter++;
    } while (dif > eps);
    cout << "Simple Iterations Method:" << endl;
    cout << endl << "Iterations: " << counter << endl << endl;
    for (int i = 0; i < size; i++)
        cout << "x" << i + 1 << " = " << x[i] << " " << endl;
}

vector<double> Zeidel(vector<valarray<double>> v, double epsilon)
{
    unsigned  tmp_unsigned = v[0].size() - 1;
    double B1 = 0, B2 = 0, tmp, beta = 0, norm;
    vector<double> keep, ans(tmp_unsigned), old_ans(tmp_unsigned);
    for (unsigned i = 0; i < v.size(); ++i)
    {
        v[i] /= (-v[i][i]);
        v[i][i] = 0;
        v[i][v[i].size() - 1] *= -1;
    }
    for (unsigned i = 0; i < v.size(); ++i)
    {
        ans[i] = v[i][v[i].size() - 1];
    }
    do
    {
        for (unsigned i = 0; i < ans.size(); ++i)
        {
            old_ans[i] = ans[i];
        }
        ans.assign(ans.size(), 0);
        for (unsigned i = 0; i < tmp_unsigned; ++i) 
        {
            for (unsigned j = 0; j < tmp_unsigned; ++j)
            {
                ans[i] += old_ans[j] * v[i][j];
            }
            ans[i] += v[i][tmp_unsigned];
        }
        norm = 0;
        for (unsigned i = 0; i < ans.size(); ++i)
        {
            norm += pow((ans[i] - old_ans[i]), 2);
        }
        norm = sqrt(norm);
    } while (norm > epsilon);
    return ans;
}

void Progon(vector <valarray<double>> v)
{
    unsigned n = v.size();
    vector <double> P(n + 1), Q(n + 1);
    P[0] = 0;
    Q[0] = 0;
    unsigned step = -1;
    double A, B, C, x, D;
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1)
        {
            A = v[n - 1][n - 2];
            B = v[n - 1][n - 1];
            C = 0;
        }
        else if (i == 0)
        {
            A = 0;
            B = v[0][0];
            C = v[0][1];
        }
        else
        {
            A = v[i][step];
            B = v[i][step + 1];
            C = v[i][step + 2];
        }
        step++;
        D = v[i][n];
        Q[i + 1] = (D - A * Q[i]) / (B + A * P[i]);
        P[i + 1] = (-C) / (B + A * P[i]);
    }
    x = Q[n];
    cout << "Method Progona:" << endl << endl;
    cout << "x" << n << " = " << x << "\n";
    for (int i = 0; i < n; i++)
    {
        x = Q[i] + P[i] * x;
        cout << "x" << i << " = " << x << "\n";
    }
}

template <typename type>
ostream& operator<<(ostream& stream, const vector<type>& v)
{
    int i = 1;
    for(auto el : v)
    {
        stream << "x" << i++ << " = " << el << endl;
    }
    return stream;
}

int main()
{
    setlocale(LC_ALL, "Russian");
	unsigned size = 1;
    vector<int> v ={1, 2, 3};
	cout << "Enter size: "; cin >> size;
	vector<valarray<double>> kaef(size);
	for (int i = 0; i < size; i++)
		kaef[i].resize(size + 1);
        
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size + 1; j++){
            cout << "kaef [" << i+1 << "][" << j+1 << "] = ";
            cin >> kaef[i][j];
        }
	}

    Gaus(kaef);
    cout << endl;
    Progon(kaef);
    vector<double> ans;
    ans = Zeidel(kaef, 0.01);
    cout << "\nZeidel Method:" << endl;
    cout << endl << ans << endl;
    SimpIterations(kaef, 0.001);
}