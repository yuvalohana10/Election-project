#include "DistrictList.h"

DistrictList::~DistrictList()
{
		for (auto itr : dlist)
		{
			delete itr;
		}
}

SimpleDis* DistrictList::CreateSimDistrict(const District& dis)
{
	SimpleDis* tmp = new SimpleDis(dis);
	if (tmp == nullptr)
		throw("Memory Allocation failed");
		return tmp;
	}

DivDis* DistrictList::CreateDivDistrict(const District& dis)
{
	DivDis* tmp= new DivDis(dis);
	if(tmp == nullptr)
		throw("Memory Allocation failed");

	return tmp;
}

District* DistrictList::ReturnPointerToRightDis(int dnum)
{
	for (auto itr : dlist)
	{
		if (itr->getSerial() == dnum)
			return itr;
	}
	throw("District was not found.");
}

void DistrictList::AddCitToRightDis(Citizen* c, int ser)
{
	for (auto itr : dlist)
	{
		if (itr->getSerial() == ser)
		{
			itr->AddToCitizenList(c);
			return;
		}
	}
	throw ("District Was Not Found");
	
}

void DistrictList::AddRepToRightDis(Citizen* c, int ser)
{
 for (auto itr : dlist)
	{
		if (itr->getSerial() == ser)
		{
			itr->AddToRepList(c);
			return;
		}
	}
	throw ("District Was Not Found");
}

int DistrictList::AllDisRepNum() const
{
	int count = 0;
	for (auto itr : dlist)
	{
		count += itr->getNumOfReps();
	}
	return count;
}
	

void DistrictList::print()
{
		if (dlist.empty())
		{
			cout << "There are no Districts yet." << endl;
			return;
		}
		else
		{
			int i = 0;
			cout << "|=================================================|" << endl;
			cout << "|   Name\t\tSerial\t\tRep Count |" << endl;
			cout << "|=================================================|" << endl << endl;
			for (auto itr : dlist)
			{
				cout << ++i << ". ";
				cout << *itr;
			}
		}

	
		
}

District* DistrictList::findDisByNum(int num)
{
	for (auto itr : dlist)
	{
		if (itr->getSerial() == num)
			return itr;
	}
	throw("District Was not found.");
	
}


void DistrictList::saveAllDis(ostream& out)
{
	int dnum = dlist.size();
	out.write(rcastcc(&dnum), sizeof(int));
	for (auto itr : dlist)
	{
		itr->save(out);
	}
}


void DistrictList::saveAllReps(ostream& out)
{
	int repscount = AllDisRepNum();
	out.write(rcastcc(&repscount), sizeof(repscount));
	for (auto itr : dlist)
	{
		itr->saveReps(out);
	}
}

int DistrictList::countAllVotes()
{
	int count = 0;

	for (auto itr : dlist)
	{
		count += itr->getVoted();
	}
	return count;
}