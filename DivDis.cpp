#include "DivDis.h"

DivDis::DivDis(const District& dis) : District(dis)
{
	DisType = dis.getDisType();

}

DivDis::~DivDis()
{
}

void DivDis::printResults(const list<Party*>plist) 
{
	PrintPartyNameAndLeader();
	cout << endl << "The candidates are: " << endl;
	for (int i = 1; i < sizeArray; i++)
	{
		if (array[i].reps > 0)
		{
			cout << getLeaderNameByPartyNum(plist, i) << " With " << array[i].reps << " chosen representatives. " << endl;
		}
	}
	cout << endl << "Chosen Representatives:" << endl;
	PrintReps(plist);

}

