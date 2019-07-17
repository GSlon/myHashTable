#pragma once

#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
#include <utility>
#include <cmath>
#include <string>
#include <cstring>

using std::vector;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::fstream;
using std::iterator;
using std::swap;
using std::map;
using std::pair;
using std::string;
using std::endl;
using std::cout;

// ������ � ������������ (������ ����� �������� ������, ������� � struct)
struct user
{
	user();
	user(const string&, const string&, const string&, 
		 const string&, const string&, const string& );

	~user() = default;

	//string tel_num;	// ����� ������
	string surname;		// �������
	string name;
	string patronym;	// ��������
	string email;
	string company;
	string position;	// ���������

	bool find(const user& ) const;		//�������� '*' - ������ �� �������������
	bool operator== (const user& ) const;

	friend ostream& operator<< (ostream&, const user& );
	friend istream& operator>> (istream&, user& );
	friend ifstream& operator>> (ifstream&, user& );				// �������� ����
	friend ofstream& operator<< (ofstream&, const user& );			// �������� �����
};