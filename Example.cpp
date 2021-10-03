#include <iostream>
#include <windows.h>
#include <math.h>

double gauss_matrix[4][4] =
{
	{-8, 5, 8, -6},
	{2, 7, -8, -1},
	{-5, -4, 1, -6},
    {5, -9, -2, 8}
};

double iteration_matrix[4][4] =
{
	{15, 0, 7, 5},
	{-3, -14, -6, 1},
	{-2, 9, 13, 2},
    {4, -1, 3, 9}
};

double rotation_matrix[3][3] =
{
	{-8, 9, 6},
    {9, 9, 1},
    {6, 1, 8}
};

double progonka_matrix[5][5] =
{
	{10, -1, 0, 0, 0},
	{-8, 16, -1, 0, 0},
	{0, 6, -16, 6, 0},
	{0, 0, -8, 16, -5},
    {0, 0, 0, 5, -13}
};

double progonka_vector[5] = {16, -110, 24, -3, 87};

double gauss_vector[4] = { -144, 25, -21, 103 };

double iteration_vector[4] = { 176, -111, 74, 76 };


double* gauss_method(double** A, double* B, int n);
double* itermethod(double** A, double* B, int size);
double* progonka_method(double** A, double* B, int size);
int check_esp(double* xk, double* xk1, int n);
bool simmetry_check(double** coefficients, int size);
void rotation(double** coefficients, int size, double** solution, double precision);
double* zeydel_method (double** A1, double* B1, int zeidelsize);

int main()
{
	double** a, * b, * x, * x1;//x-вектор решение через метод Гаусса, х1- вектор решениечерез метод простых итераций
	int n;
	short int method = 1;
	double** a1, * b1;
	int size;
    double** coefficients, ** solution, eps = 0.01;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("cls");
	while (method != 0)
	{
		std::cout << "Выберите метод решения СЛАУ: \n 1) Метод гаусса\n 2) Метод простых итераций\n 3) Метод прогонки \n 4) Метод вращения \n 5) Метод Зейделя \n 0) выход из программы" << std::endl;
		std::cin >> method;
		system("cls");
		switch (method)
		{
		case 1:
		{
			n = 4;
			a = new double* [n];
			b = new double[n];
			for (int i = 0; i < n; i++)
			{
				a[i] = new double[n];
				for (int j = 0; j < n; j++)
				{
					a[i][j] = gauss_matrix[i][j];
				}
			}
			for (int i = 0; i < n; i++)
			{
				b[i] = gauss_vector[i];
			}
			x = gauss_method(a, b, n);
			std::cout << "Вывод решения методом Гаусса:\n";
			for (int i = 0; i < n; i++)
				std::cout << "x[" << i+1 << "] = " << x[i] << std::endl;
			delete[] b;
			delete[] a;
			std::cout << "\n\n\n\n";
			break;
		}
		case 2:
		{
			size = 4;
			a1 = new double* [size];
			b1 = new double[size];
			for (int i = 0; i < size; i++)
			{
				a1[i] = new double[size];
				for (int j = 0; j < size; j++)
				{
					a1[i][j] = iteration_matrix[i][j];
				}
			}
			for (int i = 0; i < size; i++)
			{
				b1[i] = iteration_vector[i];
			}
			std::cout << "Вывод решения методом простых итераций:\n";
			x1 = itermethod(a1, b1, size);    //Матрица A - должна иметь диагональное преобладание для метода простых итераций
			//Вывод вектора
			for (int i = 0; i < size; i++)
				std::cout << "x[" << i+1 << "] = " << x1[i] << std::endl;
			delete[] b1;
			delete[] a1;
			std::cout << "\n\n\n\n";
			break;
		}
        case 3:
			{
				double** A1, * B1, * progonkaresult;
				int size = 5;
				A1 = new double* [size];
				B1 = new double[size];
				progonkaresult = new double[size];
				for (int i = 0; i < size; i++) //Ввод значений матрицы A
				{
					A1[i] = new double[size];
					for (int j = 0; j < size; j++)
					{
						A1[i][j] = progonka_matrix[i][j];
					}
				}
				for (int i = 0; i < size; i++) //Ввод правой части(матрица B)
				{
					B1[i] = progonka_vector[i];
				}
				progonkaresult = progonka_method(A1, B1, size); // вызов метода прогонки
				std::cout << "Вывод решения методом прогонки:\n";
				for (int i = 0; i < size; i++)
					std::cout << "x[" << i + 1 << "] = " << progonkaresult[i] << std::endl;
				std::cout << "\n\n\n";
				break;
			}
        case 4:
			{
                size = 3;
				coefficients = new double* [size];
				solution = new double* [size];
				for (int i = 0; i < size; i++) {
					coefficients[i] = new double[size];
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
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
					{
						coefficients[i][j] = rotation_matrix[i][j];
					}
				}
				if (!simmetry_check(coefficients, size))
				{
					std::cout << "Матрица не симметричная";
				}
				else {
					rotation(coefficients, size, solution, eps);
					std::cout << "Вывод решения методом вращения:\n";
					for (int i = 0; i < size; i++)
					{
						std::cout << "Собственный вектор x[" << i + 1 << "]:\n";
						for (int j = 0; j < size; j++) {
							std::cout << "\t" << solution[j][i] << ",\n";
						}
					}
					std::cout << "Собственные значения l:\n";
					for (int i = 0; i < size; i++)
					{
						std::cout << "\t" << coefficients[i][i] << ",\n";
					}
				}
				break;
				std::cout << "\n\n\n";
			}
        case 5:
			{
				double** A1, * B1, * Zeidelresult;
				int size = 4;
				A1 = new double* [size];
				B1 = new double[size];
				Zeidelresult = new double[size];
				for (int i = 0; i < size; i++) //Ввод значений матрицы A
				{
					A1[i] = new double[size];
					for (int j = 0; j < size; j++)
					{
						A1[i][j] = iteration_matrix[i][j];
					}
				}
				for (int i = 0; i < size; i++) //Ввод правой части(матрица B)
				{
					B1[i] = iteration_vector[i];
				}
				Zeidelresult = zeydel_method(A1, B1, size); // вызов метода прогонки
				std::cout << "Вывод решения методом Зейделя:\n";
				for (int i = 0; i < size; i++)
					std::cout << "x[" << i + 1 << "] = " << Zeidelresult[i] << std::endl;
				std::cout << "\n\n\n";
				break;
			}
		case 0:
			break;
		default:
		{
			system("cls");
			std::cout << "Такой опции нет. ";
		}
		}
	}
	return 0;
}

double* gauss_method(double** A, double* B, int n)
{
	double* x = new double[n], max;
	int count = 0, ikof;
	const double E = 0.01;
	while (count < n)
	{
		//ищем строки с максимальным значением matrixA[i][b]
		max = fabs(A[count][count]);//находим макс значение эл-ов на главное диагонали
		ikof = count;//сохраняем индекс макс. коэф. в отдельную переменную
		for (int i = count + 1; i < n; i++)//поиск максимального значения эл-ов находящегося после коэф на глав. диагонали b-го столбца
		{
			if (fabs(A[i][count]) > max)//проверка на нахождение макс. коэф. в i строках на j столбце
			{
				max = fabs(A[i][count]);
				ikof = i;
			}
		}
		if (max < E)
		{
			std::cout << "Получить решение СЛАУ невозможно из-за нулевого столбца матрицы";
			std::cout << ikof << "матрицы A" << std::endl;
			return 0;
		}
		//Перестановка строк в матрицы А
		for (int j = 0; j < n; j++)
		{
			double temp = A[count][j];
			A[count][j] = A[ikof][j];
			A[ikof][j] = temp;
		}
		//Перестановка строк в марице B
		double temp = B[count];
		B[count] = B[ikof];
		B[ikof] = temp;
		for (int i = count; i < n; i++)
		{
			double temp = A[i][count];
			if (fabs(temp) < E)
				continue;
			//нормируем ур-ие относительно коэфицента matrix[i][b]
			for (int j = 0; j < n; j++)//цикл деления всех выбранных строк на определенный нами ранее коэф.
				A[i][j] = A[i][j] / temp;//Деление коэф в матрице A
			B[i] = B[i] / temp;//деление коэф. в матрице B
			if (i == count)
				continue;//проверка на то чтобы ур-ие не вычитало само из себя
			for (int j = 0; j < n; j++)//Прямой ход
				A[i][j] = A[i][j] - A[count][j];//вычет одного ур-ия из другого
			B[i] = B[i] - B[count];
		}
		count++;//переход к следующей строке
	}
	//подстановка в уравнение 
	for (count = n - 1; count >= 0; count--)
	{
		x[count] = B[count];
		for (int i = 0; i < count; i++)
			B[i] = B[i] - A[i][count] * x[count];//Нахождение неизвестных
	}
	return x;//возвращаем массив
}

double* itermethod(double** A, double* B, int size)
{
	double* x1 = new double[size]; //первое приближение и результат работы ф-ии
	int i, j;
	for (i = 0; i < size; i++) // вычисляем значение вектора x
		x1[i] = B[i] / A[i][i];
	double E = 0.01;//точность
	double* Xn = new double[size]; // массив, хранящий последующие приближения 
	do
	{
		for (i = 0; i < size; i++) //Метод простых итераций
		{
			Xn[i] = B[i] / A[i][i]; //следующее приближение
			for (j = 0; j < size; j++)
			{
				if (i == j) //проверка на диаг. элемент
					continue; //пропуск шага цикла
				else
					Xn[i] -= A[i][j] / A[i][i] * x1[j]; //вычисляем последующее приближение
			}
		}
		short flag = 1; //считаем, что вектор решений изначально найден
		for (i = 0; i < size - 1; i++) //проверка точности вычисления
		{
			if (fabs(Xn[i] - x1[i]) > E) // Разность по модулю элементов между последующим приближением и предыдущим больше Eps?
			{
				flag = 0; //пока разность по модулю элементов не будет меньше точности, цикл будет прогонятся 
				break; //выход из цикла проверки
			}
		}
		for (i = 0; i < size; i++)
			x1[i] = Xn[i]; // запись   значения последующего приближения в предыдущее для увелечения точности последующих приближений
		if (flag) //Проверка на выход из бесконечного цикла
			break; //выход из беск. цикла
	} while (1);
	return x1;
}

double* progonka_method(double** A, double* B, int size) //Метод Прогонки
{
	double* Result, * before, * current, * after, * Right;
	Right = new double[size];//массив для написания значений вектора B
	Result = new double[size];//массив который будет содержать в себе решение уравнения
	before = new double[size]; //матрица содержит элемент стоящий перед коэф. на главной диагонали (before[0]=0) для каждой строки
	current = new double[size]; //матрица содержит элементы коэф. находящихся на главной диагонали
	after = new double[size]; //матрица содержит элемент стоящий поле коэф. на главной диагонали (after[n-1]=0) для каждой строки
	for (int i = 0; i < size; i++) //переписываем значение коэф. вектора B
		Right[i] = B[i];
	for (int i = 0; i < size; i++) //записываем коэф. матрицы
	{
		if (i == 0)
			before[i] = 0; //частный случай
		else
			before[i] = A[i][i - 1];
		if (i == (size - 1))
			after[i] = 0; //частный случай
		else
			after[i] = A[i][i + 1];
		current[i] = A[i][i];
	}
	//Метод прогонки:
	//Прямой ход
	for (int i = 1; i < size; i++) //определяем прогоночные коэффициенты
	{
		double temp = before[i] / current[i - 1];  // объявляем отношение коэф.
		current[i] = current[i] - temp * after[i - 1];
		Right[i] = Right[i] - temp * Right[i - 1];
	}
	//Обратный ход
	Result[size - 1] = Right[size - 1] / current[size - 1]; //находим частное решение
	for (int i = size - 2; i >= 0; i--) //вычисляем решение уравнения
		Result[i] = (Right[i] - after[i] * Result[i + 1]) / current[i];//в результат записываются искомые корни данного уравнения
	delete[] Right;
	delete[] before;
	delete[] current;
	delete[] after;
	return Result;
}
int check_esp(double* xk, double* xk1, int n) //условие окончание нахождений корней
{
	double eps = 0.001, rez = 0;
	for (int i = 0; i < n; i++)
		rez += (xk[i] - xk1[i]) * (xk[i] - xk1[i]);
	return (sqrt(rez) < eps); // возвращение 0 - решение пока не найдено. 1 - решение найдено
}

bool simmetry_check(double** coefficients, int size) //ф-я определяющая симметрична ли матрица 
/*coefficients - вводимые нами коэф. матрицы;*/
{
	bool check = true;
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = i + 1; j < size; j++)
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
//функция, вращающая матрицу
void rotation(double** coefficients, int size, double** solution, double precision)
/*coefficients - вводимые нами коэф. матрицы; numberofEquations- размер матрицы;
solution - массив предназначений для вывода значений собственных векторов;
precision - точность вычислений эпсилон*/
{
	int i, j, k, maxI, maxJ;
	double max, fi;
	double** rotationmatr;
	rotationmatr = new double* [size];
	for (i = 0; i < size; i++)
	{
		rotationmatr[i] = new double[size];
	}
	double** temp;
	temp = new double* [size];
	for (i = 0; i < size; i++)
	{
		temp[i] = new double[size];
	}
	double fault = 0.0;
	for (i = 0; i < size; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			fault = fault + coefficients[i][j] * coefficients[i][j];
		}
	}
	fault = sqrt(2 * fault);
	while (fault > precision)//условия для соблюдения точности
	{
		max = 0.0;
		for (i = 0; i < size; i++)
		{
			for (j = i + 1; j < size; j++)
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
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				rotationmatr[i][j] = 0;
			}
			rotationmatr[i][i] = 1;
		}
		if (coefficients[maxI][maxI] == coefficients[maxJ][maxJ]) {
			rotationmatr[maxI][maxI] = rotationmatr[maxJ][maxJ] =
				rotationmatr[maxJ][maxI] = sqrt(2.0) / 2.0;
			rotationmatr[maxI][maxJ] = -sqrt(2.0) / 2.0;
		}
		else {
			//вычисляем угол поворота ф
			fi = 0.5 * atan((2.0 * coefficients[maxI][maxJ]) / (coefficients[maxI][maxI] - coefficients[maxJ][maxJ]));
			//строим матрицу поворота H
			rotationmatr[maxI][maxI] = rotationmatr[maxJ][maxJ] = cos(fi);
			rotationmatr[maxI][maxJ] = -sin(fi);
			rotationmatr[maxJ][maxI] = sin(fi);
		}
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				temp[i][j] = 0.0;//массив temp нужен для вывода собственных значений векторов
			}
		}
		//перемножение матриц
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				for (k = 0; k < size; k++)
				{
					temp[i][j] = temp[i][j] + rotationmatr[k][i] * coefficients[k][j];
				}
			}
		}
		//обнуление изначальной матрицы
		for (i = 0; i < size; i++) {
			for (j = 0; j < size; j++) {
				coefficients[i][j] = 0.0;
			}
		}
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				for (k = 0; k < size; k++)
				{
					coefficients[i][j] = coefficients[i][j] + temp[i][k] * rotationmatr[k][j];//перезапись коэф. матрицы(также исопльзуются для вывода собственных значений матрицы)
				}
			}
		}
		fault = 0.0;
		for (i = 0; i < size; i++) {
			for (j = i + 1; j < size; j++) {
				fault = fault + coefficients[i][j] * coefficients[i][j];
			}
		}
		fault = sqrt(2 * fault);
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				temp[i][j] = 0.0;//обнуление вспомогательного массива 
			}
		}
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				for (k = 0; k < size; k++)
				{
					temp[i][j] = temp[i][j] + solution[i][k] * rotationmatr[k][j];//перезапись в вспомогательный массив
				}
			}
		}
		for (i = 0; i < size; i++)
		{
			for (j = 0; j < size; j++)
			{
				solution[i][j] = temp[i][j];//перезапись матрицы, которая используется для вывода собственных значенй векторов
			}
		}
	}
}
double* zeydel_method(double** A1, double* B1, int zeidelsize) //Метод Зейделя
{
	double* x, * p;
	x = new double[zeidelsize]; //массив x- содержит решение
	p = new double[zeidelsize]; // массив p- содержит текущее и предыдущие решения
	for (int i = 0; i < zeidelsize; i++) //задаётся начальное приближение, оно может быть любым
		x[i] = 1;
	do
	{
		for (int i = 0; i < zeidelsize; i++) // в текущее решение записывается предыдущие
			p[i] = x[i];
		for (int i = 0; i < zeidelsize; i++) // в данном цикле высчитываются корни решения
		{
			double temp = 0; //обнуляем значение суммы
			for (int j = 0; j < i; j++)
				temp += (A1[i][j] * x[j]); //вычисляем сумму произведения текущего решения вместе со всеми коэффицентами текущей строки
			for (int j = i + 1; j < zeidelsize; j++)
				temp += (A1[i][j] * p[j]); // вычисляем сумму произведения всех коэф. находящихся на i-ой строке с предыдущим решением
			x[i] = (B1[i] - temp) / A1[i][i]; //Определяем следующее приближение
		}
	} while (!check_esp(x, p, zeidelsize)); //условие окончание нахождений корней
	delete[] p;
	return x;
}