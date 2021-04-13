#pragma once
#include"District.h"

class SimpleDis : public District
{
private:
	int chosenPartySerial;

public:

	SimpleDis(const District& dis);
	virtual ~SimpleDis();
	virtual void printResults(const list<Party*>plist) override;
	list<Citizen*> getlist() { return citizens.getList(); }

	//getters

	int getPartySerial() const { return chosenPartySerial; }

	void updateChosenParty();

	void chosenPartyHelper();




};