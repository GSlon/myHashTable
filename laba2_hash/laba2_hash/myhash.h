#pragma once

#include "user.h"
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <utility>
#include <cmath>
#include <string>
#include <list>
#include <bitset>
#include <cstdlib>
#include <cmath>

using std::vector;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::iterator;
using std::pair;
using std::string;
using std::list;
using std::endl;
using std::is_same;
using std::make_pair;
using std::bitset;

const int SIZE = 1024;

// ������� ����� ���������� ������ (unordered_map) (map - ����� ���������)
template <typename Kty = int, typename Ty = int>
class myhash
{
	// �������� ������������ ����
	static_assert(is_same<Kty, int>::value || is_same<Kty, char>::value || is_same<Kty, string>::value, L"������������ ���");

protected:
	vector<list<pair<Kty, Ty>>> table;			// ������ ����� ������ (���������� ����� ���������� ��� ������� � ������ T)
	list<unsigned int> hsave;					// ������ ���� (��� �������� ������ � ������ �� ������)

	unsigned int Hash(string) const;
	unsigned int Hash(int) const;
	unsigned int Hash(char) const;
	bool saveHash(unsigned int);				// ��������� ���� � ��������� list (��� �������� ������ � ������)
	void set_def(const Kty & , unsigned Hkey);	// �������� � table �������� �� ���������

public:
	myhash();
	myhash(const Kty& , const Ty& );
	myhash(const myhash& );
	~myhash() = default;

	auto Find(const Kty& );
	bool empty() const;
	void clear();
	auto lend(const Kty& );				// ���������� iterator �� end ��������� �����
	bool erase(const Kty& );
	void insert(const Kty&, const Ty& );
	int size() const;
	bool existence(const Kty& );				// ��������� ������������� �������� �� �����

	Ty& operator[] (const Kty& );
	myhash& operator= (const myhash& );


	template<typename T, typename U>
	friend ostream& operator<< (ostream&, const myhash<T, U>& );

	template<typename T, typename U>
	friend ofstream& operator<< (ofstream&, myhash<T, U>& );		// �������� �����

	template<typename T, typename U>
	friend istream& operator>> (istream&, myhash<T, U>& );
	
	template<typename T, typename U>
	friend ifstream& operator>> (ifstream&, myhash<T, U>& );		// �������� ����
};

template <typename Kty, typename Ty>
inline myhash<Kty, Ty>::myhash()
{
	table.resize(0);
	hsave.resize(0);
}

template<typename Kty, typename Ty>
inline myhash<Kty, Ty>::myhash(const Kty &key, const Ty &value)
{
	unsigned Hkey = Hash(key);
	table.resize(Hkey+1);
	table[Hkey].push_back(make_pair(key, value));
	hsave.push_back(Hkey);		// ������ ���� (���������� ��� ������ � ������)
}

template<typename Kty, typename Ty>
inline myhash<Kty, Ty>::myhash(const myhash &hash2)
{
	this->table = hash2.table;
	this->hsave = hash2.hsave;
}

//������������ �������� ����� �������� �������
template<typename Kty, typename Ty>
inline unsigned int myhash<Kty, Ty>::Hash(string key) const
{
	unsigned int Hkey = 0;

	for (int i = 0; i < key.size(); i++)
		Hkey = (Hkey * 101 + (unsigned int)key[i]) % SIZE; // Hkey <= SIZE
	
	return Hkey;
}

template<typename Kty, typename Ty>
inline unsigned int myhash<Kty, Ty>::Hash(int key) const
{	
	unsigned int Hkey = 0;
	string str = " ";
	str.resize(11);

	int j = 1, k = 0;
	while (j < 10)
	{
		str[k++] = (key / j) << k;
		j++;
	}

	for (int i = 0; i < str.size(); i++)
		Hkey = (Hkey * 101 + (unsigned int)str[i]) % SIZE; // Hkey <= SIZE

	return Hkey;
}

template<typename Kty, typename Ty>
inline unsigned int myhash<Kty, Ty>::Hash(char key) const
{
	return (unsigned int)key % SIZE;
}

template<typename Kty, typename Ty>
inline bool myhash<Kty, Ty>::saveHash(unsigned int Hkey)
{
	auto iter = find(hsave.begin(), hsave.end(), Hkey);

	if (iter != hsave.end())	// ����� ��� ��� ����
		return false;
	else
	{
		hsave.push_back(Hkey);	// ������ ���� ��� -> ���������
		return true;
	}
}

template<typename Kty, typename Ty>
inline void myhash<Kty, Ty>::set_def(const Kty &key, unsigned Hkey)
{
	/*
	if (is_same<Ty, string>::value)		// ����� �� ��������� ����� �� " ", � "0"
	{
		Ty def = (Ty)1;
		table[Hkey].push_back(make_pair(key, def));
	}
	if (is_same<Ty, char>::value)
	{
		Ty def = (Ty)1;
		table[Hkey].push_back(make_pair(key, def));
	}
	else
	*/

	table[Hkey].push_back(make_pair(key, Ty()));
	saveHash(Hkey);			//��������� ���
}

template<typename Kty, typename Ty>
inline auto myhash<Kty, Ty>::Find(const Kty &key) 
{
	unsigned Hkey = Hash(key);

	if (Hkey >= table.size())
	{
		table.resize(Hkey + 1);		// ��������� �������, ����� ������� �������� �� ����������� list
		return table[Hkey].end();	// ����� ��� ������ ��������
	}

	auto iter = find(hsave.begin(), hsave.end(), Hkey);		// ���� � ����� �����

	if (iter == hsave.end())		// ��� ������ ���� � ����� ����� (���������� �������� �� �����)
		return table[Hkey].end();

	// ���� � ����� -> ���� 
	for (auto iter = table[Hkey].begin(); iter != table[Hkey].end(); ++iter)
		if (iter->first == key)
			return iter;

	return table[Hkey].end();		// ��� ������ ��������
}

template<typename Kty, typename Ty>
inline bool myhash<Kty, Ty>::empty() const
{
	if (hsave.size() == 0)
		return true;
	else
		return false;
}

template<typename Kty, typename Ty>
inline void myhash<Kty, Ty>::clear()
{
	size_t size = table.size();
	table.clear();
	table.resize(size);
	hsave.clear();
}

template<typename Kty, typename Ty>
inline auto myhash<Kty, Ty>::lend(const Kty &key) 
{
	unsigned Hkey = Hash(key);

	if (Hkey >= table.size())
		table.resize(Hkey + 1);		// ��������� �������, ����� ������� �������� �� ����������� list
	
	return table[Hkey].end();
}

template<typename Kty, typename Ty>
inline bool myhash<Kty, Ty>::erase(const Kty &key)
{
	unsigned Hkey = Hash(key);

	if (Hkey >= table.size())		// ����� ��� ������ ��������
		return false;

	if (table[Hkey].size() == 0)	// ������ ����� - ������� ������
		return false;				
	else									
	{
		auto iter = this->Find(key);		// ���� � �������
		
		if (iter != table[Hkey].end())		// �����
		{
			table[Hkey].erase(iter);		// ������� �������

			if (table[Hkey].size() == 0)	// ���� list ���� - ������� �� ������ ����� (���� �������� - ������ �������)
			{
				auto ifind = find(hsave.begin(), hsave.end(), Hkey);
				hsave.erase(ifind);			
			}
		}
		else								// �� ����� ������� � ������ ������
			return false;
	}
		
	return true;
}

template<typename Kty, typename Ty>
inline Ty& myhash<Kty, Ty>::operator[](const Kty &key)
{
	unsigned Hkey = Hash(key);

	// ����������� ������, ���� Hkey ������ vector.size()
	if (Hkey >= table.size())
		table.resize(Hkey + 1);

	//���� ������ ����, �� ������ ������� 
	if (table[Hkey].size() == 0)
	{
		set_def(key, Hkey);			   // ��������� ��������� �� ���������
		auto iter = table[Hkey].begin();
		return iter->second;		   // ���������� ������ �� �������� ��� ������ ������ � �����
	}

	// ���� ������� �� ����� � �������� �����
	auto iter = this->Find(key);

	if (iter == table[Hkey].end())	  //� �������� ����� ������� �������� ��� -> ���������  
	{
		set_def(key, Hkey);
		auto it = table[Hkey].begin();
		return it->second;			  // ���������� ������ �� �������� ��� ������ ������ � �����
	}
	else
		return iter->second;		  //������ ������� -> ����������
}

template<typename Kty, typename Ty>
inline myhash<Kty, Ty>& myhash<Kty, Ty>::operator=(const myhash &hash2)
{
	this->table = hash2.table;
	this->hsave = hash2.hsave;

	return *this;
}

template<typename Kty, typename Ty>
inline void myhash<Kty, Ty>::insert(const Kty &key, const Ty &value)
{
	unsigned Hkey = Hash(key);

	// ����������� ������, ���� Hkey ������ vector.size()
	if (Hkey >= table.size())
		table.resize(Hkey + 1);

	if (table[Hkey].size() == 0)	//������ ������
	{
		table[Hkey].push_back(make_pair(key, value));	//����� ����� ������
		saveHash(Hkey);		//��������� ���
		return;
	}

	// ���������, ��� �� ��� ������ ����� � ������ �������� ������
	//auto iter = find(table[Hkey].begin(), table[Hkey].end(), make_pair(key, value));
	auto iter = this->Find(key);

	if (iter != table[Hkey].end())	// ����� ������� ���� -> ��������������
		table[Hkey].erase(iter);
	
	table[Hkey].push_back(make_pair(key, value));
	saveHash(Hkey);		//��������� ���

	return;
}

template<typename Kty, typename Ty>
inline int myhash<Kty, Ty>::size() const
{
	return hsave.size();
}

template<typename Kty, typename Ty>
inline bool myhash<Kty, Ty>::existence(const Kty &key)
{
	unsigned Hkey = Hash(key);
	auto iFind = Find(key);

	if (iFind != table[Hkey].end())
		return true;
	else
		return false;
}

template<typename Kty, typename Ty>
inline ostream& operator<< (ostream &out, const myhash<Kty, Ty> &hash)
{
	// � ������� hsave ��� ����, �� ������� ��������� ������ ������� �������
	for (auto iHash = hash.hsave.begin(); iHash != hash.hsave.end(); ++iHash)
		for (auto iList = hash.table[*iHash].begin(); iList != hash.table[*iHash].end(); ++iList)
			out << iList->first << " : " << iList->second << endl;

	return out;
}

template<typename Kty, typename Ty>
inline ofstream& operator<<(ofstream &out, myhash<Kty, Ty> &hash)
{
	// � ������� hsave ��� ����, �� ������� ��������� ������ ������� �������
	for (auto iHash = hash.hsave.begin(); iHash != hash.hsave.end(); ++iHash)
		for (auto iList = hash.table[*iHash].begin(); iList != hash.table[*iHash].end(); ++iList)
			out << iList->first << " " << iList->second << endl;

	return out;
}

template<typename Kty, typename Ty>
inline istream& operator>>(istream &in, myhash<Kty, Ty> &hash)
{
	Kty key;
	Ty value;
	in >> key;
	in >> value;
		
	if (!in.fail())
		hash.insert(key, value);

	return in;
}

template<typename Kty, typename Ty>
inline ifstream& operator>>(ifstream &in , myhash<Kty, Ty> &hash)
{
	Kty key;
	Ty value;

	while (!in.eof())
	{
		in >> key;
		in >> value;

		if (!in.fail())
			hash.insert(key, value);
		else
			break;
	}

	return in;
}


// �������� ����� ��� ������ �� �����������
// ����� Ty - ��������� � �������� find (��� ������ �� ������)
template <typename Kty = string , typename Ty = user>
class myhashBook: public myhash<Kty, Ty>
{
	// �������� ������������ ����
	static_assert(is_same<Kty, int>::value || is_same<Kty, char>::value || is_same<Kty, string>::value, L"������������ ���");

public:
	vector<Ty> find_data(const Ty& ) const;

};

template<typename Kty, typename Ty>
inline vector<Ty> myhashBook<Kty, Ty>::find_data(const Ty &data) const
{
	vector<Ty> InfoMass;
	
	for (auto iVect = this->hsave.begin(); iVect != this->hsave.end(); ++iVect)
		for (auto iList = this->table[*iVect].begin(); iList != this->table[*iVect].end(); ++iList)
			if (iList->second.find(data))
				InfoMass.push_back(iList->second);

	return InfoMass;
}
