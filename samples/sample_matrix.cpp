// ����, ���, ���� "������ ����������������-2", �++, ���
//
// sample_matrix.cpp - Copyright (c) ������� �.�. 07.05.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (20.04.2015)
//
// ������������ ����������������� �������

#include <iostream>
#include "utmatrix.h"
//---------------------------------------------------------------------------

int main()
{
    int size, i, j, choice;
    setlocale(LC_ALL, "Russian");

    cout << "������� ������ ������: ";
    cin >> size;

    TMatrix<int> a(size), b(size), c(size);

    cout << "������������ �������� � ���������" << endl;

    while (true) {
        cout << "�������� ��������:" << endl;
        cout << "1. ������ �������" << endl;
        cout << "2. ������� �������" << endl;
        cout << "3. ������� �������" << endl;
        cout << "4. ������� �������" << endl;
        cout << "5. �����" << endl;

        cin >> choice;
        switch (choice) {
        case 1:
            cout << "������� �������� ������� a:" << endl;
            cin >> a;
            cout << "������� �������� ������� b:" << endl;
            cin >> b;
            break;
        case 2:
            c = a + b;
            cout << "��������� ��������:" << endl << c << endl;
            break;
        case 3:
            c = a - b;
            cout << "��������� ���������:" << endl << c << endl;
            break;
        case 4:
            cout << "Matrix a = " << endl << a << endl;
            cout << "Matrix b = " << endl << b << endl;
            break;
        case 5:
            return 0;
        default:
            cout << "�������� �����. ���������� ��� ���." << endl;
        }
    }
    return 0;

}
//---------------------------------------------------------------------------
