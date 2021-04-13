#pragma once
#include "CitizenList.h"
#include "PartyList.h"
#include <string>
#include <iostream>
using namespace std;


class District
{
protected:
	string name;
	CitizenList citizens;
	CitizenList reps;
	DynamicArray<repsAndVotes> array;
	int numOfReps;
	int serial;
	int voted = 0;
	int DisType;//1-Normal District, 2-Divided District
	//This array save the numbers od reps and votes for each party in the district.
	//in cell [1], the data for party 1.
	int sizeArray;

public:
	District(string n, int repnum, int type);
	District(const District& dis);
	District() = default;
	virtual ~District();

	

	//getters
	string getName()         const { return name; }
	int getNumOfReps()       const { return numOfReps; }
	int getSerial()          const { return serial; }
	int getVoted()           const { return voted; }
	float getVotePrecent()   const { return calcVotePrecent(); }
	int getVotesCell(int i)  const { return array[i].votes; }
	int getRepsCell(int i)  const { return array[i].reps; }
	int getDisType()         const { return DisType; }

	void UpdateVotePeopleByone(void) { voted++; }
	void AddToCitizenList(Citizen* p);
	void AddToRepList(Citizen* p);


	float calcVotePrecent() const { return float(voted) / float(citizens.getCount()); }

	void PrintPartyNameAndLeader();
	string getLeaderNameByPartyNum(const list<Party*>plist,const  int serial);

	//This function update array
	void collectVotesHelper(int numOfParties);
	void PrintReps(const list<Party*>plist);
	virtual void printResults(const list<Party*>plist) {};

	void save(ostream& out) const;
	void printPartyPrecent(int i);
	friend ostream& operator<<(ostream& os, const District& c);
	void saveReps(ostream& out);
};

