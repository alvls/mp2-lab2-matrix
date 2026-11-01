// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

int main()
{
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование класса работы с матрицами" << endl;

  try
  {
    size_t n = 0;
    cout << "Введите размер матриц: ";
    cin >> n;
    TDynamicMatrix<double> a(n), b(n);
    cout << "Введите матрицу a (" << n << " x " << n << "):" << endl;
    cin >> a;
    cout << "Введите матрицу b (" << n << " x " << n << "):" << endl;
    cin >> b;

    int choice = -1;
    while (choice != 0)
    {
      cout << endl;
      cout << "1 - a + b" << endl;
      cout << "2 - a - b" << endl;
      cout << "3 - a * b" << endl;
      cout << "4 - a * число" << endl;
      cout << "5 - a * вектор" << endl;
      cout << "6 - сравнить a и b" << endl;
      cout << "7 - показать a и b" << endl;
      cout << "0 - выход" << endl;
      cout << "Выберите операцию: ";
      if (!(cin >> choice))
      {
        if (cin.eof())
          break;
        cin.clear();
        cin.ignore(10000, '\n');
        choice = -1;
        cout << "Нужно ввести число" << endl;
        continue;
      }
      cout << endl;

      switch (choice)
      {
      case 1:
        cout << "a + b =" << endl << a + b;
        break;
      case 2:
        cout << "a - b =" << endl << a - b;
        break;
      case 3:
        cout << "a * b =" << endl << a * b;
        break;
      case 4:
      {
        double k;
        cout << "Введите число: ";
        if (!(cin >> k))
        {
          cin.clear();
          cin.ignore(10000, '\n');
          cout << "Некорректный ввод" << endl;
          break;
        }
        cout << "a * " << k << " =" << endl << a * k;
        break;
      }
      case 5:
      {
        TDynamicVector<double> v(n);
        cout << "Введите вектор из " << n << " чисел: ";
        if (!(cin >> v))
        {
          cin.clear();
          cin.ignore(10000, '\n');
          cout << "Некорректный ввод" << endl;
          break;
        }
        cout << "a * v = " << a * v << endl;
        break;
      }
      case 6:
        if (a == b)
          cout << "Матрицы равны" << endl;
        else
          cout << "Матрицы не равны" << endl;
        break;
      case 7:
        cout << "Матрица a:" << endl << a << endl;
        cout << "Матрица b:" << endl << b;
        break;
      case 0:
        break;
      default:
        cout << "Нет такой операции" << endl;
      }
    }
  }
  catch (exception& e)
  {
    cout << "Ошибка: " << e.what() << endl;
  }
  return 0;
}
//---------------------------------------------------------------------------
