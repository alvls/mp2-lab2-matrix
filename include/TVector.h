#pragma once

#ifndef __TDynamicVector_H__
#define __TDynamicVector_H__

#include <iostream>

template<class T>
class TDynamicVector
{
protected:
  int size;
  T* pMem;
public:
  TDynamicVector();
  TDynamicVector(int _size);
  TDynamicVector(const TDynamicVector& _vec);
  TDynamicVector(TDynamicVector&& _vec);
  ~TDynamicVector();
  int GetSize();
  void Resize(int nsize);

  T& operator[](int index);
  bool operator==(const TDynamicVector& _vec);
  bool operator!=(const TDynamicVector& _vec);
  TDynamicVector operator+(const T inp);
  TDynamicVector operator-(const T inp);
  TDynamicVector operator*(const T inp);
  TDynamicVector operator+(const TDynamicVector& _vec);
  TDynamicVector operator-(const TDynamicVector& _vec);
  T operator*(const TDynamicVector& _vec);
  TDynamicVector& operator=(const TDynamicVector& _vec);

  template<class T>
  friend std::istream& operator>>(std::istream& istr, TDynamicVector<T>& _vec);
  template<class T>
  friend std::ostream& operator<<(std::ostream& ostr, const TDynamicVector<T>& _vec);
};

#endif