#include "TVector.h"
#include <iostream>
#include "..\src\TVector.cpp"

using namespace std;

void main() {
  TDynamicVector<int> vec1(2);
  cin >> vec1;
  TDynamicVector<int> vec2(2);
  cin >> vec2;
  int res = vec1 * vec2;
  cout << res;
}