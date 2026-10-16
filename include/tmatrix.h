// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz > MAX_VECTOR_SIZE)
          throw out_of_range("TDynamicMatrix: size too large");
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];
      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept: sz(v.sz), pMem(v.pMem)
  {
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = new T[sz];
          std::copy(v.pMem, v.pMem + sz, pMem);
      }
      return *this;

  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {     
      if (this != &v) {
          delete[] pMem;
          sz = v.sz;
          pMem = v.pMem;
          v.sz = 0;
          v.pMem = nullptr;
      }
      return *this;
      

  }

  size_t size() const noexcept { return sz;}

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind >= sz) throw out_of_range("TDynamicVector::at: index out of range");
      return pMem[ind];
      
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw out_of_range("TDynamicVector::at: index out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (v.sz != sz) {
          return false;
      }
      for (int i = 0; i < sz; i++) {
          if (pMem[i] != v.pMem[i]) return false;
          
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
      
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("TDynamicVector::operator+: size mismatch");
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw invalid_argument("TDynamicVector::operator-: size mismatch");
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - v.pMem[i];
      }
      return res;
  }
  
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw invalid_argument("TDynamicVector::operator*: size mismatch");
      T res = T();
      for (int i = 0; i < sz; i++) {
          res += pMem[i] * v.pMem[i];
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw out_of_range("TDynamicMatrix: size too large");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
  }
  // индексация с контролем
  T& at(size_t ind1,size_t ind2)
  {
      if (ind1 >= sz || ind2 >= sz) throw out_of_range("TDynamicMatrix::at: index out of range");
      return pMem[ind1][ind2];

  }
  const T& at(size_t ind1, size_t ind2) const
  {
      if (ind1 >= sz || ind2 >= sz) throw out_of_range("TDynamicMatrix::at: index out of range");
      return pMem[ind1][ind2];
  }
  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size())
          throw invalid_argument("TDynamicMatrix::operator*: size mismatch");
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] * v;
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz !=m.size())
          throw invalid_argument("TDynamicMatrix::operator+: size mismatch");
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.size())
          throw invalid_argument("TDynamicMatrix::operator-: size mismatch");
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.size())
          throw invalid_argument("TDynamicMatrix::operator*: size mismatch");
      TDynamicMatrix res(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              T sum = T();
              for (int y = 0; y < sz; y++) {
                  sum += pMem[i][y] * m.pMem[y][j];
              }
              res.pMem[i][j] = sum;
          }
      }
      return res;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < v.sz; i++) {
          ostr << v.pMem[i] << "\n";
      }
      return ostr;
  }
};

#endif
