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
    int Size;       // Размер вектора
    int StartIndex; // Индекс первого элемента вектора
public:
    TVector(int s = 10, int si = 0);
    TVector(const TVector& v);                // Конструктор копирования
    ~TVector();
    int GetSize() { return Size; } // Размер вектора
    int GetStartIndex() { return StartIndex; } // Индекс первого элемента
    ValType& operator[](int pos);             // Доступ
    bool operator==(const TVector& v) const;  // Сравнение
    bool operator!=(const TVector& v) const;  // Сравнение
    TVector& operator=(const TVector& v);     // Присваивание

    // Скалярные операции
    TVector  operator+(const ValType& val);   // Прибавить скаляр
    TVector  operator-(const ValType& val);   // Вычесть скаляр
    TVector  operator*(const ValType& val);   // Умножить на скаляр

    // Векторные операции
    TVector  operator+(const TVector& v);     // Сложение
    TVector  operator-(const TVector& v);     // Вычитание
    ValType  operator*(const TVector& v);     // Скалярное произведение

    // Ввод
    friend istream& operator>>(istream& in, TVector& v)
    {
        int dump;
        for (int i = 0; i < v.StartIndex; i++)
            in >> dump;
        for (int i = 0; i < v.Size; i++)
            in >> v.pVector[i];
        return in;
    }

    // Вывод
    friend ostream& operator<<(ostream& out, const TVector& v)
    {
        for (int i = 0; i < v.StartIndex; i++)
            out << 0 << ' ';
        for (int i = 0; i < v.Size; i++)
            out << v.pVector[i] << ' ';
        return out;
    }
};

template <class ValType> // Конструктор по умолчанию
TVector<ValType>::TVector(int s, int si) : Size(s), StartIndex(si)
{
    if (s < 1 || s > MAX_VECTOR_SIZE || si < 0 || si > MAX_VECTOR_SIZE - 1)
        throw exception("Неверные значения при создании объекта pVector");
    pVector = new ValType[Size];
    for (int i = 0; i < Size; i++)
        pVector[i] = {};
}

template <class ValType> // Конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v)
{
    Size = v.Size;
    StartIndex = v.StartIndex;
    pVector = new ValType[Size];
    for (int i = 0; i < v.Size; i++)
        pVector[i] = v.pVector[i];
}

template <class ValType> // Деструктор
TVector<ValType>::~TVector()
{
    delete[] pVector;
}

template <class ValType> // Доступ
ValType& TVector<ValType>::operator[](int pos)
{
    if ((pos - StartIndex < 0) || (pos - StartIndex >= Size))
        throw exception("Неправильный индекс в operator[]");
    return pVector[pos - StartIndex];
}

template <class ValType> // Сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
    if (this == &v)
        return true;
    if (Size != v.Size || StartIndex != v.StartIndex)
        return false;
    for (int i = 0; i < Size; i++)
        if (pVector[i] != v.pVector[i])
            return false;
    return true;
}

template <class ValType> // Сравнение
bool TVector<ValType>::operator!=(const TVector& v) const
{
    return !(*this == v);
}

template <class ValType> // Присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
    if (this == &v)
        return *this;
    if (Size != v.Size)
    {
        delete[] pVector;
        Size = v.Size;
        pVector = new ValType[v.Size];
    }
    StartIndex = v.StartIndex;
    for (int i = 0; i < v.Size; i++)
        pVector[i] = v.pVector[i];
    return *this;
}

template <class ValType> // Прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
    TVector tmp(Size, StartIndex);
    for (int i = 0; i < tmp.Size; i++)
        tmp.pVector[i] = pVector[i] + val;
    return tmp;
}

template <class ValType> // Вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
    TVector tmp(Size, StartIndex);
    for (int i = 0; i < tmp.Size; i++)
        tmp.pVector[i] = pVector[i] - val;
    return tmp;
}

template <class ValType> // Умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
    TVector tmp(Size, StartIndex);
    for (int i = 0; i < tmp.Size; i++)
        tmp.pVector[i] = pVector[i] * val;
    return tmp;
}

template <class ValType> // Сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
    if (Size != v.Size)
        throw exception("Сложение векторов разных размеров недопустимо");
    TVector tmp(Size, StartIndex);
    for (int i = 0; i < tmp.Size; i++)
        tmp.pVector[i] = pVector[i] + v.pVector[i];
    return tmp;
}

template <class ValType> // Вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
    if (Size != v.Size)
        throw exception("Вычитание векторов разных размеров недопустимо");
    TVector tmp(Size, StartIndex);
    for (int i = 0; i < tmp.Size; i++)
        tmp.pVector[i] = pVector[i] - v.pVector[i];
    return tmp;
}

template <class ValType> // Cкалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
    if (Size != v.Size)
        throw exception("Cкалярное произведение векторов разных размеров недопустимо");
    ValType tmp = {};
    for (int i = 0; i < Size; i++)
        tmp += pVector[i] * v.pVector[i];
    return tmp;
}



// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
    TMatrix(int s = 10);
    TMatrix(const TMatrix& mt);                    // Копирование
    TMatrix(const TVector<TVector<ValType> >& mt); // Преобразование типа
    bool operator==(const TMatrix& mt) const;      // Сравнение
    bool operator!=(const TMatrix& mt) const;      // Сравнение
    TMatrix& operator= (const TMatrix& mt);        // Присваивание
    TMatrix  operator+ (const TMatrix& mt);        // Сложение
    TMatrix  operator- (const TMatrix& mt);        // Вычитание

    // Ввод
    friend istream& operator>>(istream& in, TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            in >> mt.pVector[i];
        return in;
    }

    // Вывод
    friend ostream& operator<<(ostream& out, const TMatrix& mt)
    {
        for (int i = 0; i < mt.Size; i++)
            out << mt.pVector[i] << endl;
        return out;
    }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s) : TVector<TVector<ValType> >(s)
{
    if (s > MAX_MATRIX_SIZE)
        throw exception("Слишком большой размер матрицы");
    for (int i = 0; i < s; i++)
        pVector[i] = TVector<ValType>(s - i, i);
}

template <class ValType> // Конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> // Конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) : TVector<TVector<ValType> >(mt) {}

template <class ValType> // Сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
    if (this == &mt)
        return true;
    if (Size != mt.Size)
        return false;
    for (int i = 0; i < Size; i++)
        if (pVector[i] != mt.pVector[i])
            return false;
    return true;
}

template <class ValType> // Сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const
{
    return !(*this == mt);
}

template <class ValType> // Присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
    if (this == &mt)
        return *this;
    if (Size != mt.Size)
    {
        delete[] pVector;
        pVector = new TVector<ValType>[mt.Size];
    }
    Size = mt.Size;
    StartIndex = mt.StartIndex;
    for (int i = 0; i < Size; i++)
        pVector[i] = mt.pVector[i];
    return *this;
}

template <class ValType> // Сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
    if (Size != mt.Size)
        throw exception("Сложение матриц разных размеров недопустимо");
    TMatrix tmp(Size);
    for (int i = 0; i < tmp.Size; i++)
        tmp.pVector[i] = pVector[i] + mt.pVector[i];
    return tmp;
}

template <class ValType> // Вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
    if (Size != mt.Size)
        throw exception("Вычитание матриц разных размеров недопустимо");
    TMatrix tmp(Size);
    for (int i = 0; i < tmp.Size; i++)
        tmp.pVector[i] = pVector[i] - mt.pVector[i];
    return tmp;
}

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
