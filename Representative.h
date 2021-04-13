#pragma once

class Representative
{
private:

	long int id;
	int PartyNum;
	int DisNum;

public:
	Representative(long int _id, int pn, int dn);

	//getters
	long int getId()  const { return id; }
	int getPartyNum() const { return PartyNum; }
	int getDisNum()   const { return DisNum; }
};

