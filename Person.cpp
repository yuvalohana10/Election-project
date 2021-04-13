#include "Person.h"

Person::Person():id(0)
{
}

Person::Person(const Person& per)
{
	name = per.getName();
	id = per.getId();
	yearOfBirth = per.getYearOfBirth();
	CheckID();
}

Person::Person(string n, long int id, int year) :id(id), yearOfBirth(year)
{
	name.append(n);
	CheckID();
}

void Person::CheckID()
{
	string idToCheck = to_string(id);
	int count = 0;
	for (auto itr : idToCheck)
	{
		if (itr < '0' || itr > '9')
			throw("Invalid ID.");
		count++;
	}
	if (count != IDLen)
		throw("Invalid ID.");

}

