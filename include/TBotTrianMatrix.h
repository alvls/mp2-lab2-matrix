#pragma once

#ifndef __TDynamicBotTrianMatrix_H__
#define __TDynamicBotTrianMatrix_H__

#include <iostream>
#include "TVector.h"

template<class T>
class TDynamicBotTrianMatrix : protected TDynamicVector<TDynamicVector<T>>
{
public:
  TDynamicBotTrianMatrix();
  TDynamicBotTrianMatrix(int _size);
  ~TDynamicBotTrianMatrix();

  const int GetSize();

  using TDynamicVector<TDynamicVector<T>>::operator[];
  bool operator==(const TDynamicBotTrianMatrix& _mat);
  bool operator!=(const TDynamicBotTrianMatrix& _mat);
  TDynamicBotTrianMatrix operator+(const TDynamicBotTrianMatrix& _mat);
  TDynamicBotTrianMatrix operator-(const TDynamicBotTrianMatrix& _mat);
  TDynamicBotTrianMatrix operator*(const TDynamicBotTrianMatrix& _mat);
  TDynamicVector<T> operator*(TDynamicVector<T>& _vec);
  TDynamicBotTrianMatrix operator*(const T inp);

  template<class T>
  friend std::istream& operator>>(std::istream& istr, TDynamicBotTrianMatrix<T>& _mat);
  template<class T>
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicBotTrianMatrix<T>& _mat);
};

#endif