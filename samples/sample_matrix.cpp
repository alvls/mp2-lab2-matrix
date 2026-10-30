// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------
using namespace std;
void main()
{
  setlocale(LC_ALL, "Russian");

  int size;
  cout<< "Введите размерность матриц (N): ";
  cin >> size;
 
  if (size <= 0) {
      cout << "Ошибка: размер должен быть больше нуля." <<endl;
  }
  TDynamicMatrix<int> a(size), b(size);

  cout << "\nВведите элементы матрицы A (построчно, " << size * size << " чисел):" << endl;
  cin >> a;

  cout << "\nВведите элементы матрицы B (построчно, " << size * size << " чисел):" << endl;
  cin >> b;

  cout << "\nМатрица A:" << endl << a;
  cout << "Матрица B:" << endl << b;

  cout << "\nРезультат сложения (A + B):" << endl;
  cout << a + b;

  cout << "\nРезультат вычитания (A - B):" << endl;
  cout << a - b;
}
//---------------------------------------------------------------------------
