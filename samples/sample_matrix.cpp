// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// sample_matrix.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (20.04.2015)
//
// Тестирование верхнетреугольной матрицы

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void main()
{
   TMatrix<int> a(7), b(7), c(7), d(7);
   int i, j;

   setlocale(LC_ALL, "Russian");
   cout << "Тестирование программ поддержки представления треугольных матриц"
      << endl;
   for (i = 0; i < 7; i++)
      for (j = i; j < 7; j++)
      {
         a[i][j] = i * 10 + j;
         b[i][j] = (i * 10 + j) * 100;
      }
   c = a + b;

   cout << "Matrix a = " << endl << a << endl;
   cout << "Matrix b = " << endl << b << endl;
   cout << "Matrix c = a + b" << endl << c << endl;

   d = b - a;
   cout << "Matrix d = b - a" << endl << d << endl;

   if (a == a)
      cout << "Верно" << endl;
   else
      cout << "Неверно" << endl;

   if (a != b)
      cout << "Верно" << endl;
   else
      cout << "Неверно" << endl;
}
//---------------------------------------------------------------------------
