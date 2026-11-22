// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

TDynamicMatrix<int> InputMatrix() {
    size_t size;
    cout << "Введите длину стороны матрицы\n";
    cin >> size;

    TDynamicMatrix<int> result(size);
    cout << "Введите n * n элементов (слева направо, сверху вниз):\n";
    cin >> result;

    return result;
}
TDynamicVector<int> InputVector() {
    size_t size;
    cout << "Введите длину вектора\n";
    cin >> size;

    TDynamicVector<int> result(size);
    cout << "Введите n элементов:\n";
    cin >> result;

    return result;
}

void Menu() {
    cout << "0 - выход\n"
        << "1 - задать основную матрицу (начните с этого)\n"
        << "2 - сравнить матрицы\n"
        << "3 - сложить со скаляром\n"
        << "4 - вычесть скаляр\n"
        << "5 - умножить на скаляр\n"
        << "6 - сложить матрицы\n"
        << "7 - вычесть матрицы\n"
        << "8 - перемножить матрицы\n"
        << "9 - умножить матрицу на вектор\n";
}

void main()
{
  setlocale(LC_ALL, "Russian");

  TDynamicMatrix<int> m;

  while (true) {
    Menu();
    int flag;
    cin >> flag;

    switch (flag) {
    case 0: {
        return;
    }
    case 1: {
        m = InputMatrix();
        cout << "Матрица изменена\n";
        break;
    }
    case 2: {
        TDynamicMatrix<int> m1 = InputMatrix();

        cout << "A == B = " << (m == m1) << endl;
        break;
    }
    case 3: {
        int val;
        cout << "Введите скаляр:\n";
        cin >> val;

        cout << "A + " << val << " =\n" << (m + val) << endl;
        break;
    }
    case 4: {
        int val;
        cout << "Введите скаляр:\n";
        cin >> val;

        cout << "A - " << val << " =\n" << (m - val) << endl;
        break;
    }
    case 5: {
        int val;
        cout << "Введите скаляр:\n";
        cin >> val;

        cout << "A * " << val << " =\n" << (m * val) << endl;
        break;
    }
    case 6: {
        TDynamicMatrix<int> m1 = InputMatrix();

        cout << "A + B =\n" << (m + m1) << endl;
        break;
    }
    case 7: {
        TDynamicMatrix<int> m1 = InputMatrix();

        cout << "A - B =\n" << (m - m1) << endl;
        break;
    }
    case 8: {
        TDynamicMatrix<int> m1 = InputMatrix();

        cout << "A * B =\n" << (m * m1) << endl;
        break;
    }
    case 9: {
        TDynamicVector<int> m1 = InputVector();

        cout << "A * b =\n" << (m * m1) << endl;
        break;
    }
    default: {
        break;
    }
    }
  }

}
//---------------------------------------------------------------------------
