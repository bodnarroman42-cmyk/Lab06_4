#include <iostream>
#include <iomanip>
#include <time.h>
#include <cmath>
#include <clocale>
using namespace std;

// Прототипи рекурсивних функцій
void CreateRec(double* a, const int size, const double Low, const double High, int i);
void PrintRec(double* a, const int size, int i);
double SumPositiveRec(double* a, const int size, int i);
void FindMaxMinModuleIndices(double* a, const int size, int i, int& maxIdx, int& minIdx, double& maxMod, double& minMod);
double ProductBetweenIndicesRec(double* a, int start, int end, int i);
double ProductBetweenMaxMinModuleRec(double* a, const int size);
void SortOddDescendingRec(double* a, const int size, int i, int j);

int main() {
    setlocale(LC_ALL, "ukr");
    // Ініціалізація генератора випадкових чисел
    srand((unsigned)time(NULL));

    int n; // Кількість елементів масиву
    cout << "Введiть кiлькiсть елементiв n = ";
    cin >> n;

    // Виділення динамічної пам'яті для масиву дійсних чисел
    double* a = new double[n];
    double Low = -20.0;        // Нижня межа діапазону
    double High = 20.0;        // Верхня межа діапазону

    // Рекурсивне формування та виведення початкового масиву
    CreateRec(a, n, Low, High, 0);
    cout << "Початковий масив:" << endl;
    PrintRec(a, n, 0);

    // 1.1. Рекурсивне обчислення суми додатних елементів
    double sumPos = SumPositiveRec(a, n, 0);
    cout << "Сума додатних елементiв (рекурсивно) = " << sumPos << endl;

    // 1.2. Обчислення добутку між макс. і мін. за модулем елементами
    double prod = ProductBetweenMaxMinModuleRec(a, n);
    cout << "Добуток елементiв мiж максимальним i мiнiмальним за модулем = " << prod << endl;

    // 2. Рекурсивне впорядкування непарних елементів за спаданням
    SortOddDescendingRec(a, n, 0, 1);
    cout << "Модифiкований масив (непарнi елементи за спаданням):" << endl;
    PrintRec(a, n, 0);

    // Звільнення динамічної пам'яті
    delete[] a;

    return 0;
}

// --- Рекурсивні функції ---

// 1. Рекурсивне формування масиву
void CreateRec(double* a, const int size, const double Low, const double High, int i) {
    a[i] = Low + (double)(rand() % 100) / 99.0 * (High - Low);
    if (i < size - 1) {
        CreateRec(a, size, Low, High, i + 1);
    }
}

// 2. Рекурсивне виведення масиву
void PrintRec(double* a, const int size, int i) {
    cout << setw(8) << fixed << setprecision(2) << a[i];
    if (i < size - 1) {
        PrintRec(a, size, i + 1);
    }
    else {
        cout << endl << endl;
    }
}

// 3. Рекурсивне обчислення суми додатних елементів
double SumPositiveRec(double* a, const int size, int i) {
    double current = (a[i] > 0) ? a[i] : 0.0;
    if (i < size - 1) {
        return current + SumPositiveRec(a, size, i + 1);
    }
    return current;
}

// Допоміжна функція пошуку індексів макс. і мін. за модулем елементів (ітераційно-рекурсивний обхід)
void FindMaxMinModuleIndices(double* a, const int size, int i, int& maxIdx, int& minIdx, double& maxMod, double& minMod) {
    if (i >= size) return;

    if (fabs(a[i]) > maxMod) {
        maxMod = fabs(a[i]);
        maxIdx = i;
    }
    if (fabs(a[i]) < minMod) {
        minMod = fabs(a[i]);
        minIdx = i;
    }
    FindMaxMinModuleIndices(a, size, i + 1, maxIdx, minIdx, maxMod, minMod);
}

// Рекурсивне обчислення добутку елементів між межами
double ProductBetweenIndicesRec(double* a, int start, int end, int i) {
    if (i >= end) return 1.0;
    return a[i] * ProductBetweenIndicesRec(a, start, end, i + 1);
}

// Обчислення добутку між макс і мін за модулем
double ProductBetweenMaxMinModuleRec(double* a, const int size) {
    int maxIdx = 0, minIdx = 0;
    double maxMod = fabs(a[0]);
    double minMod = fabs(a[0]);

    FindMaxMinModuleIndices(a, size, 1, maxIdx, minIdx, maxMod, minMod);

    int start = (maxIdx < minIdx) ? maxIdx : minIdx;
    int end = (maxIdx < minIdx) ? minIdx : maxIdx;

    if (end - start <= 1) return 0.0;

    return ProductBetweenIndicesRec(a, start, end, start + 1);
}

// 4. Рекурсивне впорядкування непарних елементів за спаданням
void SortOddDescendingRec(double* a, const int size, int i, int j) {
    if (i >= size - 1) return;

    if (j < size) {
        if (i % 2 != 0 && j % 2 != 0) {
            if (a[i] < a[j]) {
                double tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }
        SortOddDescendingRec(a, size, i, j + 1);
    }
    else {
        SortOddDescendingRec(a, size, i + 1, i + 2);
    }
}