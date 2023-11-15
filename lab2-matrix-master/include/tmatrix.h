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
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Can't create too large vector");
    pMem = new T[sz]();
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
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (&v == this) return *this;
      if (v.sz != sz) {
          T* tmpMem = new T[v.sz];
          delete[] pMem;
          sz = v.sz;
          pMem = tmpMem;
      }
      std::copy(v.pMem, v.pMem + sz, pMem);
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);
      return *this;
  }

  size_t size() const noexcept { return sz; }

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
      if (ind >= sz) throw out_of_range("elem pos is out of range");
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz) throw out_of_range("elem pos is out of range");
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz) return false;
      for (size_t i = 0; i < sz; i++)
          if (pMem[i] != v.pMem[i]) return false;
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !operator==(v);
  }

  // скалярные операции
  //TDynamicVector operator+(double val)
  //{
  //    TDynamicVector tmp(sz);
  //    for (size_t i = 0; i < sz; i++)
  //        tmp.pMem[i] = pMem[i] + val;
  //    return tmp;
  //}
  //TDynamicVector operator-(double val)
  //{
  //    return operator+(-val);
  //}
  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++)
          tmp.pMem[i] = pMem[i] * val;
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw length_error("cant add vectors with not equal size");
      TDynamicVector res(sz);
      for (size_t i = 0; i < sz; i++)
          res.pMem[i] = pMem[i] + v.pMem[i];
      return res;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
      return operator+(TDynamicVector(v) * (-1));
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) throw length_error("cant multiply vectors with not equal size");
      T res{};
      for (size_t i = 0; i < sz; i++)
        res = res + pMem[i] * v.pMem[i];
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
    ostr << "\n";
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
  //using TDynamicVector<TDynamicVector<T>>::pMem;
  //using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE)
          throw out_of_range("Can't create too large matrix");
      for (size_t i = 0; i < sz; i++)
          pMem[i] = TDynamicVector<T>(sz);
  }

  TDynamicMatrix(const TDynamicVector<TDynamicVector<T>>& v) : TDynamicVector<TDynamicVector<T>>(v) {}

  //using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  //bool operator==(const TDynamicMatrix& m) const noexcept
  //{
  //    return TDynamicVector<TDynamicVector<T> == m;
  //}

  // матрично-скалярные операции
  TDynamicMatrix<T> operator*(double val)
  {
      return TDynamicVector<TDynamicVector<T>>::operator*(val);
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (sz != v.size()) throw length_error("cant multiply matrix and vector with not equal size");
      TDynamicVector<T> res(sz);
      for (size_t i = 0; i < sz; i++)
          res[i] = pMem[i] * v;
      return res;
  }

  // матрично-матричные операции
  //TDynamicMatrix operator+(const TDynamicMatrix& m) //возможно стоит заменить конструктором
  //{
  //}
  //TDynamicMatrix operator-(const TDynamicMatrix& m) //возможно стоит заменить конструктором
  //{
  //}
  TDynamicMatrix operator*(const TDynamicMatrix& m) //возможно стоит заменить конструктором
  {
      if (sz != m.sz) throw length_error("cant multiply matrixs with not equal size");
      TDynamicMatrix<T> res(sz);
      T tmp{};
      for (size_t i = 0; i < sz; i++)
          for (size_t j = 0; j < sz; j++) {
              tmp = T{};
              for (size_t k = 0; k < sz; k++)
                  tmp = tmp + pMem[i][k] * m.pMem[k][j];
              res[i][j] = tmp;
          }
      return res;
  }

  //// ввод/вывод
  //friend istream& operator>>(istream& istr, TDynamicMatrix& v) //возможно стоит заменить конструктором.. вводим с клавиатуры, нажимаем вектор
  //{
  //}
  //friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v) //возможно стоит заменить конструктором (удалить)
  //{
  //}
};

#endif
