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
  size_t n;
  cout << "Введите размер матриц: ";
  cin >> n;

  TDynamicMatrix<int> a(n), b(n), c(n);

  cout << "Введите матрицу a (" << n << "x" << n << "):" << endl;
  cin >> a;
  cout << "Введите матрицу b (" << n << "x" << n << "):" << endl;
  cin >> b;

  int choice;
  do
  {
    cout << "\nВыберите операцию:" << endl;
    cout << "1 - a + b" << endl;
    cout << "2 - a - b" << endl;
    cout << "3 - a * b (матричное)" << endl;
    cout << "4 - a * scalar" << endl;
    cout << "5 - a * vector" << endl;
    cout << "6 - вывести a и b" << endl;
    cout << "0 - выход" << endl;
    cout << "> ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      c = a + b;
      cout << "a + b =" << endl << c;
      break;
    case 2:
      c = a - b;
      cout << "a - b =" << endl << c;
      break;
    case 3:
      c = a * b;
      cout << "a * b =" << endl << c;
      break;
    case 4:
    {
      int s;
      cout << "Введите скаляр: ";
      cin >> s;
      c = a * s;
      cout << "a * " << s << " =" << endl << c;
      break;
    }
    case 5:
    {
      TDynamicVector<int> v(n);
      cout << "Введите вектор (" << n << " элементов): ";
      cin >> v;
      TDynamicVector<int> r = a * v;
      cout << "a * v = " << r << endl;
      break;
    }
    case 6:
      cout << "a =" << endl << a;
      cout << "b =" << endl << b;
      break;
    case 0:
      cout << "Выход." << endl;
      break;
    default:
      cout << "Неверный выбор." << endl;
    }
  } while (choice != 0);

  return 0;
}
//---------------------------------------------------------------------------