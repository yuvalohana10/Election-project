#define _CRT_SECURE_NO_WARNINGS
#include "Citizen.h"
#include <string>
#include <fstream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>


Citizen::Citizen(const Person& person, int _disNum, District* p, int year) :Person(person), disNum(_disNum), choice(0), isRep(nullptr), dis(p)
{
	checkAge(year);
}
Citizen::Citizen(): Person(), disNum(0), choice(0),isRep(nullptr),dis(nullptr)
{

}
Citizen::~Citizen()
{
}
Citizen::Citizen(const Citizen& cit, int year) : Person(Person(cit.getName(), cit.getId(), cit.getYearOfBirth()))
{
	this->setChoice(cit.getChoice());
	this->dis = cit.dis;
	this->isRep = cit.isRep;
}

Citizen Citizen::operator=(const Citizen& cit) const
{
	if (this != &cit)
	{
		*this = Citizen(cit);
		return *this;
	}
	return *this;
}


ostream& operator<<(ostream& os, const Citizen& c)
{

	os << "Name: " << c.getName() << "\tID: " << c.getId() << " Birth: " << c.getYearOfBirth() << " District: " << c.getDisNum() <<endl;
	return os;
}


void Citizen::setRepresentative(int PartyNum)
{
		Representative* tRep = new Representative(id, PartyNum, disNum);
		if(tRep == nullptr)
			throw("Memory allocation failed.");	
		isRep = tRep;	
}

void Citizen::setChoice(int c, int partycount)
{
	if (c<1 || c>partycount)
		throw("Invalid input.");
	else
		choice = c;
}

void Citizen::saveVote(ostream& out)
{
	if (choice != 0)
	{
		out.write(rcastcc(&id), sizeof(id));
		out.write(rcastcc(&choice), sizeof(choice));
	}

}

bool Citizen::isHeRep()
{
	if (isRep != nullptr)
		return true;
	else
		return false;
}

void Citizen::save(ostream& out) const
{
	int x = name.length();
	char* str = new char[x + 1];
	strcpy(str, name.c_str());
	out.write(rcastcc(&x), sizeof(x));
	out.write(rcastcc(str), x);
	out.write(rcastcc(&id), sizeof(id));
	out.write(rcastcc(&yearOfBirth), sizeof(yearOfBirth));
	out.write(rcastcc(&disNum), sizeof(disNum));
}
void Citizen::checkAge(int yearOfElections) const
{
	if (yearOfElections - this->getYearOfBirth() < minimunAgeToVote)
		throw("Citizen not allowed to vote.");

}
