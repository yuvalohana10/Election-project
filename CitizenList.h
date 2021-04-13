#pragma once
#pragma once
#include "Citizen.h"
#include "DynamicArray.h"
#include <list>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>



struct repsAndVotes
{
	int reps;
	int votes;
};


class CitizenList
{
private:
	list<Citizen*> clist;
public:

	CitizenList();
	~CitizenList();
	int getCount(void) const { return clist.size(); }
	void AddToCTail(Citizen* d) { clist.push_back(d); }
	Citizen* getHead() { return clist.front(); }
	Citizen* findCitizen(int idNum);
	void print(void);

	DynamicArray<repsAndVotes> collectVotes(int numOfParties);
	Citizen* CreateCitizen(const Person& p, int dnum,District* dis,int year);
	list<Citizen*> getList() { return clist; }
	//repsAndVotes* CollectVotes(int numOfParties);
	int PrintRepsByParty(int pnum, int howmany);
	void updateVotes(int* collectVotes, int size, int dNum);
	void saveAllCitizens(ostream& out) const;
	void SaveAllVotes(ostream& out, int VotesNum) const;
	void printRepsByCounter(int& counter, const int partyNum,int serial);

};

