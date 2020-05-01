#include <iostream>
#include <utility>
#include "City.h"

using std::istream;
using std::ostream;

City::City(string name, long peoplesCount): _name(std::move(name)), _peoplesCount(peoplesCount)
{
}

City::City(): _name("___"), _peoplesCount(0)
{
}

bool City::operator ==(City& other)
{
	return _name == other._name && _peoplesCount == other._peoplesCount;
}

istream& operator>>(istream& in, City& clone)
{
	return in >> clone._name >> clone._peoplesCount;
}

ostream& operator<<(ostream& out, City& clone)
{
	return out << clone._name << ' ' << clone._peoplesCount;
}
