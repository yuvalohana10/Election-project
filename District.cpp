#define _CRT_SECURE_NO_WARNINGS
#include "District.h"
#include <iostream>
#include <fstream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
int ser = 0;


void District::save(ostream& out) const
{
	int x = name.length() + 1;
	char* str = new char[x];
	if (str == nullptr)
		throw("Allocation memory failed");
	strcpy(str, name.c_str());
	out.write(rcastcc(&x), sizeof(x));
	out.write(rcastcc(str), x);
	out.write(rcastcc(&numOfReps), sizeof(int));
	out.write(rcastcc(&DisType), sizeof(int));
}

District::District(string n, int repnum, int type) :sizeArray(0), numOfReps(0), DisType(type)
{
	name.append(n);
	serial = ++ser;
	numOfReps = repnum;

}

District::District(const District& dis) :sizeArray(0), numOfReps(dis.getNumOfReps())
{
	name = dis.getName();
	serial = dis.getSerial();
}

District::~District()
{

}

void District::PrintReps(const list<Party*>plist)
{
	int counter = 0;
	for (int i = 1; i < sizeArray; i++) {

		for (auto itr : plist) {
			if(itr->getSerial()==i)
			cout << endl << "Party: " << itr->getPartyName()<< "  - ";
		}
		counter = array[i].reps;
		printPartyPrecent(i);
		cout << endl;
		reps.printRepsByCounter(counter, i,getSerial());
	}
	cout << endl;
}

void District::PrintPartyNameAndLeader()
{
	cout << "|================|" << endl;
	cout << "|     " << getName() << "\t |" << endl;
	cout << "|================|" << endl << "Number of representative :" << getNumOfReps();
}

string District::getLeaderNameByPartyNum(const list<Party*>plist,const int serial)
{	
	for(auto itr: plist)
	{
		if (itr->getSerial() == serial)
			return itr->getLeaderName();
	}
	throw("Cannot found leader name.");
}

void District::printPartyPrecent(int i)
{
	cout << " Won " << array[i].votes << " votes ";
	if (voted == 0 || array[i].votes == 0)
		cout << "  [ 0.000000% of The Votes]" << endl;
	else
		cout << "  [ " << float(array[i].votes) / float(voted) << "% of The Votes]" << endl;

}

void District::saveReps(ostream& out)
{
	for (auto itr : reps.getList())
	{
		if (itr->isHeRep() == true)
		{
			long int id = itr->getId();
			int pnum = itr->GetPartyNumOfRep();
			int dnum = itr->getDisNum();
			out.write(rcastcc(&id), sizeof(id));
			out.write(rcastcc(&pnum), sizeof(pnum));
			out.write(rcastcc(&dnum), sizeof(dnum));

		}
	}
	
}



void District::collectVotesHelper(int numOfParties)
{
	
	int counter = 0;
	sizeArray = numOfParties + 1;
	int _size = numOfParties + 1;
	array = citizens.collectVotes(_size);
	for (int i = 1; i < _size; i++) {
		if (array[i].votes == 0 || this->voted == 0)
			array[i].reps = 0;
		else
			array[i].reps = ((static_cast<float>(array[i].votes) / static_cast<float>(this->voted)) * static_cast<float>(getNumOfReps()) + 0.5);
		counter += array[i].reps;
		if (counter > getNumOfReps())
		{
			while (counter > getNumOfReps())
			{
				array[i].reps--;
				counter--;
			}
			return;
		}
	}
}

void District::AddToCitizenList(Citizen* p)
{
	citizens.AddToCTail(p);
}

void District::AddToRepList(Citizen* p)
{
	reps.AddToCTail(p);
}

ostream& operator<<(ostream& os, const District& c)
{
	os << c.getName() << "\t\t  " << c.getSerial() << "\t\t     " << c.getNumOfReps() << endl;
	return os;
}