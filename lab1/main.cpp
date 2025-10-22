#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

// Функция f(x) = x * log(x + 1)
double f(double x) {
    return x * log(x + 1);
}

// Функция для формирования Чебышевской сетки
void nodes(const double a, const double b, const int n, std::vector<double>& x_h, std::vector<double>& y_h) {
    x_h.resize(n);
    y_h.resize(n);
    for (int k = 0; k < n; ++k) {
        const double x_cheb = cos((M_PI * (2 * k + 1)) / (2 * n)); // Узлы Чебышева на интервале [-1, 1]
        const double x_new = ((b - a) / 2) * x_cheb + (a + b) / 2;     // Преобразование узлов на интервал [a, b]
        const double y_new = f(x_new);                                 // Вычисление значения функции
        x_h[k] = x_new;
        y_h[k] = y_new;
    }
}

// Функция для вычисления разделенных разностей
std::vector<double> divided_differences(const std::vector<double>& x_h, const std::vector<double>& y_h) {
    const size_t
    n = x_h.size();
    if (n != y_h.size()) {
        throw std::invalid_argument("Sizes of x_h and y_h must be the same");
    }

    std::vector divided_difference(n, std::vector(n, 0.0));
    for (size_t i = 0; i < n; ++i) {
        divided_difference[i][0] = y_h[i];
    }

    for (size_t j = 1; j < n; ++j) {
        for (size_t i = 0; i < n - j; ++i) {
            divided_difference[i][j] = (divided_difference[i + 1][j - 1] - divided_difference[i][j - 1]) / (x_h[i + j] - x_h[i]);
        }
    }

    std::vector<double> dd_forward(n);
    for (size_t i = 0; i < n; ++i) {
        dd_forward[i] = divided_difference[0][i];
    }

    return dd_forward;
}

// Функция для интерполяции Ньютона
std::vector<double> newton_interpolation(const std::vector<double>& x, const std::vector<double>& x_h, const std::vector<double>& dd_forward) {
    size_t n = dd_forward.size();
    std::vector y(x.size(), dd_forward[n - 1]); // Инициализация y последним коэффициентом
    std::vector<double> err(x.size(), 0);

    //for (int i = n - 2; i >= 0; --i) {
    for (size_t j = 0; j < x.size(); ++j) {
        for (int i = n - 2; i >= 0; --i) {
            y[j] = y[j] * (x[j] - x_h[i]) + dd_forward[i];
        }
            err[j] = y[j] - f(x[j]);
    }

    std::cout << "Newton Polynomial values for each x:\n";
    for (size_t i = 0; i < y.size(); ++i) {
        std::cout << "x = " << x[i] << ", y = " << y[i] << ", error =  " << err[i] <<"\n";
    }

    return y;
}

// Функция для генерации равномерно распределенных точек
std::vector<double> linspace(double start, double end, size_t num_points) {
    std::vector<double> result(num_points);
    double step = (end - start) / (num_points - 1);
    for (size_t i = 0; i < num_points; ++i) {
        result[i] = start + i * step;
    }
    return result;
}

int main() {
    const double a = -0.8;
    const double b = 0.8;
    const int n = 8;

    std::vector<double> x_h, y_h;
    nodes(a, b, n, x_h, y_h);

    std::vector<double> dd_forward = divided_differences(x_h, y_h);

    //std::vector<double> x = linspace(x_h[0], x_h[n - 1], 10);
    const std::vector<double> x = {-0.7, -0.25, 0.25, 0.5};
    std::vector<double> y = newton_interpolation(x, x_h, dd_forward);

    return 0;
}
