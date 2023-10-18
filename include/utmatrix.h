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
#include <vector>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

//---------------------------------------------------------------------------------------------------------------------------------
// Шаблон вектора
template <class ValType>
class TVector
{
protected:
	ValType* pVector;                                 // вектор
	size_t Size;                                      // размер вектора
public:
	TVector(size_t s = 5);                            // конструктор-инициализатор
	TVector(size_t s, ValType el);                    // конструктор-инициализатор
	TVector(ValType arr[], size_t s);                 // конструктор-инициализатор
	TVector(const TVector& v);                        // конструктор копирования
	~TVector();                                       // деструктор
	size_t GetSize() const;                           // получить размер вектора
	ValType* GetVector() const;                       // получить вектор
	ValType& operator[](int pos);                     // доступ
	bool operator==(const TVector& v) const;          // сравнение
	bool operator!=(const TVector& v) const;          // сравнение
	TVector& operator=(const TVector& v);             // присваивание
	TVector<ValType>& operator=(const ValType arr[]); // присваивание

	// скалярные операции
	TVector  operator+(const ValType& val);           // прибавить скаляр
	TVector& operator+=(const ValType& val);          // сложение с присваиванием
	TVector  operator-(const ValType& val);           // вычесть скаляр
	TVector& operator-=(const ValType& val);          // вычитание с присваиванием
	TVector  operator*(const ValType& val);           // умножить на скаляр
	TVector& operator*=(const ValType& val);          // умножение с присваиванием
	TVector<ValType>& operator++();                   // префиксный инкремент
	TVector<ValType>& operator--();                   // префиксный декремент
	TVector<ValType> operator++(int);                 // постфиксный инкремент
	TVector<ValType> operator--(int);                 // постфиксный инкремент

	// векторные операции
	TVector  operator+(const TVector& v);             // сложение
	TVector& operator+=(const TVector& v);            // сложение с присваиванием
	TVector  operator-(const TVector& v);             // вычитание
	TVector& operator-=(const TVector& v);            // вычитание с присваиванием
	ValType  operator*(const TVector& v);             // скалярное произведение

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
			if (i != v.Size - 1)
				out << v.pVector[i] << ' ';
			else
				out << v.pVector[i];
		out << '|';
		return out;
	}
};
//---------------------------------------------------------------------------------------------------------------------------------

template <class ValType>
TVector<ValType>::TVector(size_t s) : Size(s)
{
	if (s <= 0 || s > MAX_VECTOR_SIZE)
		throw invalid_argument("invalid length");
	pVector = new ValType[Size]();
}

template <class ValType>
TVector<ValType>::TVector(size_t s, ValType el) : TVector(s)
{
	for (int i = 0; i < Size; i++)
		pVector[i] = el;
}

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType>& v) : Size(v.Size)
{
	pVector = new ValType[Size];
	copy(v.pVector,v.pVector + Size ,pVector);
}

template <class ValType>
TVector<ValType> ::TVector(ValType arr[], size_t s) : Size(s)
{
	if (s <= 0 || s > MAX_VECTOR_SIZE)
		throw invalid_argument("invalid length");
	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = arr[i];
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

template <class ValType> 
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos < 0 || pos >= Size)
		throw invalid_argument("invalid index");
	return pVector[pos];
}

template <class ValType> 
bool TVector<ValType>::operator==(const TVector& v) const
{
	if (Size != v.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return false;
	return true;
}

template <class ValType> 
bool TVector<ValType>::operator!=(const TVector& v) const { return !(*this == v); }

template <class ValType> 
TVector<ValType>& TVector<ValType>::operator=(const TVector& v)
{
	if (Size != v.Size)
	{
		Size = v.Size;
		ValType* tmp = new ValType[Size];
		delete[] pVector;
		pVector = tmp;
	}
	copy(v.pVector, v.pVector + Size, pVector);
	return *this;
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator=(const ValType arr[])
{
	for (int i = 0; i < Size; i++)
		pVector[i] = arr[i];
	return *this;
}

template <class ValType> 
TVector<ValType> TVector<ValType>::operator+(const ValType& val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res[i] += val;
	return res;
}

template <class ValType> 
TVector<ValType>& TVector<ValType>::operator+=(const ValType& val)
{
	for (int i = 0; i < Size; i++)
		pVector[i] += val;
	return *this;
}

template <class ValType> 
TVector<ValType> TVector<ValType>::operator-(const ValType& val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res[i] -= val;
	return res;
}

template <class ValType> 
TVector<ValType>& TVector<ValType>::operator-=(const ValType& val)
{
	for (int i = 0; i < Size; i++)
		pVector[i] -= val;
	return *this;
}

template <class ValType> 
TVector<ValType> TVector<ValType>::operator*(const ValType& val)
{
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res.pVector[i] = pVector[i] * val;
	return res;
}

template <class ValType> 
TVector<ValType>& TVector<ValType>::operator*=(const ValType& val)
{
	for (int i = 0; i < Size; i++)
		pVector[i] *= val;
	return *this;
}

template <class ValType> 
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw invalid_argument("different length");
	TVector<ValType> res(*this);
	for (int i = 0; i < Size; i++)
		res.pVector[i] += v.pVector[i];
	return res;

}

template <class ValType> 
TVector<ValType>& TVector<ValType>::operator+=(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw invalid_argument("different length");
	for (int i = 0; i < Size; i++)
		pVector[i] += v.pVector[i];
	return *this;
}

template <class ValType> 
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

template <class ValType> 
ValType TVector<ValType>::operator*(const TVector<ValType>& v)
{
	if (Size != v.Size)
		throw invalid_argument("different length");
	ValType res{};
	for (int i = 0; i < Size; i++)
		res += pVector[i] * v.pVector[i];
	return res;
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator++()
{
	for (int i = 0; i < Size; i++)
		pVector[i] += 1;
	return *this;
}

template <class ValType>
TVector<ValType>& TVector<ValType>::operator--()
{
	for (int i = 0; i < Size; i++)
		pVector[i] -= 1;
	return *this;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator++(int)
{
	TVector res(*this);
	for (int i = 0; i < Size; i++)
		res[i] += 1;
	return res;
}

template <class ValType>
TVector<ValType> TVector<ValType>::operator--(int)
{
	TVector res(*this);
	for (int i = 0; i < Size; i++)
		res[i] -= 1;
	return res;
}

//---------------------------------------------------------------------------------------------------------------------------------
// Матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
	TMatrix(size_t s = 5);                                   // инициализация
	TMatrix(size_t s, ValType el);                           // инициализация
	TMatrix(const TMatrix& mt);                              // копирование
	TMatrix(const TVector<TVector<ValType> >& mt);           // преобразование типа
	void Clr() { *this = TMatrix(Size, 0); }                 // очистка матрицы
	bool operator==(const TMatrix& mt) const;                // сравнение
	bool operator!=(const TMatrix& mt) const;                // сравнение
	TMatrix& operator= (const TMatrix& mt);                  // присваивание
	TMatrix  operator+ (const TMatrix& mt);                  // сложение
	TMatrix  operator- (const TMatrix& mt);                  // вычитание
	TMatrix<ValType> operator+=(const TMatrix<ValType>& mt); // сложение с присваиванием
	TMatrix<ValType> operator-=(const TMatrix<ValType>& mt); // вычитание с присваиванием
	TMatrix<ValType>& operator++();                          // префиксный инкремент
	TMatrix<ValType>& operator--();                          // префиксный декремент
	TMatrix<ValType> operator++(int);                        // постфиксный инкремент
	TMatrix<ValType> operator--(int);                        // постфиксный декремент

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
//---------------------------------------------------------------------------------------------------------------------------------

template<class ValType>
TMatrix<ValType>::TMatrix(size_t s) : TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE)
		throw invalid_argument("invalid size");
	for (int i = 0; i < s; i++)
		pVector[i] = TVector <ValType>(s);
}

template<class ValType>
TMatrix<ValType>::TMatrix(size_t s, ValType el)
{
	if (s > MAX_MATRIX_SIZE)
		throw invalid_argument("invalid size");
	Size = s;
	pVector = new TVector<ValType>[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = TVector<ValType>(Size, el);
}

template <class ValType> 
TMatrix<ValType>::TMatrix(const TMatrix<ValType>& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> 
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> >& mt) :
	TVector<TVector<ValType> >(mt) {}

template <class ValType> 
bool TMatrix<ValType>::operator==(const TMatrix<ValType>& mt) const
{
	if (this == &mt)
		return true;
	else if (Size != mt.Size)
		return false;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != mt.pVector[i])
			return false;
	return true;
}

template <class ValType> 
bool TMatrix<ValType>::operator!=(const TMatrix<ValType>& mt) const { return !(*this == mt); }

template <class ValType> 
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType>& mt)
{	
	if (Size != mt.Size)
	{
		Size = mt.Size;
		TVector<ValType>* tmp = new TVector<ValType>[Size];
		delete[] pVector;
		pVector = tmp;
	}
	for(int i = 0; i < Size; i++)
		pVector[i] = mt.pVector[i];
	return *this;
} 

template <class ValType> 
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType>& mt)
{
	TMatrix res(*this);
	for(int i = 0; i < Size; i++)
		res.pVector[i] += mt.pVector[i];
	return res;
} 

template <class ValType>  
TMatrix<ValType> TMatrix<ValType>::operator+=(const TMatrix<ValType>& mt)
{
	for (int i = 0; i < Size; i++)
		pVector[i] += mt.pVector[i];
	return *this;
}

template <class ValType> 
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType>& mt)
{
	TMatrix res(*this);
	for (int i = 0; i < Size; i++)
		res.pVector[i] -= mt.pVector[i];
	return res;
} 

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator-=(const TMatrix<ValType>& mt)
{
	for (int i = 0; i < Size; i++)
		pVector[i] -= mt.pVector[i];
	return *this;
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator++() 
{
	for (int i = 0; i < Size; i++)
		pVector[i]++;
	return *this;
}

template <class ValType>
TMatrix<ValType>& TMatrix<ValType>::operator--()
{
	for (int i = 0; i < Size; i++)
		pVector[i]--;
	return *this;
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator++(int) 
{
	TMatrix res(*this);
	for (int i = 0; i < Size; i++)
		++res.pVector[i];
	return res; 
}

template <class ValType>
TMatrix<ValType> TMatrix<ValType>::operator--(int) 
{
	TMatrix res(*this);
	for (int i = 0; i < Size; i++)
		--res.pVector[i];
	return res;
}

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif

