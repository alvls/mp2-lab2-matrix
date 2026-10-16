// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"

using namespace std;

TDynamicMatrix<int> InputMatrix()
{
    int n;
    cout << "Размер матрицы: ";
    cin >> n;
    TDynamicMatrix<int> m(n);
    cout << "Введите " << n * n << " элементов:\n";
    cin >> m;
    return m;
}

void PrintMatrix(const TDynamicMatrix<int>& m)
{
    cout << m << endl;
}

void ShowMenu()
{
    cout<< "1. A + B\n"
        << "2. A - B\n"
        << "3. A * B\n"
        << "4. A * k (скаляр)\n"
        << "5. A == B\n"
        << "6. A * v (вектор)\n"
        << "0. Выход\n"
        << "Выбор: ";
}

int main() {
    setlocale(LC_ALL, "Russian");
    int key = 1;
    while (key == 1) {
        ShowMenu();
        int choice;
        cin >> choice;
        if (choice == 0) {
            key = 0;
            continue;
        }
            TDynamicMatrix<int> a = InputMatrix();
            switch (choice) {
            case 1: {
                TDynamicMatrix<int> b = InputMatrix();
                cout << "A + B =\n";
                PrintMatrix(a + b);
                break;
            }
            case 2: {
                TDynamicMatrix<int> b = InputMatrix();
                cout << "A - B =\n";
                PrintMatrix(a - b);
                break;
            }
            case 3: {
                TDynamicMatrix<int> b = InputMatrix();
                cout << "A * B =\n";
                PrintMatrix(a * b);
                break;
            }
            case 4: {
                int k;
                cout << "Скаляр k: ";
                cin >> k;
                cout << "A*k =\n";
                PrintMatrix(a * k);
                break;
            }
            case 5: {
                TDynamicMatrix<int> b = InputMatrix();
                cout << "A == B: " << (a == b ? "true" : "false") << endl;
                break;
            }
            case 6: {
                TDynamicVector<int> v(a.size());
                cout << "Введите " << a.size() << " элементов вектора:\n";
                cin >> v;
                cout << "A * v = " << (a * v) << endl;
                break;
            }
            }
    }
    cout << "Выход.\n";
    return 0;
}