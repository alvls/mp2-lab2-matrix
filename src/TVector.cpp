#include <iostream>
#include "TVector.h"

template<class T>
T minim(T a, T b) { return (a < b ? a : b); }

template<class T>
TDynamicVector<T>::TDynamicVector()
{
  size = NULL;
  pMem = nullptr;
}

template<class T>
TDynamicVector<T>::TDynamicVector(int _size)
{
  if (_size > 0) {
    size = _size;
    pMem = new T[size];
    for (int i = 0; i < size; i++) { pMem[i] = 0; }
  }
  else { throw "TDynamicVector init error"; }
}

template<class T>
TDynamicVector<T>::TDynamicVector(const TDynamicVector& _vec)
{
  if (_vec.size == 0 || _vec.pMem == nullptr || *this == _vec) { throw "TDynamicVector init error"; }
  size = _vec.size;
  pMem = new T[size];
  for (int i = 0; i < size; i++) { pMem[i] = _vec.pMem[i]; }
}

template<class T>
TDynamicVector<T>::TDynamicVector(TDynamicVector&& _vec)
{
  if (_vec.size == 0 || _vec.pMem == nullptr || *this == _vec) { throw "TDynamicVector init error"; }
  size = _vec.size;
  pMem = _vec.pMem;
  _vec.size = NULL;
  _vec.pMem = nullptr;
}

template<class T>
TDynamicVector<T>::~TDynamicVector()
{
  if (pMem != nullptr) { delete[] pMem; }
  size = NULL;
  pMem = nullptr;
}

template<class T>
int TDynamicVector<T>::GetSize()
{
  return size;
}

template<class T>
void TDynamicVector<T>::Resize(int nsize)
{
  if (nsize <= 0) { throw "TDynamicVector Resize error"; }
  if (nsize != size)
  {
    T* _pMem = new T[nsize];
    for (int i = 0; i < minim<T>(size, nsize); i++) { _pMem[i] = pMem[i]; }
    delete[] this->pMem;
    pMem = new T[nsize];
    for (int i = 0; i < minim<T>(size, nsize); i++) { pMem[i] = _pMem[i]; }
    if (nsize > size) 
    {
      for (int i = size; i < nsize; i++) { pMem[i] = 0; }
    }
    size = nsize;
    delete[] _pMem;
  }
}

template<class T>
TDynamicVector<T>& TDynamicVector<T>::operator=(const TDynamicVector& _vec)
{
  if (*this == _vec) { throw "TDynamicVector operation= error"; }
  delete[] this->pMem;
  size = _vec.size;
  if (size != 0) {
    pMem = new T[size];
    for (int i = 0; i < size; i++) { pMem[i] = _vec.pMem[i]; }
  }
  else { pMem = nullptr; }
  return *this;
}

template<class T>
T& TDynamicVector<T>::operator[](int index)
{
  return pMem[index];
}

template<class T>
bool TDynamicVector<T>::operator==(const TDynamicVector& _vec)
{
  if (size != _vec.size) { return false; }
  if (pMem == nullptr || _vec.pMem == nullptr) { throw "TDynamicVector operation== error"; }
  else { 
    for (int i = 0; i < size; i++) { if (pMem[i] != _vec.pMem[i]) { return false; } }
    return true;
  }
}

template<class T>
bool TDynamicVector<T>::operator!=(const TDynamicVector& _vec)
{
  if (size != _vec.size) { return true; }
  if (pMem == nullptr || _vec.pMem == nullptr) { throw "TDynamicVector operation!= error"; }
  else {
    for (int i = 0; i < size; i++) { if (pMem[i] != _vec.pMem[i]) { return true; } }
    return false;
  }
}

template<class T>
TDynamicVector<T> TDynamicVector<T>::operator+(const T inp)
{
  if (size == 0 || pMem == nullptr) { throw "TDynamicVector operator+ error"; }
  TDynamicVector<T> Result = TDynamicVector<T>(size);
  for (int i = 0; i < size; i++) { Result.pMem[i] = pMem[i] + inp; }
  return Result;
}

template<class T>
TDynamicVector<T> TDynamicVector<T>::operator-(const T inp)
{
  if (size == 0 || pMem == nullptr) { throw "TDynamicVector operator+ error"; }
  TDynamicVector<T> Result = TDynamicVector<T>(size);
  for (int i = 0; i < size; i++) { Result.pMem[i] = pMem[i] - inp; }
  return Result;
}

template<class T>
TDynamicVector<T> TDynamicVector<T>::operator*(const T inp)
{
  if (size == 0 || pMem == nullptr) { throw "TDynamicVector operator+ error"; }
  TDynamicVector<T> Result = TDynamicVector<T>(size);
  for (int i = 0; i < size; i++) { Result.pMem[i] = pMem[i] * inp; }
  return Result;
}

template<class T>
TDynamicVector<T> TDynamicVector<T>::operator+(const TDynamicVector& _vec)
{
  if (size != _vec.size || size == 0 || pMem == nullptr) { throw "TDynamicVector operator+ error"; }
  TDynamicVector<T> Result = TDynamicVector<T>(size);
  for (int i = 0; i < size; i++) {
    Result.pMem[i] = pMem[i] + _vec.pMem[i];
  }
  return Result;
}

template<class T>
TDynamicVector<T> TDynamicVector<T>::operator-(const TDynamicVector& _vec)
{
  if (size != _vec.size || size == 0 || pMem == nullptr) { throw "TDynamicVector operator+ error"; }
  TDynamicVector<T> Result = TDynamicVector<T>(size);
  for (int i = 0; i < size; i++) { Result.pMem[i] = pMem[i] - _vec.pMem[i]; }
  return Result;
}

template<class T>
T TDynamicVector<T>::operator*(const TDynamicVector& _vec)
{
  if (size != _vec.size || size == 0 || pMem == nullptr) { throw "TDynamicVector operator+ error"; }
  T Result = 0;
  for (int i = 0; i < size; i++) { Result += pMem[i] * _vec.pMem[i]; }
  return Result;
}

template<class T>
std::istream& operator>>(std::istream& istr, TDynamicVector<T>& _vec)
{
  for (int i = 0; i < _vec.size; i++) { istr >> _vec.pMem[i]; }
  return istr;
}

template<class T>
std::ostream& operator<<(std::ostream& ostr, const TDynamicVector<T>& _vec)
{
  for (int i = 0; i < _vec.size; i++) { ostr << _vec.pMem[i] << ' '; }
  return ostr;
}