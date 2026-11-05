#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

// Рекурсивне створення матриці
void Create(int** Q, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0) {
    if (i >= rowCount) return;

    Q[i][j] = Low + rand() % (High - Low + 1);

    if (j + 1 < colCount) {
        Create(Q, rowCount, colCount, Low, High, i, j + 1);
    }
    else {
        Create(Q, rowCount, colCount, Low, High, i + 1, 0);
    }
}

// Рекурсивне виведення матриці
void Print(int** Q, const int rowCount, const int colCount, int i = 0, int j = 0) {
    if (i >= rowCount) {
        cout << endl;
        return;
    }
    if (j == 0 && i == 0) cout << endl;

    cout << setw(5) << Q[i][j];

    if (j + 1 < colCount) {
        Print(Q, rowCount, colCount, i, j + 1);
    }
    else {
        cout << endl;
        Print(Q, rowCount, colCount, i + 1, 0);
    }
}

// Рекурсивний обмін стовпчиків
void Change(int** Q, const int col1, const int col2, const int rowCount, int i = 0) {
    if (i >= rowCount) return;

    int tmp = Q[i][col1];
    Q[i][col1] = Q[i][col2];
    Q[i][col2] = tmp;

    Change(Q, col1, col2, rowCount, i + 1);
}

// Внутрішній цикл сортування (бульбашка)
void SortSort(int** Q, const int rowCount, const int colCount, int j1) {
    if (j1 >= colCount - 1) return;

    if ((Q[0][j1] > Q[0][j1 + 1]) ||
        (Q[0][j1] == Q[0][j1 + 1] && Q[1][j1] < Q[1][j1 + 1]) ||
        (Q[0][j1] == Q[0][j1 + 1] && Q[1][j1] == Q[1][j1 + 1] && Q[2][j1] > Q[2][j1 + 1])) {
        Change(Q, j1, j1 + 1, rowCount);
    }

    SortSort(Q, rowCount, colCount, j1 + 1);
}

// Зовнішній цикл сортування
void Sort(int** Q, const int rowCount, const int colCount, int j0 = 0) {
    if (j0 >= colCount - 1) return;

    SortSort(Q, rowCount, colCount - j0, 0);
    Sort(Q, rowCount, colCount, j0 + 1);
}

// Рекурсивне обчислення та заміна
void Calc(int** Q, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0) {
    if (i >= rowCount) return;

    if (i == 0 && j == 0) {
        S = 0;
        k = 0;
    }

    // Критерій: всі елементи, КРІМ додатних парних
    if (!(Q[i][j] > 0 && Q[i][j] % 2 == 0)) {
        S += Q[i][j];
        k++;
        Q[i][j] = 0;
    }

    if (j + 1 < colCount) {
        Calc(Q, rowCount, colCount, S, k, i, j + 1);
    }
    else {
        Calc(Q, rowCount, colCount, S, k, i + 1, 0);
    }
}

int main() {
    srand((unsigned)time(NULL));

    const int Low = -26;
    const int High = 23;
    const int rowCount = 8;
    const int colCount = 6;

    int** Q = new int* [rowCount];
    for (int i = 0; i < rowCount; i++) {
        Q[i] = new int[colCount];
    }

    // 1. Формування та виведення початкової матриці
    Create(Q, rowCount, colCount, Low, High);
    cout << "Initial matrix:";
    Print(Q, rowCount, colCount);

    // 2. Впорядкування стовпчиків та виведення
    Sort(Q, rowCount, colCount);
    cout << "Sorted matrix:";
    Print(Q, rowCount, colCount);

    // 3. Обчислення суми, кількості та заміна елементів
    int S = 0;
    int k = 0;
    Calc(Q, rowCount, colCount, S, k);

    cout << "S = " << S << endl;
    cout << "k = " << k << endl;
    cout << "Modified matrix:";
    Print(Q, rowCount, colCount);

    // Звільнення пам'яті
    for (int i = 0; i < rowCount; i++) {
        delete[] Q[i];
    }
    delete[] Q;

    return 0;
}
