#include "PartyList.h"

;

const string PartyList::getPartyNameBySerial(int partyNum)
{
	for (auto itr : plist)
	{
		if (itr->getSerial() == partyNum)
			return itr->getPartyName();
	}
	return nullptr;
}

Party* PartyList::CreateParty(string name)
{
	Party* tmp = new Party(name);
	if (tmp == nullptr)
		throw("Memmory allocation failed.");
	return tmp;
}

PartyList::~PartyList()
{
	for (auto itr : plist)
		delete itr;
}

const string PartyList::getLeaderNameByPartyNum(int partyNum)
{
	for (auto itr : plist)
	{
		if (itr->getSerial() == partyNum)
			return itr->getLeaderName();
	}
	throw("Unable to find Leader.");
}



void PartyList::printList()
{
	for (auto itr : plist)
	{
		cout << *itr << endl;
	}
}

void PartyList::AddRepToRightParty(Citizen* p, int ser)
{

	for(auto itr: plist)
	{
		if (itr->getSerial() == ser)
		{
			itr->AddRep(p);
			return;
		}
	}
	throw("cannot found party");
}

void PartyList::printPartyAndLeaderNamebySerial(int partyNum)
{
	for (auto itr : plist)
	{
		if (itr->getSerial() == partyNum)
		{
			cout << "Candidate: " << itr->getLeaderName() << "\t Party: ";
			cout << itr->getPartyName() << "\t";
			return;
		}
	}
}

void PartyList::saveAllParties(ostream& out)
{
	int pnum = getCount();
	out.write(rcastcc(&pnum), sizeof(pnum));
	for (auto itr : plist)
	{
		itr->save(out);
	}
	
}