#include "TTopTrianMatrix.h"
#include <iostream>
#include "..\src\TBotTrianMatrix.cpp"

using namespace std;

void main() {
  TDynamicBotTrianMatrix<int> mat1(2);
  cin >> mat1;
  TDynamicBotTrianMatrix<int> mat2(2);
  cin >> mat2;
  TDynamicBotTrianMatrix<int> res = mat1 * mat2;
  cout << res;
}