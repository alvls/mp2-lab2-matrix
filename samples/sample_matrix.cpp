#include <iostream>
#include "tmatrix.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    
    int n;
    cout << "Введите размерность матриц (N x N): ";
    if (!(cin >> n) || n <= 0) {
        cout << "Некорректная размерность." << endl;
        return 1;
    }

    TDynamicMatrix<int> a(n), b(n);
    
    cout << "Введите элементы первой матрицы (" << n * n << " чисел):" << endl;
    cin >> a;
    
    cout << "Введите элементы второй матрицы (" << n * n << " чисел):" << endl;
    cin >> b;

    cout << "\nМатрица A:" << endl << a;
    cout << "\nМатрица B:" << endl << b;

    try {
        cout << "\nA + B:" << endl << (a + b);
        cout << "\nA - B:" << endl << (a - b);
        cout << "\nA * B:" << endl << (a * b);
    } catch (const exception& e) {
        cout << "Ошибка при выполнении операций: " << e.what() << endl;
    }

    return 0;
}