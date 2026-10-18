#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cassert>
#include <utility>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size), pMem(nullptr)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Invalid vector size");
        pMem = new T[sz]();
    }
    TDynamicVector(T* arr, size_t s) : sz(s), pMem(nullptr)
    {
        if (sz == 0 || sz > MAX_VECTOR_SIZE || arr == nullptr)
            throw out_of_range("Invalid vector input");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v) : sz(v.sz), pMem(new T[v.sz])
    {
        std::copy(v.pMem, v.pMem + sz, pMem);
    }
    TDynamicVector(TDynamicVector&& v) noexcept : sz(v.sz), pMem(v.pMem)
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
        if (this != &v)
        {
            TDynamicVector temp(v);
            swap(*this, temp);
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if (this != &v)
        {
            delete[] pMem;
            sz = v.sz;
            pMem = v.pMem;
            v.sz = 0;
            v.pMem = nullptr;
        }
        return *this;
    }
    size_t size() const noexcept { return sz; }
    T& operator[](size_t ind)
    {
        return at(ind);
    }
    const T& operator[](size_t ind) const
    {
        return at(ind);
    }
    T& at(size_t ind)
    {
        if (ind >= sz) throw out_of_range("Vector index out of range");
        return pMem[ind];
    }
    const T& at(size_t ind) const
    {
        if (ind >= sz) throw out_of_range("Vector index out of range");
        return pMem[ind];
    }
    bool operator==(const TDynamicVector& v) const noexcept
    {
        if (sz != v.sz) return false;
        for (size_t i = 0; i < sz; ++i)
            if (!(pMem[i] == v.pMem[i])) return false;
        return true;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }
    TDynamicVector operator+(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] + val;
        return result;
    }
    TDynamicVector operator-(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] - val;
        return result;
    }
    TDynamicVector operator*(T val)
    {
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] * val;
        return result;
    }
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw length_error("Vector sizes differ");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] + v.pMem[i];
        return result;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw length_error("Vector sizes differ");
        TDynamicVector result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] - v.pMem[i];
        return result;
    }
    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz) throw length_error("Vector sizes differ");
        T result = T();
        for (size_t i = 0; i < sz; ++i) result = result + pMem[i] * v.pMem[i];
        return result;
    }
    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; ++i) istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sz; ++i) ostr << v.pMem[i] << ' ';
        return ostr;
    }
};

template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(checkSize(s))
    {
        for (size_t i = 0; i < sz; ++i) pMem[i] = TDynamicVector<T>(sz);
    }
private:
    static size_t checkSize(size_t s)
    {
        if (s == 0 || s > MAX_MATRIX_SIZE) throw out_of_range("Invalid matrix size");
        return s;
    }
public:
    using TDynamicVector<TDynamicVector<T>>::operator[];
    size_t size() const noexcept { return sz; }
    bool operator==(const TDynamicMatrix& m) const noexcept
    {
        if (sz != m.sz) return false;
        for (size_t i = 0; i < sz; ++i)
            if (pMem[i] != m.pMem[i]) return false;
        return true;
    }
    TDynamicMatrix operator*(const T& val)
    {
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] * val;
        return result;
    }
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (sz != v.size()) throw length_error("Matrix/vector sizes differ");
        TDynamicVector<T> result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] * v;
        return result;
    }
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw length_error("Matrix sizes differ");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] + m.pMem[i];
        return result;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw length_error("Matrix sizes differ");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i) result[i] = pMem[i] - m.pMem[i];
        return result;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        if (sz != m.sz) throw length_error("Matrix sizes differ");
        TDynamicMatrix result(sz);
        for (size_t i = 0; i < sz; ++i)
            for (size_t j = 0; j < sz; ++j)
            {
                T value = T();
                for (size_t k = 0; k < sz; ++k) value = value + pMem[i][k] * m.pMem[k][j];
                result[i][j] = value;
            }
        return result;
    }
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i) istr >> v.pMem[i];
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (size_t i = 0; i < v.sz; ++i) ostr << v.pMem[i] << '\n';
        return ostr;
    }
};

#endif
