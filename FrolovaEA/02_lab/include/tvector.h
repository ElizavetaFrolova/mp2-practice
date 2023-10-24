#ifndef _TVECTOR_H
#define _TVECTOR_H
//#include <cmath>
#include <math.h>
using namespace std;

template <class T>
class TVector
{
protected:
	T* pVector;
	int Size; // размер вектора
	int StartIndex; // индекс первого элемента вектора
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector& v); // конструктор копирования
	virtual ~TVector<T>();
	int GetSize() { return Size; } // размер вектора
	int GetStartIndex() { return StartIndex; } // индекс первого элемента
//	T& GetValue(int pos); // доступ с контролем индекса
	T& operator[](int pos); // доступ
	int operator==(const TVector<T>& v) const; // сравнение
	TVector<T>& operator= (const TVector<T>& v); // присванивание
	// скалярные операции
	TVector<T> operator+ (const T& val); // прибавить скаляр
	TVector<T> operator- (const T& val); // вычесть скаляр
	TVector<T> operator* (const T& val); // умножить на скаляр
	// векторные операции
	TVector<T> operator+ (const TVector<T>& v); // сложение
	TVector<T> operator- (const TVector<T>& v); // вычитание
	T operator* (const TVector<T>& v); // скалярное произведение
	// ввод-вывод
	friend istream& operator>>(istream& in, TVector& v)
	{
		int strSize;
		cout << "Enter size: ";
		in >> strSize;
		int strStartIndex;
		cout << "Enter StartIndex: ";
		in >> strStartIndex;
		cout << endl;
		cout << "Enter " << strSize - strStartIndex << " elements :";
		if (v.Size != strSize || v.StartIndex != strStartIndex)
		{
			if (v.pVector != NULL)
				delete[] v.pVector;
			v.Size = strSize;
			v.StartIndex = strStartIndex;
			v.pVector = new T[strSize - strStartIndex];
		}
		for (int i = 0; i < v.Size - v.StartIndex; ++i)
			in >> v.pVector[i];
		return in;
	}

	friend ostream& operator<<(ostream& out, const TVector& v)
	{

		out << "Vector: (";
		for (int j = 0; j < v.StartIndex; j++)
		{
			out<< "0"<<",";
		}
		for (int i = 0; i < v.Size - v.StartIndex; i++)
		{
			out << v.pVector[i];
			if (i == v.Size - v.StartIndex - 1)
				out << ")\n";
			else
				out << ",";
		}
		return out;

	}
};

template <class T>
TVector <T> ::TVector(int Size, int StartIndex)
{
	this->StartIndex = StartIndex;
	this->Size = Size;
	pVector = new T[Size - StartIndex];
}

template <class T>
TVector <T>::TVector(const TVector<T>& v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new T[Size - StartIndex];
	for (int i = 0; i < Size - StartIndex; i++)
	{
		pVector[i] = v.pVector[i];
	}
}

template <class T>
TVector <T>::~TVector()
{
	if (pVector != NULL)
	{
		delete[] pVector;
		pVector = NULL;
		Size = 0;
	}
}

template <class T>
T& TVector <T>:: operator[](int pos)
{
	if (pos < 0 || pos >= Size - StartIndex)
		abort();
	return pVector[pos];
}

template<class T>
int TVector<T>::operator==(const TVector<T>& v) const
{
	if (StartIndex != v.StartIndex)
		return 0;
	if (Size != v.Size)
		return 0;
	for (int i = 0; i < Size - StartIndex; i++)
		if (pVector[i] != v.pVector[i])
			return 0;
	return 1;
}

template <class T>
TVector<T>& TVector<T>::operator=(const TVector<T>& v)
{
	if (this != &v)
	{
		if (Size != v.Size)
		{
			delete[] pVector;
			pVector = new T[v.Size];
		}
		Size = v.Size;
		StartIndex = v.StartIndex;
		for (int i = 0; i < Size; i++)
			pVector[i] = v.pVector[i];
	}
	return *this;
}

template <class T>
TVector<T> TVector<T>:: operator+ (const T& val)
{
	TVector<T> tmp(*this);
	for (int i = 0; i < Size - StartIndex; i++)
	{
		tmp.pVector[i] += val;
	}
	return tmp;
}

template <class T>
TVector<T> TVector<T>:: operator- (const T& val)
{
	TVector<T> tmp(*this);
	for (int i = 0; i < Size - StartIndex; i++)
	{
		tmp.pVector[i] -= val;
	}
	return tmp;
}

template <class T>
TVector<T> TVector<T>:: operator* (const T& val)
{
	TVector<T> tmp(*this);
	for (int i = 0; i < Size - StartIndex; i++)
	{
		tmp.pVector[i] *= val;
	}
	return tmp;
}

template <class T>
TVector<T> TVector<T>:: operator+ (const TVector<T>& v)
{
	if (Size != v.Size || StartIndex != v.StartIndex)
		throw"Error";
	TVector<T> tmp(*this);
	for (int i = 0; i < Size - StartIndex; i++)
	{
		tmp.pVector[i] = tmp.pVector[i] + v.pVector[i];
	}
	return tmp;
}

template <class T>
TVector<T> TVector<T>:: operator- (const TVector<T>& v)
{
	if (Size != v.Size || StartIndex != v.StartIndex)
		throw"Error";
	TVector<T> tmp(*this);
	for (int i = 0; i < Size - StartIndex; i++)
	{
		tmp.pVector[i] -= v.pVector[i];
	}
	return tmp;
}

template <class T>
T TVector <T>:: operator* (const TVector<T>& v)
{
	if (Size != v.Size || StartIndex!=v.StartIndex)
		throw "Error";
	T res = T();
	for (int i = 0; i < Size-StartIndex; i++)
	{
		res += pVector[i] * v.pVector[i];
	}
	return res;
}
/*
template <class T>
istream& operator>>(istream& stream, TVector<T>& vec) // ввод из потока
{
	int strSize;
	cout << "Enter size: ";
	stream >> strSize;
	cout << endl;
	int strStartIndex;
	cout << "Enter StartIndex: ";
	stream >> strStartIndex;
	cout << endl;
	cout << "Enter " << strSize - strStartIndex << " elements :";
	if (vec.Size != strSize || vec.StartIndex!=strStartIndex)
	{
		if (vec.pVector != NULL)
			delete[] vec.pVector;
		vec.Size = strSize;
		vec.StartIndex = strStartIndex;
		vec.pVector = new T[strSize-strStartIndex];
	}
	for (int i = 0; i < vec.Size-vec.StartIndex; ++i)
		stream >> vec.pVector[i];
	return stream;
}
*/
/*
template <class T>
ostream& operator<<(ostream& os, const TVector<T>& v)
{
	os << "Vector: (";
	for (int i = 0; i < v.Size-v.StartIndex; i++)
	{
		os << v.pVector[i];
		if (i == v.Size - v.StartIndex - 1)
			os << ")\n";
		else
			os << ",";
	}
	return os;

}
*/
#endif