#include "TTopTrianMatrix.h"
#include <iostream>
#include "..\src\TTopTrianMatrix.cpp"

using namespace std;

void main() {
  TDynamicTopTrianMatrix<int> mat1(2);
  cin >> mat1;
  TDynamicTopTrianMatrix<int> mat2(2);
  cin >> mat2;
  TDynamicTopTrianMatrix<int> res = mat1 * mat2;
  cout << res;
}