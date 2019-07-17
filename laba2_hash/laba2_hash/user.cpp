#include "stdafx.h"
#include "user.h"

user::user()
{
	surname = "*";
	name = "*";
	patronym = "*";
	email = "*";
	company = "*";
	position = "*";
}

user::user(const string &sur, const string &nam, const string &pat, 
		   const string &email, const string &comp, const string &pos)
{
	this->surname = sur;
	this->name = nam;
	this->patronym = pat;
	this->email = email;
	this->company = comp;
	this->position = pos;
}

bool user::find(const user &data) const
{
	if (data.surname != "*")
		if (surname.find(data.surname) == std::string::npos)
			return false;
	
	if (data.name != "*")
		if (name.find(data.name) == std::string::npos)
			return false;
	
	if (data.patronym != "*")
		if (patronym.find(data.patronym) == std::string::npos)
			return false;

	if (data.email != "*")
		if (email.find(data.email) == std::string::npos)
			return false;

	if (data.company != "*")
		if (company.find(data.company) == std::string::npos)
			return false;

	if (data.position != "*")
		if (position.find(data.position) == std::string::npos)
			return false;

	return true;
}

bool user::operator==(const user &data2) const
{
	if (surname != data2.surname || name != data2.name || patronym != data2.patronym ||
		email != data2.email || company != data2.company || position != data2.position)
			return false;

	return true;
}

ostream& operator<<(ostream &out, const user &data)
{
	out << data.surname << " " << data.name << " " << data.patronym << " " << 
		data.email << " " << data.company << " " << data.position;

	return out;
}

istream& operator>>(istream &in, user &data)
{
	in >> data.surname;
	in >> data.name;
	in >> data.patronym;
	in >> data.email;
	in >> data.company;
	in >> data.position;

	return in;
}

ifstream& operator>>(ifstream &in, user &data)
{
	in >> data.surname >> data.name >> data.patronym >> data.email >>
		data.company >> data.position;

	return in;
}

ofstream& operator<<(ofstream &out, const user &data)
{
	out << data.surname << " " << data.name << " " << data.patronym << " " <<
		data.email << " " << data.company << " " << data.position;

	return out;
}
