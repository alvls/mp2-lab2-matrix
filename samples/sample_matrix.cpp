// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"

using namespace std;

static void printMenu()
{
    cout << "\n===== Меню =====\n"
        << "1. Ввести матрицу A\n"
        << "2. Ввести матрицу B\n"
        << "3. A + B\n"
        << "4. A - B\n"
        << "5. A * B\n"
        << "6. A * скаляр\n"
        << "7. A * вектор\n"
        << "8. Показать A и B\n"
        << "0. Выход\n"
        << "Выбор: ";
}

int main()
{
    setlocale(LC_ALL, "Russian");

    int n = 0;
    cout << "Введите размер матриц (n): ";
    cin >> n;

    TDynamicMatrix<int> A(n), B(n);
    bool hasA = false, hasB = false;

    int choice = -1;
    while (choice != 0)
    {
        printMenu();
        cin >> choice;

        try
        {
            switch (choice)
            {
            case 1:
                cout << "Введите A (" << n * n << " чисел):\n";
                cin >> A;
                hasA = true;
                break;

            case 2:
                cout << "Введите B (" << n * n << " чисел):\n";
                cin >> B;
                hasB = true;
                break;

            case 3:
                if (!hasA || !hasB) { cout << "Сначала введите обе матрицы.\n"; break; }
                cout << "A + B =\n" << (A + B);
                break;

            case 4:
                if (!hasA || !hasB) { cout << "Сначала введите обе матрицы.\n"; break; }
                cout << "A - B =\n" << (A - B);
                break;

            case 5:
                if (!hasA || !hasB) { cout << "Сначала введите обе матрицы.\n"; break; }
                cout << "A * B =\n" << (A * B);
                break;

            case 6:
            {
                if (!hasA) { cout << "Сначала введите A.\n"; break; }
                int k; cout << "Скаляр: "; cin >> k;
                cout << "A * " << k << " =\n" << (A * k);
                break;
            }

            case 7:
            {
                if (!hasA) { cout << "Сначала введите A.\n"; break; }
                TDynamicVector<int> v(n);
                cout << "Введите вектор (" << n << " чисел):\n";
                cin >> v;
                cout << "A * v =\n" << (A * v);
                break;
            }

            case 8:
                if (hasA) cout << "A =\n" << A;
                else      cout << "A не задана.\n";
                if (hasB) cout << "B =\n" << B;
                else      cout << "B не задана.\n";
                break;

            case 0:
                break;

            default:
                cout << "Неверный пункт меню.\n";
            }
        }
        catch (const exception& e)
        {
            cout << "Ошибка: " << e.what() << endl;
        }
    }

    cout << "Выход.\n";
    return 0;
}