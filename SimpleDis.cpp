#include "SimpleDis.h"
SimpleDis::SimpleDis(const District& dis) : District(dis), chosenPartySerial(0)
{
	DisType = dis.getDisType();
}

SimpleDis::~SimpleDis()
{
}

void SimpleDis::updateChosenParty()
{
	int max = 0;
	int index = 1;
	for (int i = 1; i < sizeArray; i++)
	{
		if (array[i].votes > max)
		{
			index = i;
			max = array[i].votes;
		}
	}
	chosenPartySerial = index;
}

void SimpleDis::chosenPartyHelper()
{
	for (int i = 1; i <= sizeArray; i++)
	{
		if (array[i].reps != 0)
			chosenPartySerial = i;
	}
}

void SimpleDis::printResults(const list<Party*>plist)
{
	PrintPartyNameAndLeader();
	updateChosenParty();
	cout << endl << "The Candidate is: " << getLeaderNameByPartyNum(plist, chosenPartySerial);
	cout << endl << "--------" << endl << "Chosen Representatives:" << endl;
	PrintReps(plist);
}





