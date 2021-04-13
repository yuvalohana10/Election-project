#pragma once
#include "Person.h"
#include "Representative.h"
class District;

enum age { minimunAgeToVote = 18};

class Citizen :public Person
{
protected:
	int disNum;
	int choice;
	District* dis;
	Representative* isRep;

public:
	Citizen(const Person& person, int _disNum,District* p,int year);
	Citizen(const Citizen& cit, int year);
	Citizen();
	~Citizen(); //Distructor
	Citizen operator=(const Citizen& cit) const ;

	//getters

	void setRepresentative(int PartyNum);
	int getDisNum() const { return disNum; }
	int getChoice() const { return choice; }
	int getRepParty() const { return isRep->getPartyNum(); }

	//getters for Rep Details;
	int GetPartyNumOfRep() const { return isRep->getPartyNum(); }

	//setters
	void setName(string n) { name = n; }
	void setChoice(int c) { choice = c; }
	void setChoice(int c, int partycount);
	void saveVote(ostream& out);
	friend ostream& operator<<(ostream& os, const Citizen& c);

	//checking if the citizen is also a rep
	bool isHeRep();
	void save(ostream& out) const;
	void checkAge(int yearOfElections) const;


};