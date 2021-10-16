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

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
    ValType* pVector;
    int Size;       // размер вектора
    int StartIndex; // индекс первого элемента вектора
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // конструктор копирования
    ~TVector();
    int GetSize() { return Size; } // размер вектора
    int GetStartIndex() { return StartIndex; } // индекс первого элемента
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
        for (int i = v.StartIndex; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }
    friend ostream& operator<<(ostream& out, const TVector& v)
    {
        for (int i = 0; i < v.StartIndex; i++)
            out << "0 ";
        for (int i = v.StartIndex; i < v.Size; i++)
            out << v.pVector[i] << ' ';
        return out;
    }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
    if (s < 0 || s > MAX_VECTOR_SIZE)
        throw - 1;
    if (si < 0)
        throw - 1;
    Size = s;
    StartIndex = si;
    /*cout << "StartIndex = " << StartIndex << endl;////////////////////////////////////////////////
    cout << "Size = " << Size << endl;*/
    pVector = new ValType[Size];
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v) :Size(v.Size), StartIndex(v.StartIndex)////////////////////////////////
{
    pVector = new ValType[Size];
    for (int i = StartIndex; i < Size; i++)
        pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
    delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
    int i = pos - StartIndex;
    if (i < 0 || i >= Size)
    {
        //cout << "Size_1 = " << Size << endl;///////////////////////////////////////////////////
        //cout << "pos_1 = " << pos << endl;
        //cout << "StartIndex_1 = " << StartIndex << endl;
        throw - 1;
    }
    return pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
    if (&v == this)
        return true;
    if (Size != v.Size)
        return false;
    if (StartIndex != v.StartIndex)
        return false;
    for (int i = 0; i < Size; i++)
        if (pVector[i] != v.pVector[i])
            return false;
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return (!((*this) == v));
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
    if (*this != v)
    {
        if (Size != v.Size)
        {
            Size = v.Size;
            delete[] pVector;
            pVector = new ValType[Size];
        }
        StartIndex = v.StartIndex;
        std::copy(v.pVector, v.pVector + Size, pVector);
    }
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
    TVector out(*this);
    for (int i = 0; i < Size; i++)
        out[i] += val;
    return out;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
    TVector out(*this);
    for (int i = 0; i < Size; i++)
        out[i] -= val;
    return out;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
    TVector out(*this);
    for (int i = 0; i < Size; i++)
        out[i] *= val;
    return out;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw string("not equal size");
    TVector<ValType> out(*this);
    for (int i = 0; i < Size; i++)
        out[i] = out[i] + v.pVector[i];
    return out;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw string("not equal size");
    TVector<ValType> out(*this);
    for (int i = 0; i < Size; i++)
        out[i] = out[i] - v.pVector[i];
    return out;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
    if (Size != v.Size)
        throw string("not equal size");
    ValType out = 0;
    for (int i = 0; i < Size; i++)
        out += pVector[i] * v.pVector[i];
    return out;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
      for (int i = 0; i < mt.Size; i++)
      {
          in >> mt.pVector[i];
      }
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
      for (int i = 0; i < mt.Size; i++)
      {
          out << mt.pVector[i] << endl;
      }
      return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
    if (s < 0 || s > MAX_MATRIX_SIZE)
        throw - 1;
    Size = s;
    StartIndex = 0;
    for (int i = 0; i < Size; i++)
    {
        pVector[i] = TVector<ValType>(Size - i, i);
    }
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt):
    TVector<TVector<ValType> >(mt)
{

}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) 
{

}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
    if (&mt == this)
        return true;
    if (Size != mt.Size)
        return false;
    for (int i = 0; i < Size; i++)
        if (pVector[i] != mt.pVector[i])
            return false;
    return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
    return !(*this == mt)
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
    if (this == &mt)
        return *this;
    if (Size != mt.Size)
    {
        Size = mt.Size;
        delete[] pVector;
        pVector = new TVector<ValType>[Size];
    }
    StartIndex = mt.StartIndex;
    std::copy(mt.pVector, mt.pVector + Size, pVector);
    return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    TMatrix<ValType> tmp(Size);
    if (tmp.Size != mt.Size)
        throw string("not equal size");
    for (int i = 0; i < Size; i++)
        for(int j=i;j<Size;j++)
        tmp.pVector[i][j] = tmp.pVector[i][j] + mt.pVector[i][j];
    return tmp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
    TMatrix<ValType> tmp(*this);
    if (tmp.Size != mt.Size)
        throw string("not equal size");
    for (int i = 0; i < Size; i++)
        tmp.pVector[i] = tmp.pVector[i] - mt.pVector[i];
    return tmp;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
