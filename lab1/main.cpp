#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <windows.h>

using namespace std;

// Алгебраическое уравнение: x^4 - 3x^2 + 75x - 9999 = 0
double f_algebraic(double x) {
    return x*x*x*x - 3*x*x + 75*x - 9999;
}

// Трансцендентное уравнение: 3x - 4ln(x) - 5 = 0
double f_transcendental(double x) {
    return 3*x - 4*log(x) - 5;
}

// Итерационные функции для алгебраического уравнения
double phi_algebraic_pos(double x) {
    return pow(3*x*x - 75*x + 9999, 0.25);
}

double phi_algebraic_neg(double x) {
    return -pow(3*x*x - 75*x + 9999, 0.25);
}

// Итерационные функции для трансцендентного уравнения
double phi_transcendental1(double x) { // для корня на [1.5, 5]
    return (4*log(x) + 5) / 3;
}

double phi_transcendental2(double x) { // для корня на [0.2, 1.3333]
    return exp((3*x - 5) / 4);
}

// Метод половинного деления
struct BisectionResult {
    double root;
    int iterations;
    vector<double> errors;
};

BisectionResult bisection(double (*f)(double), double a, double b, double epsilon, int max_iter = 1000) {
    BisectionResult result;
    result.iterations = 0;

    if (f(a) * f(b) >= 0) {
        throw invalid_argument("Функция должна иметь разные знаки на концах отрезка");
    }

    double c;
    while ((b - a) >= 2*epsilon && result.iterations < max_iter) {
        c = (a + b) / 2;
        result.errors.push_back(fabs(f(c)));

        if (f(c) == 0.0) {
            break;
        } else if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
        result.iterations++;
    }

    result.root = (a + b) / 2;
    return result;
}

// Метод простых итераций
struct IterationResult {
    double root;
    int iterations;
    vector<double> errors;
    vector<double> approximations;
};

IterationResult simpleIteration(double (*phi)(double), double x0, double epsilon, double q, int max_iter = 1000) {
    IterationResult result;
    result.iterations = 0;
    double x_prev = x0;
    double x_next;

    result.approximations.push_back(x0);
    result.errors.push_back(fabs(phi(x0) - x0));

    do {
        x_next = phi(x_prev);
        result.errors.push_back(fabs(x_next - x_prev));
        result.approximations.push_back(x_next);

        x_prev = x_next;
        result.iterations++;
    } while (result.errors.back() > ((1-q)/q)*epsilon && result.iterations < max_iter);

    result.root = x_next;
    return result;
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

// Тест A: Количество итераций от заданной точности
void runTestA() {

    vector<double> epsilons = {1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10};
    vector<double> iter_bisect_pos, iter_iter_pos, iter_bisect_neg, iter_iter_neg;
    vector<double> iter_bisect_trans1, iter_iter_trans1, iter_bisect_trans2, iter_iter_trans2;


    for (double eps : epsilons) {
        // Алгебраическое уравнение - положительный корень
        auto bisect_pos = bisection(f_algebraic, 0, 15, eps);
        auto iter_pos = simpleIteration(phi_algebraic_pos, 7.5, eps, 0.5);

        // Алгебраическое уравнение - отрицательный корень
        auto bisect_neg = bisection(f_algebraic, -17, 0, eps);
        auto iter_neg = simpleIteration(phi_algebraic_neg, -7.5, eps, 0.5);

        // Трансцендентное уравнение - корень 1
        auto bisect_trans1 = bisection(f_transcendental, 1.5, 5, eps);
        auto iter_trans1 = simpleIteration(phi_transcendental1, 3.0, eps, 0.9);

        // Трансцендентное уравнение - корень 2
        auto bisect_trans2 = bisection(f_transcendental, 0.2, 1.3333, eps);
        auto iter_trans2 = simpleIteration(phi_transcendental2, 0.75, eps, 0.6);

        iter_bisect_pos.push_back(bisect_pos.iterations);
        iter_iter_pos.push_back(iter_pos.iterations);
        iter_bisect_neg.push_back(bisect_neg.iterations);
        iter_iter_neg.push_back(iter_neg.iterations);
        iter_bisect_trans1.push_back(bisect_trans1.iterations);
        iter_iter_trans1.push_back(iter_trans1.iterations);
        iter_bisect_trans2.push_back(bisect_trans2.iterations);
        iter_iter_trans2.push_back(iter_trans2.iterations);

    }

    // Сохранение результатов
    saveToFile("testA_epsilon.txt", epsilons, epsilons);
    saveToFile("testA_bisect_pos.txt", epsilons, iter_bisect_pos);
    saveToFile("testA_iter_pos.txt", epsilons, iter_iter_pos);
    saveToFile("testA_bisect_neg.txt", epsilons, iter_bisect_neg);
    saveToFile("testA_iter_neg.txt", epsilons, iter_iter_neg);
    saveToFile("testA_bisect_trans1.txt", epsilons, iter_bisect_trans1);
    saveToFile("testA_iter_trans1.txt", epsilons, iter_iter_trans1);
    saveToFile("testA_bisect_trans2.txt", epsilons, iter_bisect_trans2);
    saveToFile("testA_iter_trans2.txt", epsilons, iter_iter_trans2);
}







// Тест B: Зависимость погрешности от номера итерации
void runTestB() {

    double epsilon = 1e-10;

    // Алгебраическое уравнение - положительный корень
    auto bisect_pos = bisection(f_algebraic, 0, 15, epsilon);
    auto iter_pos = simpleIteration(phi_algebraic_pos, 7.5, epsilon, 0.5);

    vector<double> bisect_iter_numbers_pos(bisect_pos.errors.size());
    vector<double> iter_numbers_pos(iter_pos.errors.size());
    for (size_t i = 0; i < bisect_iter_numbers_pos.size(); ++i) {
        bisect_iter_numbers_pos[i] = i;
    }
    for (size_t i = 0; i < iter_numbers_pos.size(); ++i) {
        iter_numbers_pos[i] = i;
    }

    // Алгебраическое уравнение - отрицательный корень
    auto bisect_neg = bisection(f_algebraic, -17, 0, epsilon);
    auto iter_neg = simpleIteration(phi_algebraic_neg, -7.5, epsilon, 0.5);

    vector<double> bisect_iter_numbers_neg(bisect_neg.errors.size());
    vector<double> iter_numbers_neg(iter_neg.errors.size());
    for (size_t i = 0; i < bisect_iter_numbers_neg.size(); ++i) {
        bisect_iter_numbers_neg[i] = i;
    }
    for (size_t i = 0; i < iter_numbers_neg.size(); ++i) {
        iter_numbers_neg[i] = i;
    }

    // Трансцендентное уравнение - корень 1
    auto bisect_trans1 = bisection(f_transcendental, 1.5, 5, epsilon);
    auto trans1 = simpleIteration(phi_transcendental1, 3.0, epsilon, 0.9);

    vector<double> bisect_iter_numbers_trans1(bisect_trans1.errors.size());
    vector<double> iter_numbers_trans1(trans1.errors.size());
    for (size_t i = 0; i < bisect_iter_numbers_trans1.size(); ++i) {
        bisect_iter_numbers_trans1[i] = i;
    }
    for (size_t i = 0; i < iter_numbers_trans1.size(); ++i) {
        iter_numbers_trans1[i] = i;
    }

    // Трансцендентное уравнение - корень 2
    auto bisect_trans2 = bisection(f_transcendental, 0.2, 1.3333, epsilon);
    auto trans2 = simpleIteration(phi_transcendental2, 0.75, epsilon, 0.6);

    vector<double> bisect_iter_numbers_trans2(bisect_trans2.errors.size());
    vector<double> iter_numbers_trans2(trans2.errors.size());
    for (size_t i = 0; i < bisect_iter_numbers_trans2.size(); ++i) {
        bisect_iter_numbers_trans2[i] = i;
    }
    for (size_t i = 0; i < iter_numbers_trans2.size(); ++i) {
        iter_numbers_trans2[i] = i;
    }

    // Сохранение результатов
    saveToFile("testB_bisect_pos.txt", bisect_iter_numbers_pos, bisect_pos.errors);
    saveToFile("testB_iter_pos.txt", iter_numbers_pos, iter_pos.errors);
    saveToFile("testB_bisect_neg.txt", bisect_iter_numbers_neg, bisect_neg.errors);
    saveToFile("testB_iter_neg.txt", iter_numbers_neg, iter_neg.errors);
    saveToFile("testB_bisect_trans1.txt", bisect_iter_numbers_trans1, bisect_trans1.errors);
    saveToFile("testB_iter_trans1.txt", iter_numbers_trans1, trans1.errors);
    saveToFile("testB_bisect_trans2.txt", bisect_iter_numbers_trans2, bisect_trans2.errors);
    saveToFile("testB_iter_trans2.txt", iter_numbers_trans2, trans2.errors);

}


// Тест C: Зависимость фактической ошибки от заданной точности
void runTestC() {

    vector<double> epsilons = {1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10};
    vector<double> actual_errors_bisect_pos, actual_errors_iter_pos;
    vector<double> actual_errors_bisect_neg, actual_errors_iter_neg;
    vector<double> actual_errors_bisect_trans1, actual_errors_iter_trans1;
    vector<double> actual_errors_bisect_trans2, actual_errors_iter_trans2;

    // Известные корни (приближенные значения)
    double true_root_pos = 9.885744988278;   // Положительный корень алгебраического уравнения
    double true_root_neg = -10.260725414297;  // Отрицательный корень алгебраического уравнения
    double true_root_trans1 = 3.229959439728;  // Корень трансцендентного уравнения на [1.5, 5]
    double true_root_trans2 = 0.381376808649;  // Корень трансцендентного уравнения на [0.2, 1.3333]


    for (double eps : epsilons) {
        // Алгебраическое уравнение - положительный корень
        auto bisect_pos = bisection(f_algebraic, 0, 15, eps);
        auto iter_pos = simpleIteration(phi_algebraic_pos, 7.5, eps, 0.5);

        // Алгебраическое уравнение - отрицательный корень
        auto bisect_neg = bisection(f_algebraic, -17, 0, eps);
        auto iter_neg = simpleIteration(phi_algebraic_neg, -7.5, eps, 0.5);

        // Трансцендентное уравнение - корень 1
        auto bisect_trans1 = bisection(f_transcendental, 1.5, 5, eps);
        auto iter_trans1 = simpleIteration(phi_transcendental1, 3.0, eps, 0.9);

        // Трансцендентное уравнение - корень 2
        auto bisect_trans2 = bisection(f_transcendental, 0.2, 1.3333, eps);
        auto iter_trans2 = simpleIteration(phi_transcendental2, 0.75, eps, 0.6);

        actual_errors_bisect_pos.push_back(fabs(bisect_pos.root - true_root_pos));
        actual_errors_iter_pos.push_back(fabs(iter_pos.root - true_root_pos));
        actual_errors_bisect_neg.push_back(fabs(bisect_neg.root - true_root_neg));
        actual_errors_iter_neg.push_back(fabs(iter_neg.root - true_root_neg));
        actual_errors_bisect_trans1.push_back(fabs(bisect_trans1.root - true_root_trans1));
        actual_errors_iter_trans1.push_back(fabs(iter_trans1.root - true_root_trans1));
        actual_errors_bisect_trans2.push_back(fabs(bisect_trans2.root - true_root_trans2));
        actual_errors_iter_trans2.push_back(fabs(iter_trans2.root - true_root_trans2));

    }

    // Сохранение результатов
    saveToFile("testC_epsilon.txt", epsilons, epsilons);
    saveToFile("testC_actual_bisect_pos.txt", epsilons, actual_errors_bisect_pos);
    saveToFile("testC_actual_iter_pos.txt", epsilons, actual_errors_iter_pos);
    saveToFile("testC_actual_bisect_neg.txt", epsilons, actual_errors_bisect_neg);
    saveToFile("testC_actual_iter_neg.txt", epsilons, actual_errors_iter_neg);
    saveToFile("testC_actual_bisect_trans1.txt", epsilons, actual_errors_bisect_trans1);
    saveToFile("testC_actual_iter_trans1.txt", epsilons, actual_errors_iter_trans1);
    saveToFile("testC_actual_bisect_trans2.txt", epsilons, actual_errors_bisect_trans2);
    saveToFile("testC_actual_iter_trans2.txt", epsilons, actual_errors_iter_trans2);
}





// Тест D: Зависимость количества итераций от начального приближения
void runTestD() {

    double epsilon = 1e-8;

    // Алгебраическое уравнение - положительный корень
    vector<double> x0_pos = {1.0, 3.0, 5.0, 7.5, 10.0, 12.0, 14.0};
    vector<double> iter_bisect_pos, iter_iter_pos;

    for (double x0 : x0_pos) {
        auto bisect_result = bisection(f_algebraic, 0, 15, epsilon);
        auto iter_result = simpleIteration(phi_algebraic_pos, x0, epsilon, 0.5);

        iter_bisect_pos.push_back(bisect_result.iterations);
        iter_iter_pos.push_back(iter_result.iterations);


    }

    // Алгебраическое уравнение - отрицательный корень
    vector<double> x0_neg = {-1.0, -3.0, -5.0, -7.5, -10.0, -12.0, -14.0};
    vector<double> iter_bisect_neg, iter_iter_neg;

    for (double x0 : x0_neg) {
        auto bisect_result = bisection(f_algebraic, -17, 0, epsilon);
        auto iter_result = simpleIteration(phi_algebraic_neg, x0, epsilon, 0.5);

        iter_bisect_neg.push_back(bisect_result.iterations);
        iter_iter_neg.push_back(iter_result.iterations);

    }

    // Трансцендентное уравнение - корень 1
    vector<double> x0_trans1 = {1.6, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5};
    vector<double> iter_bisect_trans1, iter_iter_trans1;

    for (double x0 : x0_trans1) {
        auto bisect_result = bisection(f_transcendental, 1.5, 5, epsilon);
        auto iter_result = simpleIteration(phi_transcendental1, x0, epsilon, 0.9);

        iter_bisect_trans1.push_back(bisect_result.iterations);
        iter_iter_trans1.push_back(iter_result.iterations);

    }

    // Трансцендентное уравнение - корень 2
    vector<double> x0_trans2 = {0.3, 0.5, 0.7, 0.9, 1.1, 1.3};
    vector<double> iter_bisect_trans2, iter_iter_trans2;


    for (double x0 : x0_trans2) {
        auto bisect_result = bisection(f_transcendental, 0.2, 1.3333, epsilon);
        auto iter_result = simpleIteration(phi_transcendental2, x0, epsilon, 0.6);

        iter_bisect_trans2.push_back(bisect_result.iterations);
        iter_iter_trans2.push_back(iter_result.iterations);

    }

    // Сохранение результатов
    saveToFile("testD_x0_pos.txt", x0_pos, x0_pos);
    saveToFile("testD_bisect_pos.txt", x0_pos, iter_bisect_pos);
    saveToFile("testD_iter_pos.txt", x0_pos, iter_iter_pos);

    saveToFile("testD_x0_neg.txt", x0_neg, x0_neg);
    saveToFile("testD_bisect_neg.txt", x0_neg, iter_bisect_neg);
    saveToFile("testD_iter_neg.txt", x0_neg, iter_iter_neg);

    saveToFile("testD_x0_trans1.txt", x0_trans1, x0_trans1);
    saveToFile("testD_bisect_trans1.txt", x0_trans1, iter_bisect_trans1);
    saveToFile("testD_iter_trans1.txt", x0_trans1, iter_iter_trans1);

    saveToFile("testD_x0_trans2.txt", x0_trans2, x0_trans2);
    saveToFile("testD_bisect_trans2.txt", x0_trans2, iter_bisect_trans2);
    saveToFile("testD_iter_trans2.txt", x0_trans2, iter_iter_trans2);
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    try {
        runTestA();
        runTestB();
        runTestC();
        runTestD();

        cout << "\nВсе тесты выполнены успешно!" << endl;
        cout << "Данные сохранены в файлы для построения графиков в Python." << endl;

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}
