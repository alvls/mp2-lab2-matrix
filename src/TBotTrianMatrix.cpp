#include <iostream>
#include "TBotTrianMatrix.h"
#include "..\src\TVector.cpp"

template<class T>
TDynamicBotTrianMatrix<T>::TDynamicBotTrianMatrix()
{
  this->size = NULL;
  this->pMem = nullptr;
}

template<class T>
TDynamicBotTrianMatrix<T>::TDynamicBotTrianMatrix(int _size)
{
  if (_size > 0) {
    this->size = _size;
    this->pMem = new TDynamicVector<T>[this->size];
    for (int i = 0; i < this->size; i++) { this->pMem[i] = TDynamicVector<T>(this->size - i); }
  }
  else { throw "TDynamicBotTrianMatrix init error"; }
}

template<class T>
TDynamicBotTrianMatrix<T>::~TDynamicBotTrianMatrix()
{
  if (this->pMem != nullptr) { delete[] this->pMem; }
  this->size = NULL;
  this->pMem = nullptr;
}

template<class T>
const int TDynamicBotTrianMatrix<T>::GetSize()
{
  return this->size;
}

template<class T>
bool TDynamicBotTrianMatrix<T>::operator==(const TDynamicBotTrianMatrix& _mat)
{
  if (this->size != _mat.size) { return false; }
  if (this->pMem == nullptr || _mat.pMem == nullptr) { throw "TDynamicBotTrianMatrix operation== error"; }
  else {
    for (int i = 0; i < this->size; i++) { if (this->pMem[i] != _mat.pMem[i]) { return false; } }
    return true;
  }
}

template<class T>
bool TDynamicBotTrianMatrix<T>::operator!=(const TDynamicBotTrianMatrix& _mat)
{
  if (this->size != _mat.size) { return true; }
  if (this->pMem == nullptr || _mat.pMem == nullptr) { throw "TDynamicBotTrianMatrix operation== error"; }
  else {
    for (int i = 0; i < this->size; i++) { if (this->pMem[i] != _mat.pMem[i]) { return true; } }
    return false;
  }
}

template<class T>
TDynamicBotTrianMatrix<T> TDynamicBotTrianMatrix<T>::operator+(const TDynamicBotTrianMatrix& _mat)
{
  if (this->size != _mat.size || this->size == 0 || this->pMem == nullptr) { throw "TDynamicBotTrianMatrix operator+ error"; }
  TDynamicBotTrianMatrix<T> Result = TDynamicBotTrianMatrix<T>(this->size);
  for (int i = 0; i < this->size; i++) { Result.pMem[i] = this->pMem[i] + _mat.pMem[i]; }
  return Result;
}

template<class T>
TDynamicBotTrianMatrix<T> TDynamicBotTrianMatrix<T>::operator-(const TDynamicBotTrianMatrix& _mat)
{
  if (this->size != _mat.size || this->size == 0 || this->pMem == nullptr) { throw "TDynamicBotTrianMatrix operator+ error"; }
  TDynamicBotTrianMatrix<T> Result = TDynamicBotTrianMatrix<T>(this->size);
  for (int i = 0; i < this->size; i++) { Result.pMem[i] = this->pMem[i] - _mat.pMem[i]; }
  return Result;
}

template<class T>
TDynamicBotTrianMatrix<T> TDynamicBotTrianMatrix<T>::operator*(const TDynamicBotTrianMatrix& _mat)
{
  if (this->size != _mat.size || this->size == 0 || this->pMem == nullptr) { throw "TDynamicBotTrianMatrix operator+ error"; }
  TDynamicBotTrianMatrix<T> Result = TDynamicBotTrianMatrix<T>(this->size);
  for (int i = 0; i < this->size; i++)
  {
    for (int j = 0; j <= i; j++)
    {
      Result[i - j][j] = 0;
      for (int k = 0; k <= j; k++)
      {
        Result[i - j][j] += this->pMem[i - k][k] * _mat.pMem[i - j][j - k];
      }
    }
  }
  return Result;
}

template<class T>
TDynamicVector<T> TDynamicBotTrianMatrix<T>::operator*(TDynamicVector<T>& _vec)
{
  if (this->size != _vec.GetSize() || this->size == 0 || this->pMem == nullptr) { throw "TDynamicBotTrianMatrix operator+ error"; }
  TDynamicVector<T> Result = TDynamicVector<T>(this->size);
  for (int i = 0; i < this->size; i++)
  {
    Result[i] = 0;
    for (int j = 0; j <= i; j++)
    {
      Result[i] += this->pMem[j][i - j] * _vec[j];
    }
  }
  return Result;
}

template<class T>
TDynamicBotTrianMatrix<T> TDynamicBotTrianMatrix<T>::operator*(const T inp)
{
  if (this->size == 0 || this->pMem == nullptr) { throw "TDynamicBotTrianMatrix operator* error"; }
  TDynamicBotTrianMatrix<T> Result = TDynamicBotTrianMatrix<T>(this->size);
  for (int i = 0; i < this->size; i++) { Result.pMem[i] = this->pMem[i] * inp; }
  return Result;
}

template<class T>
std::istream& operator>>(std::istream& istr, TDynamicBotTrianMatrix<T>& _mat)
{
  for (int i = 0; i < _mat.size; i++)
  {
    for (int j = 0; j < _mat.size - i; j++)
    {
      istr >> _mat.pMem[i][j];
    }
  }
  return istr;
}

template<class T>
std::ostream& operator<<(std::ostream& ostr, const TDynamicBotTrianMatrix<T>& _mat)
{
  for (int i = 0; i < _mat.size; i++)
  {
    for (int j = 0; j < _mat.size - i; j++)
    {
      ostr << _mat.pMem[i][j] << ' ';
    }
    ostr << '\n';
  }
  return ostr;
}