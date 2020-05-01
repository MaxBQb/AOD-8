#pragma once
#include <string>
#include <iostream>

using std::string;
using std::istream;
using std::ostream;

class City
{
private:
	string _name;
	unsigned _peoplesCount;
public:
	City(string name, long peoplesCount);
	City();
	bool operator ==(City& other);
	istream& operator >>(istream& in, City& clone);
	ostream& operator <<(ostream& out, City& clone);
};
