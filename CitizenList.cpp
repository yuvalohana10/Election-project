#include "CitizenList.h"
#include "DynamicArray.h"
CitizenList::CitizenList()
{
}

CitizenList::~CitizenList()
{
	for (auto itr : clist)
	{
		delete itr;
	}
}

Citizen* CitizenList::findCitizen(int idNum)
{
	for (auto itr : getList())
	{
		if (itr->getId() == idNum)
			return itr;
	}
	throw ("Citizen not found.");
}

void CitizenList::print(void)
{
	for (auto itr : getList())
		cout << *itr << endl;
	
}


Citizen* CitizenList::CreateCitizen(const Person& p, int dnum, District* dis, int year)
{
	Person c(p.getName(), p.getId(), p.getYearOfBirth());
	
	Citizen* tmp = new Citizen(c, dnum, dis, year);
	if (tmp == nullptr)
		throw("Memory allocation failed.");
	return tmp;

}


void initArray(repsAndVotes* array,int sizeArray)
{

	for (int i = 0; i < sizeArray; i++)
	{
		array[i].votes = 0;
		array[i].reps = 0;
	}
	
}


DynamicArray<repsAndVotes> CitizenList::collectVotes(int numOfParties)
{
	int size = numOfParties + 1;
	DynamicArray<repsAndVotes> array(size,0);
	for (auto itr : clist)
		array[itr->getChoice()].votes++;
	
	return array;
}

//repsAndVotes* CitizenList::CollectVotes(int numOfParties)
//{
//    int size = numOfParties + 1;
//	repsAndVotes* array = new repsAndVotes[size];
//	initArray(array, size);
//	for (auto itr : clist)
//		array[itr->getChoice()].votes++;
//	return array;
//
//}

int CitizenList::PrintRepsByParty(int pnum, int howmany)
{

	int i = 0;
	for (auto itr : getList())
	{
		if (i < howmany)
			return (howmany - i);
		if (pnum == itr->getRepParty())
		{
			cout << "Name: " << itr->getName() << "\tID:" << itr->getId() << endl;
			i++;
		}
	}
	return (howmany - i);
}

void CitizenList::updateVotes(int* collectVotes, int size, int dNum)
{
	for (auto itr : clist)
		collectVotes[itr->getChoice()]++;
	
}

void CitizenList::saveAllCitizens(ostream& out) const
{

	int cnum = getCount();
	out.write(rcastcc(&cnum), sizeof(cnum));
	for (auto itr : clist)
	{
		itr->save(out);
	}
}

void CitizenList::SaveAllVotes(ostream& out, int votesNum) const
{
	
	out.write(rcastcc(&votesNum), sizeof(votesNum));
	for (auto itr : clist)
	{
		itr->saveVote(out);
	}

}

void CitizenList::printRepsByCounter(int& counter, const int partyNum,int serial)
{
	for(auto itr : clist)
	{
		if (itr->getRepParty() == partyNum && itr->getDisNum() == serial)
		{
			cout << *itr;
			counter--;
		}
	}
}

