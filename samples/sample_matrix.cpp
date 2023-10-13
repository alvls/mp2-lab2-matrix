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
  TMatrix<int> a(5), b(5), c(5),d, e, f(5, 2);
  int i, j;
  setlocale(LC_ALL, "Russian");
  cout << "Тестирование программ поддержки представления матриц"
    << endl;
  for (i = 0; i < 5; i++)
    for (j = i; j < 5; j++ )
    {
      a[i][j] =  i * 10 + j;
      b[i][j] = (i * 10 + j) * 100;
    }
  c = a + b;
  d = c - a - a;
  cout << "Clean matrix =" << endl << TMatrix<int>(5) << endl;
  cout << "Matrix a = " << endl << a << endl;
  cout << "Matrix b = " << endl << b << endl;
  cout << "Matrix c = a + b" << endl << c << endl;

  
  cout << "Matrix d = c - a - a" << endl << d << endl;
  e = d++;
  cout << "Matrix e = d + 1" << endl << e << endl;
  f += e;
  cout << "Matrix f = f + e" << endl << f << endl;
  f += a;
  cout << "Matrix f += a" << endl << f << endl;
}
//---------------------------------------------------------------------------
