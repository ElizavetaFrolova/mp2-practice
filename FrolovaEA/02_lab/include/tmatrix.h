#ifndef _TMATRIX_H
#define _TMATRIX_H

#include "tvector.h"
#include <math.h>
using namespace std;

template <class T>
class TMatrix : public TVector<TVector<T>>{
public:
	TMatrix<T>(int s = 10);
	TMatrix<T>(const TMatrix<T>& mt); // копирование
	TMatrix<T>(const TVector<TVector<T> >& mt); // преобразование типа
	int operator==(const TMatrix<T>& mt) const; // сравнение
	TMatrix<T>& operator= (const TMatrix<T>& mt); // присваивание
	TMatrix<T> operator+ (const TMatrix<T>& mt); // сложение
	TMatrix<T> operator- (const TMatrix<T>& mt); // вычитание
//	TMatrix<T> operator* (const TMatrix<T>& mt); // умножение
	// ввод / вывод
	friend istream& operator>>(istream& in, TMatrix<T>& mt)
	{
		for (int i = 0; i < mt.Size; i++)

			in >> mt.pVector[i];
		return in;
	}
	friend ostream& operator<<(ostream& out, const TMatrix<T>& mt)
	{
		for (int i = 0; i < mt.Size; i++)

			out << mt.pVector[i] << endl;
		return out;
	}
};

template <typename T>
TMatrix<T>::TMatrix(int s) : TVector<TVector<T>>(s) {
	if (s <= 0) throw "";
	for (int i = 0; i < s; i++) {
		this->pVector[i] = TVector<T>(s - i, i);
	}
}

template <class T>
TMatrix<T>::TMatrix(const TMatrix& mt) :TVector<TVector<T>>(mt){}

template <class T>
TMatrix<T>::TMatrix<T>(const TVector<TVector<T> >& mt) :TVector<TVector<T>>(mt){}

template <class T>
int TMatrix<T>:: operator==(const TMatrix<T>& mt) const
{
	return TVector<TVector<T>>::operator==(mt);
}

template <class T>
TMatrix<T>& TMatrix<T>::operator=(
	const TMatrix<T>& mt)
{
	if (this != &mt)
	{
		if (this->Size != mt.Size)
		{
			delete[] this->pVector;
			this->pVector = new TVector<T>[mt.Size];
		}
		this->Size = mt.Size;
		this->StartIndex = mt.StartIndex;
		for (int i = 0; i < this->Size; i++)
			this->pVector[i] = mt.pVector[i];
	}
	return *this;
}


template <class T>
TMatrix<T> TMatrix<T>::operator+ (const TMatrix<T>& mt)
{
	return TVector<TVector<T>>::operator+(mt);
}

template <class T>
TMatrix<T> TMatrix<T>::operator- (const TMatrix<T>& mt)
{
	return TVector<TVector<T>>::operator-(mt);
}
/*
template <class T>
TMatrix<T> TMatrix<T>::operator* (const TMatrix<T>& mt)
{
	if (Size != mt.Size)
		throw"Error";

	TMatrix<T> tmp(Size);

	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
		{
			if (i <= j)
			{
				T sum;
				for (int k = j; k < size; k++)
				{
					sum += (*this)[i][k] * mt[k][j];
				}

				tmp[i][j] = sum;

			}
		}
	return tmp;
}
*/
#endif