#include <cmath>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <windows.h>
#include <stdio.h>


using namespace std;

/*
Решаем ДУ y'= y^2*exp(x) - 2y на отрезке x из [-1, 1].
Точное решение y = exp(-x)
Начальные условия: y(-1) = e
*/

// f(x,y) = y^2*exp(x) -2y
double f(double x, double y){
    return y * y * exp(x) - 2 * y;
}


// Точное решение для сравнения
double exactSolution(double x) {
    return exp(-x);
}

// Функция для создания равномерной сетки на отрезке [a, b]
vector<double> nodes(double a, double b, int num_nodes) {
    vector<double> x(num_nodes);
    double step = (b - a) / (num_nodes - 1);
    for (int i = 0; i < num_nodes; ++i) {
        x[i] = a + i * step;
    }
    return x;
}

// Метод Рунге-Кутты 3-го порядка (α = 1/2) для одного шага
double rungeKuttaStep(double y, double x, double h) {
    double k1 = f(x, y);
    double k2 = f(x + h / 2, y + h * k1 / 2);
    double k3 = f(x + h, y - h * k1 + 2 * h * k2);
    return y + h * (k1 + 4 * k2 + k3) / 6;
}

// Функция метода Рунге-Кутты 3-го порядка на всей сетке
vector<double> rungeKuttaThirdOrder(double a, double b, double y0, int n) {
    vector<double> x = nodes(a, b, n);
    vector<double> y(n);
    y[0] = y0;

    double h = (b - a) / (n - 1);

    for (int i = 0; i < n - 1; ++i) {
        y[i + 1] = rungeKuttaStep(y[i], x[i], h);
    }

    return y;
}


vector<double> solveODEWithAccuracy(double a, double b, double y0, double eps, int initial_n = 2) {
    int n = initial_n;
    vector<double> y_prev, y_curr;
    double max_error;
    int max_iterations = 100; // Защита от бесконечного цикла
    int iterations = 0;

    do {
        iterations++;

        y_prev = rungeKuttaThirdOrder(a, b, y0, n);
        y_curr = rungeKuttaThirdOrder(a, b, y0, 2*n-1);

        n = 2*n-1; // Новое число узлов, чтобы шаг уменьшился в 2 раза
        cout << "Iteration " << iterations << ": n = " << n << endl;

        max_error = 0;
        for (int i = 0; i < y_prev.size(); ++i) {
            int j = 2 * i;
            if (j < y_curr.size()) {
                double error = fabs(y_prev[i] - y_curr[j]) / 7.0;
                if (error > max_error) {
                    max_error = error;
                }
            }
        }
        cout << "Current error: " << max_error << " (target: " << eps << ")" << endl;

    } while (max_error > eps && iterations < max_iterations);

    return y_curr;
}




// Функция для сохранения данных в файл
void saveToFile(const string& filename, const vector<double>& x, const vector<double>& y) {
    ofstream out(filename);
    if (!out) {
        cerr << "Не удалось открыть файл " << filename << " для записи" << endl;
        return;
    }

    out << scientific << setprecision(12);
    for (size_t i = 0; i < x.size(); ++i) {
        out << x[i] << "\t" << y[i] << endl;
    }
    out.close();
}


// Функция для проведения контрольных тестов
void runControlTests() {
    double a = -1.0;
    double b = 1.0;
    double y0 = exp(1.0); // y(-1) = e

    // Тест а: два значения шага (h2 = h1/2)
    {
        int n1 = 5; // Количество узлов для h1 (h1 = 0.5)
        int n2 = 9; // Количество узлов для h2 (h2 = 0.25)

        vector<double> x1 = nodes(a, b, n1);
        vector<double> y1 = rungeKuttaThirdOrder(a, b, y0, n1);
        vector<double> exact_y1(n1);
        vector<double> error1(n1);
        for (int i = 0; i < n1; ++i) {
            exact_y1[i] = exactSolution(x1[i]);
            error1[i] = fabs(y1[i] - exact_y1[i]);
        }

        vector<double> x2 = nodes(a, b, n2);
        vector<double> y2 = rungeKuttaThirdOrder(a, b, y0, n2);
        vector<double> exact_y2(n2);
        vector<double> error2(n2);
        for (int i = 0; i < n2; ++i) {
            exact_y2[i] = exactSolution(x2[i]);
            error2[i] = fabs(y2[i] - exact_y2[i]);
        }

        saveToFile("solution_h1.txt", x1, y1);
        saveToFile("exact_h1.txt", x1, exact_y1);
        saveToFile("error_h1.txt", x1, error1);

        saveToFile("solution_h2.txt", x2, y2);
        saveToFile("exact_h2.txt", x2, exact_y2);
        saveToFile("error_h2.txt", x2, error2);
    }

    // Тест б: зависимость точности от величины шага
    {
        ofstream h_file("h_vs_error.txt");
        ofstream h_p_file("h_p.txt");
        h_file << scientific << setprecision(12);
        h_p_file << scientific << setprecision(12);

        vector<int> n_values = {6, 11, 21, 41, 81, 161, 321, 641};
        for (int n : n_values) {
            double h = (b - a) / (n - 1);
            vector<double> y = rungeKuttaThirdOrder(a, b, y0, n);

            // Вычисляем максимальную ошибку
            double max_error = 0;
            for (int i = 0; i < n; ++i) {
                double x = a + i * h;
                double error = fabs(y[i] - exactSolution(x));
                if (error > max_error) {
                    max_error = error;
                }
            }

            h_file << h << "\t" << max_error << endl;
            h_p_file << h << "\t" << pow(h, 3) << "\t" << pow(h, 4) << endl; // h^p, p=3 для метода 3-го порядка
        }
        h_file.close();
        h_p_file.close();
    }

    // Тест в: Графики зависимости от заданной точности (здесь используем solveODEWithAccuracy)
    {
        ofstream eps_error_file("eps_vs_actual_error.txt");
        ofstream eps_iter_file("eps_vs_iterations.txt");
        vector<double> epsilons = {1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7};

        for (double eps : epsilons) {
            vector<double> y = solveODEWithAccuracy(a, b, y0, eps);
            double h = (b - a) / (y.size() - 1);

            // Вычисляем фактическую ошибку
            double max_actual_error = 0;
            for (int i = 0; i < y.size(); ++i) {
                double x = a + i * h;
                max_actual_error = max(max_actual_error, fabs(y[i] - exactSolution(x)));
            }

            // Число итераций
            int iterations = log2(y.size());

            eps_error_file << eps << "\t" << max_actual_error << endl;
            eps_iter_file << eps << "\t" << iterations << endl;
        }
    }


}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    runControlTests();
    cout << "Контрольные тесты выполнены. Данные сохранены в файлы." << endl;
    return 0;
}
