#define _CRT_SECURE_NO_WARNINGS
#include "Party.h"


int pSerial = 0;

Party::Party(string name) :leader(new Citizen()), repList(new CitizenList())
{
	this->name.append(name);
	serial = ++pSerial;
}

Party::~Party()
{
}

void Party::AddRep(Citizen* p)
{
	repList->AddToCTail(p);
}

ostream& operator<<(ostream& os, const Party& c)
{
	os << "Name: " << c.getPartyName() << " Serial number: " << c.getSerial() << " Candidate for the presidency: "
		<< c.getLeaderName() << endl << "Representatives: " << endl;
	c.printReps();
	return os;
}

void Party::printReps() const
{
	repList->print();
}

void Party::save(ostream& out) const
{
	long int leaderId = leader->getId();
	int x = name.length();
	char* str = new char[x + 1];
	strcpy(str, name.c_str());
	out.write(rcastcc(&x), sizeof(x));  //save the size of the name
	out.write(rcastcc(str), x); 		//save party name 
	out.write(rcastcc(&serial), sizeof(serial));	// save party serial number
	out.write(rcastcc(&leaderId), sizeof(leaderId));	//save leader id
	int repNum = repList->getCount();	
	out.write(rcastcc(&repNum), sizeof(repNum));	// save the number of the representatives if the party
	//save all the reps of the party, id the district number
	for (auto itr : repList->getList())
	{
		int repId = itr->getId();
		out.write(rcastcc(&repId), sizeof(repId));
		int PartyNum = itr->GetPartyNumOfRep();
		out.write(rcastcc(&PartyNum), sizeof(PartyNum));
		int repDis = itr->getDisNum();
		out.write(rcastcc(&repDis), sizeof(repDis));
	}


} 
