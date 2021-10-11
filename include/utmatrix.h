  // ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;
#define FAKE_INT = -1;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType* pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public: 
  TVector(int _Size = 10, int _StartIndex = 0);
  TVector(const TVector& v);                // конструктор копирования
  ~TVector();
  int GetSize();// размер вектора
  int GetStartIndex(); // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector& v) const;  // сравнение
  bool operator!=(const TVector& v) const;  // сравнение
  TVector& operator=(const TVector& v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType& val);   // прибавить скаляр
  TVector  operator-(const ValType& val);   // вычесть скаляр
  TVector  operator*(const ValType& val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector& v);     // сложение
  TVector  operator-(const TVector& v);     // вычитание
  ValType  operator*(const TVector& v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream& in, TVector& v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }

  friend ostream& operator<<(ostream& out, const TVector& v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType> // конструктор по умолчанию
TVector<ValType>::TVector(int _Size, int _StartIndex) : Size (_Size), StartIndex (_StartIndex)
{
  if(_Size < 1 || _Size > MAX_VECTOR_SIZE || _StartIndex < 0 || _StartIndex > MAX_VECTOR_SIZE - 1)
    throw "Wrong size or start index";
  pVector = new ValType[Size];
  for (int i = 0; i < Size; i++)
    pVector[i] = {};
}

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v)
{
  Size = v.Size;
  StartIndex = v.StartIndex;
  pVector = new ValType[Size];
  copy (v.pVector, v.pVector + v.Size, pVector);
}

template <class ValType>
TVector<ValType>::~TVector()
{
  delete[] pVector;
} 

template <class ValType>
int TVector<ValType>::GetSize()
{
  return Size;
}

template <class ValType>
int TVector<ValType>::GetStartIndex()
{
  return StartIndex;
}

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
  if (pos < StartIndex || pos > Size + StartIndex - 1)
    throw "Invalid pos.";
  return pVector[pos - StartIndex];
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
  if (this == &v)
    return true;
  if (Size != v.Size)
    return false;
  if (StartIndex != v.StartIndex)
    return false;
  for (int i = 0; i < Size; i++)
    if (pVector[i] != v.pVector[i])
      return false;
  return true;
} 

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
  return !(*this == v);
} 

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
  if (this == &v)
    return *this;
  delete[] pVector;
  Size = v.Size;
  StartIndex = v.StartIndex;
  pVector = new ValType[Size];
  copy (v.pVector, v.pVector + v.Size, pVector);
  return *this;
} 

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
  TVector<ValType> result(*this);
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] += val;
  return result;
}  

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
  TVector<ValType> result(*this);
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] -= val;
  return result;
} 

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
  TVector<ValType> result(*this);
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] *= val;
  return result;
} 

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
  TVector<ValType> result(*this);
  if (result.Size != v.Size)
     throw "Vectores have different sizes";
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] += v.pVector[i];
  return result;
} 

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
  TVector<ValType> result(*this);
  if(result.Size != v.Size)
    throw "Vectores have different sizes";
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] -= v.pVector[i];
  return result;
} 

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
  if (Size != v.Size)
    throw "Vectors have different sizes";
  ValType result = 0;
  for (int i = 0; i < Size; i++)
    result += pVector[i] * v.pVector[i];
  return result;
}

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType>>
{
public:
  TMatrix(int _Size);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType>>& mt); // преобразование типа
  bool operator==(const TMatrix& mt) const;      // сравнение
  bool operator!=(const TMatrix& mt) const;      // сравнение
  TMatrix& operator= (const TMatrix& mt);        // присваивание
  TMatrix  operator+ (const TMatrix& mt);        // сложение
  TMatrix  operator- (const TMatrix& mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream& in, TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream& out, const TMatrix& mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int _Size): TVector<TVector<ValType>>(_Size)
{
  if (_Size > MAX_MATRIX_SIZE)
    throw "exception";
  for (int i = 0; i < _Size; i++)  
  
  {
    TVector<ValType> v(_Size - i, i);
    pVector[i] = v;
  }
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt): TVector<TVector<ValType>>(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType>>& mt): TVector<TVector<ValType>>(mt) {} 

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
  if (Size != mt.Size)
    return false;
  for (int i = 0; i < mt.Size; i++)
    if (pVector[i] != mt.pVector[i])
      return false;
  return true;
} 

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
  return !(*this == mt);
}

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
  if (this == &mt)
    return *this;
  Size = mt.Size;
  delete[] pVector;
  pVector = new TVector<ValType>[Size];
  copy (mt.pVector, mt.pVector + Size, pVector);
} 

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
  if (Size != mt.Size)
    throw "Can't add matrices with different sizes.";
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] = result.pVector[i] + mt.pVector[i];
  return result;
} 

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
  if (Size != mt.Size)
    throw "Can't subtract matrices with different sizes.";
  TMatrix<ValType> result(*this);
  for (int i = 0; i < result.Size; i++)
    result.pVector[i] = result.pVector[i] - mt.pVector[i];
  return result;
} 

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
