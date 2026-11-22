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
  TDynamicVector(size_t size = 1)
  {
      if (size < 1 || size > MAX_VECTOR_SIZE) { throw std::exception("out of range"); }
      sz = size;

    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s)
  {
    if (sz < 1 || sz > MAX_VECTOR_SIZE) { throw std::exception("out of range"); }
    sz = size;

    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) : sz(v.sz)
  {
      pMem = new T[sz];

      std::copy(v.pMem, v.pMem + sz, pMem);
  }
  TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz)
  {
      pMem = v.pMem;

      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (&v == this) { return *this; }

      sz = v.sz;

      delete[] pMem;
      pMem = new T[sz];

      std::copy(v.pMem, v.pMem + sz, pMem);

      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (&v == this) { return *this; }

      sz = v.sz;

      delete[] pMem;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;

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
      if (ind >= sz || ind < 0) { throw std::exception("out of range"); }

      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind >= sz || ind < 0) { throw std::exception("out of range"); }

      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      return (sz == v.sz && std::equal(pMem, pMem + sz, v.pMem));
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !((*this)==v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector result(sz);

      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + val;
      }

      return result;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector result(sz);

      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - val;
      }

      return result;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector result(sz);

      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] * val;
      }

      return result;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) { throw std::exception("unequal sizes"); }

      TDynamicVector result(sz);

      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] + v.pMem[i];
      }

      return result;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) { throw std::exception("unequal sizes"); }

      TDynamicVector result(sz);

      for (size_t i = 0; i < sz; i++) {
          result.pMem[i] = pMem[i] - v.pMem[i];
      }

      return result;
  }
  T operator*(const TDynamicVector& v)
  {
      if (sz != v.sz) { throw std::exception("unequal sizes"); }
      
      T result{};

      for (size_t i = 0; i < sz; i++) {
          result += (pMem[i] * v.pMem[i]);
      }

      return result;
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
private:
    size_t MatrixSizeValidation(size_t s) {
        if (s < 1 || s > MAX_MATRIX_SIZE) { throw std::exception("out of range"); }

        return s;
    }
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(MatrixSizeValidation(s))
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }


  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz) { return false; }

      for (size_t i = 0; i < sz; i++) {
          if (pMem[i].size() != m.pMem[i].size()) { return false; }
          for (size_t k = 0; k < pMem[i].size(); k++) {
              if (pMem[i][k] != m.pMem[i][k]) { return false;  }
          }
      }

      return true;
  }

  bool operator!=(const TDynamicMatrix& m) const noexcept
  {
      return !((*this) == m);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator+(const T& val)
  {
      TDynamicMatrix result(*this);

      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < pMem[i].size(); k++) {
              result.pMem[i][k] = result.pMem[i][k] + val;
          }
      }

      return result;
  }

  TDynamicMatrix operator-(const T& val)
  {
      TDynamicMatrix result(*this);

      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < pMem[i].size(); k++) {
              result.pMem[i][k] = result.pMem[i][k] - val;
          }
      }

      return result;
  }

  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix result(*this);

      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < pMem[i].size(); k++) {
              result.pMem[i][k] = result.pMem[i][k] * val;
          }
      }

      return result;
  }

  TDynamicMatrix Transpos() const {
      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < sz; k++) {
              result[k][i] = pMem[i][k];
          }
      }

      return result;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (pMem[0].size() != v.size()) { throw std::exception("invalid vector size"); };

      TDynamicVector<T> result(sz);

      for (size_t i = 0; i < sz; i++) { // i задает строку
          T val{};

          for (size_t k = 0; k < pMem[i].size(); k++) { // k задает столбец
              val = val + pMem[i][k] * v[k];
          }

          result[i] = val;
      }

      return result;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.size()) { throw std::exception("unequal sizes"); };

      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < sz; k++) {
              result[i][k] = pMem[i][k] + m[i][k];
          }
      }

      return result;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.size()) { throw std::exception("unequal sizes"); };

      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < sz; k++) {
              result[i][k] = pMem[i][k] - m[i][k];
          }
      }

      return result;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.size()) { throw std::exception("unequal sizes"); };

      TDynamicMatrix m_tr = m.Transpos();

      TDynamicMatrix result(sz);

      for (size_t i = 0; i < sz; i++) {
          for (size_t k = 0; k < sz; k++) {
              T val{};

              for (size_t j = 0; j < sz; j++) {
                  val = val + pMem[i][j] * m_tr[k][j];
              }
              result[i][k] = val;
          }
      }

      return result;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; ++i) {
          for (size_t k = 0; k < m.sz; ++k)
              istr >> m[i][k];
      }

      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m)
  {
      for (size_t i = 0; i < m.sz; ++i) {
          for (size_t k = 0; k < m.sz; ++k)
              ostr << m[i][k] << ' ';
          ostr << '\n';
      }

      return ostr;
  }
};

#endif
