// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include <limits>
#include "tmatrix.h"
//---------------------------------------------------------------------------

using namespace std;

// Сброс потока после неудачного ввода
void clearInput()
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

size_t readSize()
{
    size_t n;
    while (true)
    {
        cout << "Введите размер матриц (n): ";
        if (cin >> n && n > 0)
            return n;
        cout << "Ошибка: нужно положительное целое число." << endl;
        clearInput();
    }
}

TDynamicMatrix<int> readMatrix(size_t n, const char* name)
{
    TDynamicMatrix<int> m(n);
    cout << "Введите элементы матрицы " << name
        << " (" << n << " x " << n << "):" << endl;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            while (!(cin >> m[i][j]))
            {
                cout << "Ошибка. Повторите элемент [" << i << "][" << j << "]: ";
                clearInput();
            }
    return m;
}

void printMenu()
{
    cout << "\n=== Меню ===" << endl
        << "1. A + B" << endl
        << "2. A - B" << endl
        << "3. A * B" << endl
        << "4. Скопировать A в C" << endl
        << "5. Скопировать B в C" << endl
        << "6. Показать A, B, C" << endl
        << "0. Выход" << endl
        << "Выбор: ";
}

//---------------------------------------------------------------------------

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Тестирование класса работы с матрицами" << endl;

    size_t n = 0;
    TDynamicMatrix<int> A, B, C;

    while (true)
    {
        try
        {
            n = readSize();
            A = readMatrix(n, "A");
            B = readMatrix(n, "B");
            break;
        }
        catch (const exception& e)
        {
            cout << "Ошибка: " << e.what()
                << ". Попробуйте меньший размер." << endl;
            clearInput();
        }
    }

    int choice = -1;
    while (choice != 0)
    {
        printMenu();
        if (!(cin >> choice))
        {
            cout << "Ошибка ввода. Введите номер пункта." << endl;
            clearInput();
            continue;
        }

        try
        {
            switch (choice)
            {
            case 1:
                C = A + B;
                cout << "C = A + B =" << endl << C;
                break;
            case 2:
                C = A - B;
                cout << "C = A - B =" << endl << C;
                break;
            case 3:
                C = A * B;
                cout << "C = A * B =" << endl << C;
                break;
            case 4:
                C = A; //operator=
                cout << "C = A (копия A):" << endl << C;
                break;
            case 5:
                C = B;
                cout << "C = B (копия B):" << endl << C;
                break;
            case 6:
                cout << "Matrix A =" << endl << A;
                cout << "Matrix B =" << endl << B;
                cout << "Matrix C =" << endl << C;
                break;
            case 0:
                cout << "До свидания." << endl;
                break;
            default:
                cout << "Неизвестная команда. Введите 0..6." << endl;
            }
        }
        catch (const exception& e)
        {
            cout << "Ошибка выполнения: " << e.what() << endl;
        }
    }

    return 0;
}
//---------------------------------------------------------------------------
