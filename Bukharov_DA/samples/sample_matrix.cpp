// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------
using namespace std;

int main() 
{
  setlocale(LC_ALL, "Russian");
  cout << "=== Тестовое приложение для работы с матрицами ===" << endl;

  int choice = -1;
  while (choice != 0)
  {
    cout << "\nВыберите операцию:" << endl;
    cout << "1. Запуск стандартного теста" << endl;
    cout << "2. Ввод собственных матриц и сложение (A + B)" << endl;
    cout << "3. Ввод собственных матриц и умножение (A * B)" << endl;
    cout << "0. Выход" << endl;
    cout << "> ";
    cin >> choice;

    if (choice == 0) break;

    try
    {
      if (choice == 1)
      {

        TDynamicMatrix<int> a(5), b(5), c(5);
        for (int i = 0; i < 5; i++) {
          for (int j = 0; j < 5; j++) { 
            a[i][j] = i * 10 + j;
            b[i][j] = (i * 10 + j) * 100;
          }
        }
        c = a + b;
        cout << "Matrix a = " << endl << a << endl;
        cout << "Matrix b = " << endl << b << endl;
        cout << "Matrix c = a + b" << endl << c << endl;
      }
      else if (choice == 2 || choice == 3)
      {
        size_t size;
        cout << "Введите размер квадратных матриц: ";
        cin >> size;

        TDynamicMatrix<double> A(size), B(size), C(size);
        cout << "Введите элементы матрицы A (построчно, всего " << size * size << " чисел):" << endl;
        cin >> A;
        cout << "Введите элементы матрицы B (построчно, всего " << size * size << " чисел):" << endl;
        cin >> B;

        if (choice == 2) {
          C = A + B;
          cout << "\nРезультат сложения A + B:\n" << C << endl;
        } else {
          C = A * B;
          cout << "\nРезультат умножения A * B:\n" << C << endl;
        }
      }
      else
      {
        cout << "Неверный пункт меню!" << endl;
      }
    }
    catch (const exception& e)
    {
      cout << "\nОшибка: " << e.what() << endl;
    }
  }

  cout << "Программа завершена." << endl;
  return 0;
}
//---------------------------------------------------------------------------
