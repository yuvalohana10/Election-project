#pragma once
#include "District.h"
#include "SimpleDis.h"
#include "DivDis.h"
#include <list>
using namespace std;

class DistrictList
{
private:
	list<District*> dlist;
public:
	DistrictList() {}
	~DistrictList();
	District* getHead() { return dlist.front(); }

	SimpleDis* CreateSimDistrict(const District& dis);
	DivDis* CreateDivDistrict(const District& dis);

	District* ReturnPointerToRightDis(int dnum);
	list<District*> getList() { return dlist; }

	void AddToDTail(District* p) { dlist.push_back(p); }
	void AddCitToRightDis(Citizen* c, int ser);
	void AddRepToRightDis(Citizen* c, int ser);
	int AllDisRepNum() const;
	void print();
	District* findDisByNum(int num);
	int countAllVotes();
	void saveAllDis(ostream& out);
	void saveAllReps(ostream& out);
	int getCount() const { return dlist.size(); }
};

