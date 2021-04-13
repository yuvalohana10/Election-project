#pragma once
#include "CitizenList.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

class Party {

private:
	string name;
	Citizen* leader;
	CitizenList* repList;
	int serial;

public:

	Party(string name);
	~Party();

	//getters
	const Citizen* getLeader() { return leader; }
	const string getPartyName()	   const { return name; }
	string	getLeaderName()        const { return leader->getName(); }
	int getSerial()                const { return serial; }

	//setters
	bool SetLeader(Citizen* c) { leader = c; if (leader == nullptr)return false; return true; }

	friend ostream& operator<<(ostream& os, const Party& c);

	void printReps() const;
	void AddRep(Citizen* p);

	//save to file
	void save(ostream& out) const;
};

