// ����, ���, ���� "������ ����������������-2", �++, ���
//
// sample_matrix.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (20.04.2015)
//
// ������������ ����������������� �������

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

void main()
{
   TMatrix<int> a(7), b(7), c(7), d(7);
   int i, j;

   setlocale(LC_ALL, "Russian");
   cout << "������������ �������� ��������� ������������� ����������� ������"
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
      cout << "�����" << endl;
   else
      cout << "�������" << endl;

   if (a != b)
      cout << "�����" << endl;
   else
      cout << "�������" << endl;
}
//---------------------------------------------------------------------------
