// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <exception>
#include<cstring>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType* pVector;
	size_t Size;       // размер вектора
public:
	TVector(size_t s = 10);
	TVector(const TVector& v);                // конструктор копирования
	~TVector();
	size_t GetSize() const; // размер вектора
	ValType* GetVector() const; // получить вектор
	ValType& operator[](int pos);             // доступ
	bool operator==(const TVector& v) const;  // сравнение
	bool operator!=(const TVector& v) const;  // сравнение
	TVector& operator=(const TVector& v);     // присваивание

	// скалярные операции
	TVector  operator+(const ValType& val);   // прибавить скаляр
	TVector& operator+=(const ValType& val);
	TVector  operator-(const ValType& val);   // вычесть скаляр
	TVector& operator-=(const ValType& val);
	TVector  operator*(const ValType& val);   // умножить на скаляр
	TVector& operator*=(const ValType& val);

	// векторные операции
	TVector  operator+(const TVector& v);     // сложение
	TVector& operator+=(const TVector& v);
	TVector  operator-(const TVector& v);     // вычитание
	TVector& operator-=(const TVector& v);
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
		out << '|';
		for (int i = 0; i < v.Size; i++)
			out << v.pVector[i] << ' ';
		out << '|';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(size_t s) : Size(s)
{
	if (s <= 0 || s > MAX_VECTOR_SIZE)
		throw invalid_argument("invalid length");
	pVector = new ValType[Size]();
}

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v) : Size(v.Size)
{
	pVector = new ValType[Size];
	memcpy(pVector, v.pVector, Size * sizeof(ValType));
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
}

template<class ValType>
size_t TVector<ValType>::GetSize() const { return Size; }

template<class ValType>
ValType* TVector<ValType>::GetVector() const { return pVector; }


template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos < 0 || pos >= Size)
		throw invalid_argument("invalid index");
	return pVector[pos];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (Size != v.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return false;
	return true;
}

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector& v) const { return !(*this == v); }

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (Size != v.Size)
	{
		Size = v.Size;
		ValType* tmp = new ValType[Size];
		delete[] pVector;
		pVector = tmp;
	}
	memcpy(pVector, v.pVector, Size * sizeof(ValType));
	return *this;
}

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i] + val;
	return res;
}

template <class ValType> // прибавить скаляр
TVector<ValType>& TVector<ValType>::operator+=(const ValType& val)
{
	for (int i = 0; i < Size; i++)
		pVector[i] += val;
	return *this;
}

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i] - val;
	return res;
}

template <class ValType> // прибавить скаляр
TVector<ValType>& TVector<ValType>::operator-=(const ValType& val)
{
	for (int i = 0; i < Size; i++)
		pVector[i] -= val;
	return *this;
}

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i] * val;
	return res;
}

template <class ValType> // прибавить скаляр
TVector<ValType>& TVector<ValType>::operator*=(const ValType& val)
{
	for (int i = 0; i < Size; i++)
		pVector[i] *= val;
	return *this;
}

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw invalid_argument("different length");
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res.pVector[i] += v.pVector[i];
	return res;

}
template <class ValType> // сложение
TVector<ValType>& TVector<ValType>::operator+=(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw invalid_argument("different length");
	for (int i = 0; i < Size; i++)
		pVector[i] += v.pVector[i];
	return *this;
}

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw invalid_argument("different length");
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res.pVector[i] -= v.pVector[i];
	return res;
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator-=(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw invalid_argument("different length");
	for (int i = 0; i < Size; i++)
		pVector[i] -= v.pVector[i];
	return *this;
}

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw invalid_argument("different length");
	ValType res{};
	for (int i = 0; i < Size; i++)
		res += pVector[i] * v.pVector[i];
	return res;
}


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(int s = 10);
	TMatrix(const TMatrix& mt);                    // копирование
	TMatrix(const TVector<TVector<ValType> >& mt); // преобразование типа
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
	if (s <= 0 || s > MAX_MATRIX_SIZE)
		throw invalid_argument("invalid length");
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	if (Size != mt.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != mt.pVector[i])
			return false;
	return true;
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const { return !(*this == mt); }


template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{
	pVector = mt.pVector;
	return *this;
} 

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	TMatrix res(*this);
	res.pVector += mt.pVector;
	return res;

} 

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	TMatrix res(*this);
	res.pVector -= mt.pVector;
	return res;
} 

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif

