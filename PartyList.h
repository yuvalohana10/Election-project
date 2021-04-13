#pragma once
#include "Party.h"
#include <list>

class PartyList
{
private:
	list<Party*> plist;
public:
	~PartyList();
	const string getLeaderNameByPartyNum(int partyNum);
	const string getPartyNameBySerial(int partyNum);

	Party* getHead() { return plist.front(); }
	Party* CreateParty (string name);

	void AddToTail(Party* p) { plist.push_back(p); }
	int getCount() const { return plist.size(); }
	list<Party*> getList() const { return plist; }
	void printList();
	void AddRepToRightParty(Citizen* p, int ser);
	void printPartyAndLeaderNamebySerial(int partyNum);
	void saveAllParties(ostream& out);
};

