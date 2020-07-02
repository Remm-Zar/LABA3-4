#pragma once
#include <initializer_list>
#include <iostream>
using namespace std;
template <class T>
class Vector
{	
	T* m_vector=nullptr;
	int m_amount = 0;
	int m_len=0;
public:
	class VectorIterator
	{
		T* m_pos;
		T* m_vec;
	public:
		VectorIterator(T* pos=nullptr, T* vec=nullptr):m_pos(pos),m_vec(vec)
		{}
		VectorIterator(const VectorIterator& it):VectorIterator(it.m_pos,it.m_vec)
		{}
		~VectorIterator(){}
		VectorIterator& operator++()
		{
			++m_pos;
			return *this;
		}
		VectorIterator& operator++(int)
		{
			VectorIterator temp(*this);
			temp(*this);
			++m_pos;
			return temp;
		}
		VectorIterator& operator--()
		{
			--m_pos;
			return *this;
		}
		VectorIterator& operator--(int)
		{
			VectorIterator temp(*this);
			--m_pos;
			return temp;
		}
		T& operator*()
		{
			return *m_pos;
		}
		VectorIterator& operator=(T& elem)
		{
			*m_pos = elem;
			return *this;
		}
		VectorIterator& operator=(const VectorIterator& it)
		{
			m_pos = it.m_pos;
			m_vec = it.m_vec;
			return *this;
		}
		T* operator->()const//???
		{
			return m_pos;
		}
		VectorIterator& operator +(int a)
		{
			m_pos += a;
			return *this;
		}
		VectorIterator& operator -(int a)
		{
			m_pos -= a;
			return *this;
		}
		int operator -(const VectorIterator& it)
		{
			return m_pos - it.m_pos;
		}
		VectorIterator& operator +=(int a)
		{
			return *this + a;
		}
		VectorIterator& operator -=(int a)
		{
			return *this - a;
		}
		bool operator ==(const VectorIterator& it)
		{
			return ((m_pos==it.m_pos) && (m_vec==it.m_vec));
		}
		bool operator !=(const VectorIterator& it)
		{
			return !(*this == it);
		}
		bool operator <(const VectorIterator& it)
		{
			return  ((m_pos <it.m_pos) && (m_vec == it.m_vec));
		}
		bool operator >(const VectorIterator& it)
		{
			return !((*this < it) || (*this == it));
		}
		bool operator <=(const VectorIterator& it)
		{
			return ((*this<it) || (*this==it));
		}
		bool operator >=(const VectorIterator& it)
		{
			return !(*this < it);
		}
		/*operator (T*)()
		{
			return *m_pos;
		}*/
	};
	typedef VectorIterator IT;
	Vector(){}
	explicit Vector(int amount) :m_amount(amount)
	{
		m_vector = new T[amount + 4];
		m_len = amount + 4;
	}
	explicit Vector(int amount, T elem):m_amount(amount)
	{
		m_vector = new T[amount + 4];
		m_len = amount + 4;
		for (int i = 0; i < m_amount; ++i)
		{
			m_vector[i] = elem;
		}
	}
	Vector(const initializer_list<T>& list) :Vector(list.size())
	{ 
		int count = 0;
		for (auto& elem : list)
		{
			m_vector[count] = elem;
			++count;
		}
	}
	 Vector(IT &begin, IT& end):Vector(end - begin)
	{
		int count = 0;
		while (begin != end)
		{
			m_vector[count] = *begin;
			++begin;
			++count;
		}
	}
	Vector(const Vector& v)
	{
		m_amount = v.m_amount;
		m_len = v.m_len;
		m_vector = new T[m_len];
		for (int i = 0; i < m_amount; ++i)
		{
			m_vector[i] = v.m_vector[i];
		}
	}
	Vector(Vector&& v)noexcept//E!
	{
		m_amount = v.m_amount;
		m_len = v.m_len;
		m_vector = v.m_vector;
		v.m_amount = 0;
		v.m_len = 0;
		v.m_vector = nullptr;
	}
	~Vector()
	{
		if (m_vector != 0)
		{
			delete[]m_vector;
		}		
	}
	Vector& operator=(const Vector& v)noexcept//E!
	{
		if (*this == v)
		{
			return *this;
		}
		if (m_vector != nullptr)
		{
			delete[]m_vector;
		}		
		m_amount = v.m_amount;
		m_len = v.m_len;
		m_vector = new T[m_len];
		for (int i = 0; i < m_amount; ++i)
		{
			m_vector[i] = v.m_vector[i];
		}
		return *this;
	}
	bool operator==(const Vector& v)//E!
	{
		if ((m_amount != v.m_amount)||(m_len!=v.m_len))
		{
			return 0;
		}
		else
		{
			IT b = begin(), e = end(),b_e=const_cast<Vector&>(v).begin();
			while (b != e)
			{
				if (*b != *b_e)
				{
					return 0;
				}
				++b;
				++b_e;
			}
			return 1;
		}
	}
	Vector& operator=(Vector&& v)noexcept//E!
	{
		if (*this == v)
		{
			return *this;
		}
		if (m_vector != nullptr)
		{
			delete[]m_vector;
		}
		m_amount = v.m_amount;
		m_len = v.m_len;
		m_vector = v.m_vector;
		v.m_vector = nullptr;
		v.m_len = 0;
		v.m_amount = 0;
		return *this;
	}
	T& operator [](int index)//E!
	{
		if ((index < 0) || (index >= m_amount))
		{
			throw exception("Wrong index");
		}
		return m_vector[index];
	}
	T at(int index)const//E!
	{
		if ((index < 0) || (index >= m_amount))
		{
			throw exception("Wrong index");
		}
		return m_vector[index];
	}
	IT begin()
	{
		return IT(&m_vector[0]);
	}
	IT end()
	{
		return IT(&m_vector[m_amount]);
	}
	Vector& pushBack(const T elem)noexcept//E!
	{
		_check_memory_(1,false);		
		m_vector[m_amount] = elem;
		++m_amount;
		return *this;
	}
	Vector& popBack()//E!
	{
		if (m_amount - 1 < 0)
		{
			throw exception("Bad popBack");
		}
		m_vector[m_amount-1] = 0;
		--m_amount;
		return *this;
	}
	IT insert(IT pos, const T elem)
	{
		if ((pos < begin()) || (pos >= end()))
		{
			throw exception("Wrong index");
		}
		int pos_marker = pos - begin();
		_check_memory_(1,false);
		IT loc_pos = begin() + pos_marker;
		IT it1=end()-1, it2=it1, lim=loc_pos-1;
		while (lim != it1)
		{
			it1 + 1 = *it2;
			it1 -= 2;
			--it2;
		}
		++m_amount;
		*(++loc_pos) = elem;
		return loc_pos;
	}
	IT insert(IT pos, IT _begin, IT _end)//E!
	{
		if ((pos < begin()) || (pos > end())||(_begin<begin())||(_begin>=end())||(_end<begin())||(_end>end()))
		{
			throw exception("Wrong index");
		}
		int distance = _end - _begin;
		Vector temp(_begin, _end);
		int pos_marker = pos - begin();
		_check_memory_(distance,false);
		IT loc_pos = begin() + pos_marker;
		IT it1=end()-1, it2 =it1, lim=loc_pos-1;
		if (loc_pos+1 < end())
		{			
		    while (it1!=lim)
		    {
			    it1 + distance = *it2;
			    it1 -= distance+1;
			    --it2;
		    }
		}
		++it1;
		IT it_temp = temp.begin();
		while (it_temp!= temp.end())
		{
			it1 = *it_temp;
			++it1;
			++it_temp;
		}
		m_amount += distance;
		return ++it2;
	}
	IT erase(IT pos)
	{
		if ((pos < begin()) || (pos >= end()))
		{
			throw exception("Wrong index");
		}
		IT for_return=pos,it = pos + 1;
		--pos;
		while (it != end())
		{
			pos = *it;
			++pos;
			++it;
		}
		--m_amount;
		return for_return;
	}
	bool empty()
	{
		return m_amount != 0;
	}
	void reserve(int num)
	{
		_check_memory_(num, true);
	}
	int size()
	{
		return m_amount;
	}
	int capacity()
	{
		return m_len;
	}
	void resize(int num)
	{
		if (num <= 0)
		{
			throw exception("Wrong amount");
		}
		IT beg = begin(), end = begin() + num;
		Vector temp(beg, end);
		if (num < m_amount)
		{
			*this = move(temp);		
		}
		else
		{
			if (num > m_amount)
			{
				temp._check_memory_(num - m_amount, true);
				temp.m_amount = num;
				*this = move(temp);
			}
		}
	}
	void clear()
	{
		if (m_vector != nullptr)
		{
			delete[]m_vector;
		}
		m_vector = new T[m_len];
	}
	void _check_memory_(int amount,bool reserve)//E!
	{
		if ((m_len - m_amount - amount <= 0)||(reserve))
		{
			Vector temp(capacity()*2-4);
			temp.m_amount-= capacity() * 2 - 4 - m_amount;
			for (int i = 0; i < temp.m_amount; ++i)
			{
				temp.m_vector[i] = m_vector[i];
			}
			*this = move(temp);
		}
	}
	friend ostream& operator<<(ostream& out, Vector& o)
	{
		Vector<T>::IT beg = o.begin();
		while (beg != o.end())
		{
			out << *beg << " ";
			++beg;
		}
		return out;
	}
};
