#include <iostream>
#include "TTopTrianMatrix.h"
#include "..\src\TVector.cpp"

template<class T>
TDynamicTopTrianMatrix<T>::TDynamicTopTrianMatrix()
{
  this->size = NULL;
  this->pMem = nullptr;
}

template<class T>
TDynamicTopTrianMatrix<T>::TDynamicTopTrianMatrix(int _size)
{
  if (_size > 0) {
    this->size = _size;
    this->pMem = new TDynamicVector<T>[this->size];
    for (int i = 0; i < this->size; i++) { this->pMem[i] = TDynamicVector<T>(i + 1); }
  }
  else { throw "TDynamicTopTrianMatrix init error"; }
}

template<class T>
TDynamicTopTrianMatrix<T>::~TDynamicTopTrianMatrix()
{
  if (this->pMem != nullptr) { delete[] this->pMem; }
  this->size = NULL;
  this->pMem = nullptr;
}

template<class T>
const int TDynamicTopTrianMatrix<T>::GetSize()
{
  return this->size;
}

template<class T>
bool TDynamicTopTrianMatrix<T>::operator==(const TDynamicTopTrianMatrix& _mat)
{
  if (this->size != _mat.size) { return false; }
  if (this->pMem == nullptr || _mat.pMem == nullptr) { throw "TDynamicTopTrianMatrix operation== error"; }
  else {
    for (int i = 0; i < this->size; i++) { if (this->pMem[i] != _mat.pMem[i]) { return false; } }
    return true;
  }
}

template<class T>
bool TDynamicTopTrianMatrix<T>::operator!=(const TDynamicTopTrianMatrix& _mat)
{
  if (this->size != _mat.size) { return true; }
  if (this->pMem == nullptr || _mat.pMem == nullptr) { throw "TDynamicTopTrianMatrix operation== error"; }
  else {
    for (int i = 0; i < this->size; i++) { if (this->pMem[i] != _mat.pMem[i]) { return true; } }
    return false;
  }
}

template<class T>
TDynamicTopTrianMatrix<T> TDynamicTopTrianMatrix<T>::operator+(const TDynamicTopTrianMatrix& _mat)
{
  if (this->size != _mat.size || this->size == 0 || this->pMem == nullptr) { throw "TDynamicTopTrianMatrix operator+ error"; }
  TDynamicTopTrianMatrix<T> Result = TDynamicTopTrianMatrix<T>(this->size);
  for (int i = 0; i < this->size; i++) { Result.pMem[i] = this->pMem[i] + _mat.pMem[i]; }
  return Result;
}

template<class T>
TDynamicTopTrianMatrix<T> TDynamicTopTrianMatrix<T>::operator-(const TDynamicTopTrianMatrix& _mat)
{
  if (this->size != _mat.size || this->size == 0 || this->pMem == nullptr) { throw "TDynamicTopTrianMatrix operator+ error"; }
  TDynamicTopTrianMatrix<T> Result = TDynamicTopTrianMatrix<T>(this->size);
  for (int i = 0; i < this->size; i++) { Result.pMem[i] = this->pMem[i] - _mat.pMem[i]; }
  return Result;
}

template<class T>
TDynamicTopTrianMatrix<T> TDynamicTopTrianMatrix<T>::operator*(const TDynamicTopTrianMatrix& _mat)
{
  if (this->size != _mat.size || this->size == 0 || this->pMem == nullptr) { throw "TDynamicTopTrianMatrix operator+ error"; }
  TDynamicTopTrianMatrix<T> Result = TDynamicTopTrianMatrix<T>(this->size);
  for (int i = 0; i < this->size; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      Result[i][j] = 0;
      for (int k = j; k <= i; k++)
      {
        Result[i][j] += _mat.pMem[i][k] * this->pMem[k][j];
      }
    }
  }
  return Result;
}

template<class T>
TDynamicVector<T> TDynamicTopTrianMatrix<T>::operator*(TDynamicVector<T>& _vec)
{
  if (this->size != _vec.GetSize() || this->size == 0 || this->pMem == nullptr) { throw "TDynamicTopTrianMatrix operator+ error"; }
  TDynamicVector<T> Result = TDynamicVector<T>(this->size);
  for (int i = 0; i < this->size; i++)
  {
    Result[i] = 0;
    for (int j = 0; j <= i; j++)
    {
      Result[j] += this->pMem[i][j] * _vec[i];
    }
  }
  return Result;
}

template<class T>
TDynamicTopTrianMatrix<T> TDynamicTopTrianMatrix<T>::operator*(const T inp)
{
  if (this->size == 0 || this->pMem == nullptr) { throw "TDynamicTopTrianMatrix operator* error"; }
  TDynamicTopTrianMatrix<T> Result = TDynamicTopTrianMatrix<T>(this->size);
  for (int i = 0; i < this->size; i++) { Result.pMem[i] = this->pMem[i] * inp; }
  return Result;
}

template<class T>
std::istream& operator>>(std::istream& istr, TDynamicTopTrianMatrix<T>& _mat)
{
  for (int i = 0; i < _mat.size; i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      istr >> _mat.pMem[i][j];
    }
  }
  return istr;
}

template<class T>
std::ostream& operator<<(std::ostream& ostr, const TDynamicTopTrianMatrix<T>& _mat)
{
  for (int i = 0; i < _mat.size; i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      ostr << _mat.pMem[i][j] << ' ';
    }
    ostr << '\n';
  }
  return ostr;
}