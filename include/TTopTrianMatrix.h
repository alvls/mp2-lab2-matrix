#pragma once

#ifndef __TDynamicTopTrianMatrix_H__
#define __TDynamicTopTrianMatrix_H__

#include <iostream>
#include "TVector.h"

template<class T>
class TDynamicTopTrianMatrix : protected TDynamicVector<TDynamicVector<T>>
{
public:
  TDynamicTopTrianMatrix();
  TDynamicTopTrianMatrix(int _size);
  ~TDynamicTopTrianMatrix();

  const int GetSize();

  using TDynamicVector<TDynamicVector<T>>::operator[];
  bool operator==(const TDynamicTopTrianMatrix& _mat);
  bool operator!=(const TDynamicTopTrianMatrix& _mat);
  TDynamicTopTrianMatrix operator+(const TDynamicTopTrianMatrix& _mat);
  TDynamicTopTrianMatrix operator-(const TDynamicTopTrianMatrix& _mat);
  TDynamicTopTrianMatrix operator*(const TDynamicTopTrianMatrix& _mat);
  TDynamicVector<T> operator*(TDynamicVector<T>& _vec);
  TDynamicTopTrianMatrix operator*(const T inp);

  template<class T>
  friend std::istream& operator>>(std::istream& istr, TDynamicTopTrianMatrix<T>& _mat);
  template<class T>
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicTopTrianMatrix<T>& _mat);
};

#endif