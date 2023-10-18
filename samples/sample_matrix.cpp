// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

int main()
{
    int size, i, j, choice;
    setlocale(LC_ALL, "Russian");

    cout << "Введите размер матриц: ";
    cin >> size;

    TMatrix<int> a(size), b(size), c(size);

    cout << "Тестирование программ с матрицами" << endl;

    while (true) {
        cout << "Выберите операцию:" << endl;
        cout << "1. Задать матрицы" << endl;
        cout << "2. Сложить матрицы" << endl;
        cout << "3. Вычесть матрицы" << endl;
        cout << "4. Вывести матрицы" << endl;
        cout << "5. Выход" << endl;

        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Введите элементы матрицы a:" << endl;
            cin >> a;
            cout << "Введите элементы матрицы b:" << endl;
            cin >> b;
            break;
        case 2:
            c = a + b;
            cout << "Результат сложения:" << endl << c << endl;
            break;
        case 3:
            c = a - b;
            cout << "Результат вычитания:" << endl << c << endl;
            break;
        case 4:
            cout << "Matrix a = " << endl << a << endl;
            cout << "Matrix b = " << endl << b << endl;
            break;
        case 5:
            return 0;
        default:
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
        }
    }
    return 0;

}
//---------------------------------------------------------------------------
