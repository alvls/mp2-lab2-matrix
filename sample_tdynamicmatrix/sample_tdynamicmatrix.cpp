#include "TMatrix.h"
#include <iostream>
#include "..\src\TMatrix.cpp"

using namespace std;

void main() {
  TDynamicMatrix<int> mat1(2);
  cin >> mat1;
  TDynamicMatrix<int> mat2(2);
  cin >> mat2;
  TDynamicMatrix<int> res = mat1 * mat2;
  cout << res;
}