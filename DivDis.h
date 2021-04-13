#pragma once
#include "District.h"
#include "PartyList.h"
class DivDis : public District
{

public:

	list<Citizen*> getlist() { return citizens.getList(); }
	DivDis(const District& dis);
	virtual ~DivDis();
	virtual void printResults(const list<Party*>plist) override;

};

