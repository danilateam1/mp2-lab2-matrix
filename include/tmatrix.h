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
class TDynamicVector {
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size) {
        if ((sz > MAX_VECTOR_SIZE) || (sz <= 0)) {
            throw out_of_range("the size does not match the parameters");
        }
        pMem = new T[sz]();// У типа Т должен быть коснтруктор по умолчанию
        for (int i = 0; i < sz; i++) {
            pMem[i] = T();
        }
    }

    TDynamicVector(T* arr, size_t s) : sz(s) {
        if ((sz > MAX_VECTOR_SIZE) || (sz <= 0)) {
            throw out_of_range("the size does not match the parameters");
        }
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz]();
        std::copy(arr, arr + sz, pMem);
    }

    TDynamicVector(const TDynamicVector& v) {
        pMem = new T[v.sz]();
        sz = v.sz;
        for (int i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }
    }

    TDynamicVector(TDynamicVector&& v) noexcept {
        pMem = v.pMem;
        v.pMem = nullptr;
        sz = v.sz;
        v.sz = 0;
    }

    ~TDynamicVector() {
        delete[]pMem;
        pMem = nullptr;
        sz = 0;
    }

    TDynamicVector& operator=(const TDynamicVector& v) {
        if (&v == this) {
            return *this;
        }

        if (sz != v.sz) {
            T* tmp = new T[v.sz]();
            delete[]pMem;
            sz = v.sz;
            pMem = tmp;
        }

        for (int i = 0; i < sz; i++) {
            pMem[i] = v.pMem[i];
        }

        return *this;
    }

    TDynamicVector& operator=(TDynamicVector&& v) noexcept {
        if (&v == this) {
            return *this;
        }
        delete[]pMem;
        pMem = v.pMem;
        v.pMem = nullptr;
        sz = v.sz;
        v.sz = 0;
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind) {
        if ((ind < 0) || (ind >= sz)) {
            throw out_of_range("incorrect index");
        }
        return pMem[ind];
    }

    const T& operator[](size_t ind) const {
        if ((ind < 0) || (ind >= sz)) {
            throw out_of_range("incorrect index");
        }
        return pMem[ind];
    }

    // индексация с контролем
    T& at(size_t ind) {
        if ((ind < 0) || (ind >= sz)) {
            throw out_of_range("incorrect index");
        }
        return pMem[ind];
    }
    const T& at(size_t ind) const {
        if ((ind < 0) || (ind >= sz)) {
            throw out_of_range("incorrect index");
        }
        return pMem[ind];
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept {
        if (sz != v.sz) {
            return false;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const TDynamicVector& v) const noexcept {
        if (sz != v.sz) {
            return true;
        }
        for (int i = 0; i < sz; i++) {
            if (pMem[i] != v.pMem[i]) {
                return true;
            }
        }
        return false;
    }

    // скалярные операции
    TDynamicVector operator+(T val) {
        TDynamicVector tmp(*this);
        for (int i = 0; i < sz; i++) {
            tmp[i] += val;
        }
        return tmp;
    }

    TDynamicVector operator-(double val) {
        TDynamicVector tmp(*this);
        for (int i = 0; i < tmp.sz; i++) {
            tmp.pMem[i] -= val;
        }
        return tmp;
    }

    TDynamicVector operator*(double val) {
        TDynamicVector tmp(*this);
        for (int i = 0; i < tmp.sz; i++) {
            tmp.pMem[i] *= val;
        }
        return tmp;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v) {
        if (sz != v.sz) {
            throw "sizes should be equal";
        }
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] + v.pMem[i];
        }
        return tmp;
    }

    TDynamicVector operator-(const TDynamicVector& v) {
        if (sz != v.sz) {
            throw "sizes should be equal";
        }
        TDynamicVector tmp(sz);
        for (int i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] - v.pMem[i];
        }
        return tmp;
    }

    T operator*(const TDynamicVector& v) {
        if (sz != v.sz) {
            throw "sizes should be equal";
        }
        T dot = 0;
        for (int i = 0; i < sz; i++) {
            dot += pMem[i] * v.pMem[i];
        }
        return dot;
    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v) {
        for (size_t i = 0; i < v.sz; i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>> {
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
        if ((s <= 0) || (sz > MAX_MATRIX_SIZE)) {
            throw out_of_range("the size does not match the parameters");
        }
        for (size_t i = 0; i < sz; i++) {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }

    using TDynamicVector<TDynamicVector<T>>::operator[];

    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept {
        if (sz != m.sz) {
            return false;
        }
        for (int i = 0; i < sz; ++i) {
            if (pMem[i] != m.pMem[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const TDynamicMatrix& m) const noexcept {
        if (sz != m.sz) {
            return true;
        }
        for (int i = 0; i < sz; ++i) {
            if (pMem[i] != m.pMem[i]) {
                return true;
            }
        }
        return false;
    }

    // матрично-скалярные операции
    TDynamicMatrix operator*(const T& val) {
        TDynamicMatrix tmp();
        tmp = *this;
        for (int i = 0; i < sz; i++) {
            tmp[i] = tmp[i] * val;
        }
        return tmp;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v) {
        if (sz != v.sz) {
            throw "sizes do not match";
        }
        TDynamicVector<T> tmp(v.sz);
        for (int i = 0; i < sz; i++) {
            tmp[i] = 0;
            for (int j = 0; j < sz; j++) {
                tmp[i] += pMem[i][j] * v[j];
            }
        }
        return tmp;
    }

    size_t size() const noexcept { return sz; }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m) {
        if (sz != m.sz) {
            throw "sizes should be equal";
        }
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] + m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m) {
        if (sz != m.sz) {
            throw "sizes should be equal";
        }
        TDynamicMatrix tmp(sz);
        for (int i = 0; i < sz; i++) {
            tmp.pMem[i] = pMem[i] - m.pMem[i];
        }
        return tmp;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m) {
        if (sz != m.sz) {
            throw "sizes should be match";
        }
        TDynamicMatrix<T> tmp(sz);
        for (int i = 0; i < sz; ++i) {
            for (int k = 0; k < sz; ++k) {
                for (int j = 0; j < sz; ++j) {
                    tmp.pMem[i][j] += pMem[i][k] * pMem[k][j];
                }
            }
        }
        return tmp;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& m) {
        for (size_t i = 0; i < m.sz; i++) {
            for (size_t j = 0; j < m.sz; j++)
                istr >> m.pMem[i][j];
        }
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& m) {
        for (size_t i = 0; i < m.sz; i++) {
            if (i != m.sz - 1) ostr << "   \n  ";
            ostr << m.pMem[i];
        }
        return ostr;
    }
};
#endif