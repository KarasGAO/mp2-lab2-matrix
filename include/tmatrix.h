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
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      for (int i = 0; i < sz; ++i) {
          pMem[i] = v.~TDynamicVector[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      this->pMem = v.pMem;
      this->sz = v.sz;
      delete[]v.pMem;
      ////////////////////////
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this == &other) {
          return *this;
      }
      else {
          sz = v.sz;
          delete[]pMem;
          pMem = new T[sz];
          for (int i = 0; i < sz; ++i) {
              pMem[i] = v.pMem[i];
          }
          return *this;
      }
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (*this != other) {
          this->pMem = v.pMem;
          this->sz = sz;
          delete[] v.pMem;
      }
      return *this;
      /////////////////////////////////////////////////////////
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
      return pMem[ind];
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }
  const T& at(size_t ind) const
  {
      return pMem[ind];
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this.sz != v.sz) {
          return false;
      }
      else {
          for (int i = 0; i < sz; ++i) {
              if (pMem[i] != v[i]) {
                  return false;
              }
          }
      }
      return true;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(pMem == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      Vector<T> tmp(*this);
      for (int i = 0; i < sz; ++i) {
          tmp[i] += val;
      }
      return tmp;
  }
  TDynamicVector operator-(T val)
  {
      Vector<T> tmp(*this);
      for (int i = 0; i < sz; ++i) {
          tmp[i] -= val;
      }
      return tmp;
  }
  TDynamicVector operator*(T val)
  {
      Vector<T> tmp(*this);
      for (int i = 0; i < sz; ++i) {
          tmp[i] *= val;
      }
      return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw << "ERROR: DIFFERENT SIZES";
      }
      else {
          Vector<T> tmp(*this);
          for (int i = 0; i < sz; ++i) {
              tmp[i] += v[i];
          }
          return tmp;
      }
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw << "ERROR: DIFFERENT SIZES";
      }
      else {
          Vector<T> tmp(*this);
          for (int i = 0; i < sz; ++i) {
              tmp[i] -= v[i];
          }
          return tmp;
      }
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw << "ERROR: DIFFERENT SIZES";
      }
      else {
          int tmp = 0;
          for (int i = 0; i < sz; ++i) {
              tmp += vec[i]*v[i];
          }
          return tmp;
      }
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
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (this == &m) { return true; }
      if (sz != m.sz) { return false; }
      for (int i = 0; i < sz; ++i) {
          if (pMem[i] != m[i]) {
              return false;
          }
      }
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T>tmp(*this);
      for (int i = 0; i < sz; ++i) {
          tmp[i] = tmp[i] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> tmp(this->sz);
      for (int i = 0; i < sz; ++i) {
          tmp[i] = pMem[i] * v;
      }
      return tmp;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; ++i) {
          tmp[i]=pMem[i]+m[i]
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp(sz);
      for (int i = 0; i < sz; ++i) {
          tmp[i] = pMem[i] - m[i]
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp(sz);
      T sum;
      for (int i = 0; i < sz; ++i) {
          for (int j = 0; j < sz; ++j) {
              sum = 0;
              for (int k = 0; k < sz; ++k) {
                  sum += pMem[i][k] * m[k][j];
              }
              tmp[i][j] = sum;
          }
      }
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (int i = 0; i < sz; ++i) {
          istr >> pMem[i];
      }
      return istr;
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (int i = 0; i < sz; ++i) {
          ostr << pMem[i]<<std::endl;
      }
      return ostr;
      //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  }
};

#endif
