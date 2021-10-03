#include <iostream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

double f(double x, double y)
{
    return 1 + 0.3 * y * sin(x) - pow(y, 3);
}

map<double, double> Euler(map<double, double> data, double func(double, double), double h) 
{
    double x_i = data.rbegin()->first;
    data[x_i + h] = data[x_i] + h * func(x_i + h / 2.0, data[x_i] + (h / 2.0) * func(x_i, data[x_i]));
    return data;
}

map<double, double> Adams(map<double, double> data, double func(double, double), double h) 
{
    double x_i = data.rbegin()->first;
    data[x_i + h] = data[x_i] + h * (3.0 / 2.0 * func(x_i, data[x_i]) - 1.0 / 2.0 * func(x_i - h, data[x_i - h]));
    return data;
}

map<double,double> calc_Runge4(map<double,double> data,double func(double,double),double h) 
{
    double x_i = data.rbegin()->first;
    double y_i = data.rbegin()->second;

    double  K1 = h * func(x_i, y_i);
    double K2 = h * func(x_i + h / 2, y_i + K1 / 2);
    double  K3 = h * func(x_i + h / 2, y_i + K2 / 2);
    double  K4 = h * func(x_i + h, y_i + K3);
    data[x_i + h] = y_i + (K1 + 2 * K2 + 2 * K3 + K4) / 6;
    cout << data[x_i + h] << endl;
    return data;
}

vector<double> to_vector(map<double, double> data,bool isFirst=true) {
    vector<double> res;
    res.resize(data.size());
    int i = 0;
    for (auto el : data) 
    {
        if (isFirst) 
        {
            res[i] = el.first;
        }
        else 
        {
            res[i] = el.second;
        }
        i++;
    }
    return res;
}

int main()
{
    double x0 = 0;
    double y0 = 0;
    double eps = 0.01;
    double h = 0.1;
    map<double, double> start_data = { {x0,y0} };
    map<double, double> tmp_data = { {x0,y0} };
    double res_h = 0;
    double res_h2 = 0;
    cout << "\nRunge-Kutta:\n";
       do {

        start_data = calc_Runge4(start_data, f, h );
        res_h = tmp_data.crbegin()->second;
        tmp_data = calc_Runge4(tmp_data, f, h/2);
        tmp_data = calc_Runge4(tmp_data, f, h / 2);
        res_h2= tmp_data.crbegin()->second;
       // cout << "h=" << h*2 << "  " << res_h << endl;
       // cout << "h=" << h << "  " << res_h2 << endl;
    } while (abs(res_h - res_h2)/(pow(2,4)-1) > eps);
    for (const auto& el : tmp_data) 
    {
        cout << el.first << "\t" << el.second << endl;
    }
    cout << "\nAdams:\n";
    start_data = { {x0,y0} };
    tmp_data = { {x0,y0} };
    start_data = calc_Runge4(start_data, f, h);
    tmp_data = calc_Runge4(tmp_data, f, h );
    tmp_data = calc_Runge4(tmp_data, f, h );
    do 
    {
        start_data = Adams(start_data, f, h);
        res_h = tmp_data.crbegin()->second;
        tmp_data = Adams(tmp_data, f, h / 2);
        tmp_data = Adams(tmp_data, f, h / 2);
        res_h2 = tmp_data.crbegin()->second;
    } while (abs(res_h - res_h2) / (pow(2, 2) - 1) > eps);
    for (const auto& el : tmp_data) 
    {
        cout << el.first << "\t" << el.second << endl;
    }
    cout << "\nEuler:\n";
    start_data = { {x0,y0} };
    tmp_data = { {x0,y0} };
    do 
    {

        start_data = Euler(start_data, f, h);
        res_h = tmp_data.crbegin()->second;
        tmp_data = Euler(tmp_data, f, h / 2);
        tmp_data = Euler(tmp_data, f, h / 2);
        res_h2 = tmp_data.crbegin()->second;
    } while (abs(res_h - res_h2) / (pow(2, 1) - 1) > eps);
    for (const auto& el : tmp_data) 
    {
        cout << el.first << "\t" << el.second << endl;
    }
}