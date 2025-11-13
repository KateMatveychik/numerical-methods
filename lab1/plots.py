import numpy as np
import matplotlib.pyplot as plt

# а) Графики зависимости количества итераций от точности
def plot_iterations_vs_epsilon():
    # Загрузка данных
    epsilons = np.loadtxt('testA_epsilon.txt')
    bisect_pos = np.loadtxt('testA_bisect_pos.txt')
    iter_pos = np.loadtxt('testA_iter_pos.txt')
    bisect_neg = np.loadtxt('testA_bisect_neg.txt')
    iter_neg = np.loadtxt('testA_iter_neg.txt')
    bisect_trans1 = np.loadtxt('testA_bisect_trans1.txt')
    iter_trans1 = np.loadtxt('testA_iter_trans1.txt')
    bisect_trans2 = np.loadtxt('testA_bisect_trans2.txt')
    iter_trans2 = np.loadtxt('testA_iter_trans2.txt')
    
    plt.figure(figsize=(15, 10))
    
    # Алгебраическое уравнение - положительный корень
    plt.subplot(2, 2, 1)
    plt.semilogx(epsilons[:,0], bisect_pos[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.semilogx(epsilons[:,0], iter_pos[:,1], 'ro-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Точность ε')
    plt.ylabel('Количество итераций')
    plt.title('Алгебраическое уравнение (+ корень)')
    plt.legend()
    plt.grid()
    
    # Алгебраическое уравнение - отрицательный корень
    plt.subplot(2, 2, 2)
    plt.semilogx(epsilons[:,0], bisect_neg[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.semilogx(epsilons[:,0], iter_neg[:,1], 'ro-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Точность ε')
    plt.ylabel('Количество итераций')
    plt.title('Алгебраическое уравнение (- корень)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 1
    plt.subplot(2, 2, 3)
    plt.semilogx(epsilons[:,0], bisect_trans1[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.semilogx(epsilons[:,0], iter_trans1[:,1], 'go-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Точность ε')
    plt.ylabel('Количество итераций')
    plt.title('Трансцендентное уравнение (корень 1)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 2
    plt.subplot(2, 2, 4)
    plt.semilogx(epsilons[:,0], bisect_trans2[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.semilogx(epsilons[:,0], iter_trans2[:,1], 'go-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Точность ε')
    plt.ylabel('Количество итераций')
    plt.title('Трансцендентное уравнение (корень 2)')
    plt.legend()
    plt.grid()
    
    
    plt.tight_layout()
    plt.show()

# б) Графики зависимости погрешности от номера итерации
def plot_error_vs_iteration():
    # Загрузка данных
    bisect_pos = np.loadtxt('testB_bisect_pos.txt')
    iter_pos = np.loadtxt('testB_iter_pos.txt')
    bisect_neg = np.loadtxt('testB_bisect_neg.txt')
    iter_neg = np.loadtxt('testB_iter_neg.txt')
    bisect_trans1 = np.loadtxt('testB_bisect_trans1.txt')
    iter_trans1 = np.loadtxt('testB_iter_trans1.txt')
    bisect_trans2 = np.loadtxt('testB_bisect_trans2.txt')
    iter_trans2 = np.loadtxt('testB_iter_trans2.txt')
    
    plt.figure(figsize=(12, 8))
    
    # Алгебраическое уравнение - положительный корень
    plt.subplot(2, 2, 1)
    plt.semilogy(bisect_pos[:,0], bisect_pos[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.semilogy(iter_pos[:,0], iter_pos[:,1], 'ro-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Номер итерации')
    plt.ylabel('Погрешность')
    plt.title('Алгебраическое уравнение (+ корень)')
    plt.legend()
    plt.grid()
    
    # Алгебраическое уравнение - отрицательный корень
    plt.subplot(2, 2, 2)
    plt.semilogy(bisect_neg[:,0], bisect_neg[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.semilogy(iter_neg[:,0], iter_neg[:,1], 'ro-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Номер итерации')
    plt.ylabel('Погрешность')
    plt.title('Алгебраическое уравнение (- корень)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 1
    plt.subplot(2, 2, 3)
    plt.semilogy(bisect_trans1[:,0], bisect_trans1[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.semilogy(iter_trans1[:,0], iter_trans1[:,1], 'go-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Номер итерации')
    plt.ylabel('Погрешность')
    plt.title('Трансцендентное уравнение (корень 1)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 2
    plt.subplot(2, 2, 4)
    plt.semilogy(bisect_trans2[:,0], bisect_trans2[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.semilogy(iter_trans2[:,0], iter_trans2[:,1], 'go-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Номер итерации')
    plt.ylabel('Погрешность')
    plt.title('Трансцендентное уравнение (корень 2)')
    plt.legend()
    plt.grid()
    
    plt.tight_layout()
    plt.show()


# в) Графики зависимости фактической ошибки от заданной точности
def plot_actual_error_vs_epsilon():
    # Загрузка данных
    epsilons = np.loadtxt('testC_epsilon.txt')
    actual_pos = np.loadtxt('testC_actual_pos.txt')
    actual_neg = np.loadtxt('testC_actual_neg.txt')
    actual_trans1 = np.loadtxt('testC_actual_trans1.txt')
    actual_trans2 = np.loadtxt('testC_actual_trans2.txt')
    
    plt.figure(figsize=(12, 8))
    
    # Алгебраическое уравнение - положительный корень
    plt.subplot(2, 2, 1)
    plt.loglog(epsilons[:,0], epsilons[:,1], 'k--', label='y = x', linewidth=2)
    plt.loglog(epsilons[:,0], actual_pos[:,1], 'ro-', label='Фактическая ошибка', markersize=4)
    plt.xlabel('Заданная точность ε')
    plt.ylabel('Фактическая ошибка')
    plt.title('Алгебраическое уравнение (+ корень)')
    plt.legend()
    plt.grid()
    
    # Алгебраическое уравнение - отрицательный корень
    plt.subplot(2, 2, 2)
    plt.loglog(epsilons[:,0], epsilons[:,1], 'k--', label='y = x', linewidth=2)
    plt.loglog(epsilons[:,0], actual_neg[:,1], 'ro-', label='Фактическая ошибка', markersize=4)
    plt.xlabel('Заданная точность ε')
    plt.ylabel('Фактическая ошибка')
    plt.title('Алгебраическое уравнение (- корень)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 1
    plt.subplot(2, 2, 3)
    plt.loglog(epsilons[:,0], epsilons[:,1], 'k--', label='y = x', linewidth=2)
    plt.loglog(epsilons[:,0], actual_trans1[:,1], 'go-', label='Фактическая ошибка', markersize=4)
    plt.xlabel('Заданная точность ε')
    plt.ylabel('Фактическая ошибка')
    plt.title('Трансцендентное уравнение (корень 1)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 2
    plt.subplot(2, 2, 4)
    plt.loglog(epsilons[:,0], epsilons[:,1], 'k--', label='y = x', linewidth=2)
    plt.loglog(epsilons[:,0], actual_trans2[:,1], 'go-', label='Фактическая ошибка', markersize=4)
    plt.xlabel('Заданная точность ε')
    plt.ylabel('Фактическая ошибка')
    plt.title('Трансцендентное уравнение (корень 2)')
    plt.legend()
    plt.grid()
    
    plt.tight_layout()
    plt.show()





# в) Графики зависимости фактической ошибки от заданной точности
def plot_actual_error_vs_epsilon():
    # Загрузка данных
    epsilons = np.loadtxt('testC_epsilon.txt')
    actual_bisect_pos = np.loadtxt('testC_actual_bisect_pos.txt')
    actual_iter_pos = np.loadtxt('testC_actual_iter_pos.txt')
    actual_bisect_neg = np.loadtxt('testC_actual_bisect_neg.txt')
    actual_iter_neg = np.loadtxt('testC_actual_iter_neg.txt')
    actual_bisect_trans1 = np.loadtxt('testC_actual_bisect_trans1.txt')
    actual_iter_trans1 = np.loadtxt('testC_actual_iter_trans1.txt')
    actual_bisect_trans2 = np.loadtxt('testC_actual_bisect_trans2.txt')
    actual_iter_trans2 = np.loadtxt('testC_actual_iter_trans2.txt')
    
    plt.figure(figsize=(15, 10))
    
    # Алгебраическое уравнение - положительный корень
    plt.subplot(2, 2, 1)
    plt.loglog(epsilons[:,0], epsilons[:,1], 'k--', label='y = x', linewidth=2)
    plt.loglog(epsilons[:,0], actual_bisect_pos[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.loglog(epsilons[:,0], actual_iter_pos[:,1], 'ro-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Заданная точность ε')
    plt.ylabel('Фактическая ошибка')
    plt.title('Алгебраическое уравнение (+ корень)')
    plt.legend()
    plt.grid()
    
    # Алгебраическое уравнение - отрицательный корень
    plt.subplot(2, 2, 2)
    plt.loglog(epsilons[:,0], epsilons[:,1], 'k--', label='y = x', linewidth=2)
    plt.loglog(epsilons[:,0], actual_bisect_neg[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.loglog(epsilons[:,0], actual_iter_neg[:,1], 'ro-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Заданная точность ε')
    plt.ylabel('Фактическая ошибка')
    plt.title('Алгебраическое уравнение (- корень)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 1
    plt.subplot(2, 2, 3)
    plt.loglog(epsilons[:,0], epsilons[:,1], 'k--', label='y = x', linewidth=2)
    plt.loglog(epsilons[:,0], actual_bisect_trans1[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.loglog(epsilons[:,0], actual_iter_trans1[:,1], 'go-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Заданная точность ε')
    plt.ylabel('Фактическая ошибка')
    plt.title('Трансцендентное уравнение (корень 1)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 2
    plt.subplot(2, 2, 4)
    plt.loglog(epsilons[:,0], epsilons[:,1], 'k--', label='y = x', linewidth=2)
    plt.loglog(epsilons[:,0], actual_bisect_trans2[:,1], 'bo-', label='Метод половинного деления', markersize=4)
    plt.loglog(epsilons[:,0], actual_iter_trans2[:,1], 'go-', label='Метод простых итераций', markersize=4)
    plt.xlabel('Заданная точность ε')
    plt.ylabel('Фактическая ошибка')
    plt.title('Трансцендентное уравнение (корень 2)')
    plt.legend()
    plt.grid()
    
    plt.tight_layout()
    plt.show()

# г) Графики зависимости количества итераций от начального приближения
def plot_iterations_vs_initial_guess():
    # Загрузка данных
    x0_pos = np.loadtxt('testD_x0_pos.txt')
    bisect_pos = np.loadtxt('testD_bisect_pos.txt')
    iter_pos = np.loadtxt('testD_iter_pos.txt')
    
    x0_neg = np.loadtxt('testD_x0_neg.txt')
    bisect_neg = np.loadtxt('testD_bisect_neg.txt')
    iter_neg = np.loadtxt('testD_iter_neg.txt')
    
    x0_trans1 = np.loadtxt('testD_x0_trans1.txt')
    bisect_trans1 = np.loadtxt('testD_bisect_trans1.txt')
    iter_trans1 = np.loadtxt('testD_iter_trans1.txt')
    
    x0_trans2 = np.loadtxt('testD_x0_trans2.txt')
    bisect_trans2 = np.loadtxt('testD_bisect_trans2.txt')
    iter_trans2 = np.loadtxt('testD_iter_trans2.txt')
    
    plt.figure(figsize=(15, 10))
    
    # Алгебраическое уравнение - положительный корень
    plt.subplot(2, 2, 1)
    plt.plot(x0_pos[:,0], bisect_pos[:,1], 'bo-', label='Метод половинного деления', markersize=6)
    plt.plot(x0_pos[:,0], iter_pos[:,1], 'ro-', label='Метод простых итераций', markersize=6)
    plt.xlabel('Начальное приближение x₀')
    plt.ylabel('Количество итераций')
    plt.title('Алгебраическое уравнение (+ корень)')
    plt.legend()
    plt.grid()
    
    # Алгебраическое уравнение - отрицательный корень
    plt.subplot(2, 2, 2)
    plt.plot(x0_neg[:,0], bisect_neg[:,1], 'bo-', label='Метод половинного деления', markersize=6)
    plt.plot(x0_neg[:,0], iter_neg[:,1], 'ro-', label='Метод простых итераций', markersize=6)
    plt.xlabel('Начальное приближение x₀')
    plt.ylabel('Количество итераций')
    plt.title('Алгебраическое уравнение (- корень)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 1
    plt.subplot(2, 2, 3)
    plt.plot(x0_trans1[:,0], bisect_trans1[:,1], 'bo-', label='Метод половинного деления', markersize=6)
    plt.plot(x0_trans1[:,0], iter_trans1[:,1], 'go-', label='Метод простых итераций', markersize=6)
    plt.xlabel('Начальное приближение x₀')
    plt.ylabel('Количество итераций')
    plt.title('Трансцендентное уравнение (корень 1)')
    plt.legend()
    plt.grid()
    
    # Трансцендентное уравнение - корень 2
    plt.subplot(2, 2, 4)
    plt.plot(x0_trans2[:,0], bisect_trans2[:,1], 'bo-', label='Метод половинного деления', markersize=6)
    plt.plot(x0_trans2[:,0], iter_trans2[:,1], 'go-', label='Метод простых итераций', markersize=6)
    plt.xlabel('Начальное приближение x₀')
    plt.ylabel('Количество итераций')
    plt.title('Трансцендентное уравнение (корень 2)')
    plt.legend()
    plt.grid()
    
    plt.tight_layout()
    plt.show()

# Запуск всех графиков
plot_iterations_vs_epsilon()
plot_error_vs_iteration()
plot_actual_error_vs_epsilon()
plot_iterations_vs_initial_guess()
