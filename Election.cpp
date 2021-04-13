#define _CRT_SECURE_NO_WARNINGS
#include "Election.h"
#include "DivDis.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

enum choise
{
	addDistrict = 1,
	addCitizen = 2,
	addParty = 3,
	addRep = 4,
	printDistricts = 5,
	printCitizens = 6,
	printParties = 7,
	vote = 8,
	printResults = 9,
	exitChoise = 10,
	saveToFile = 11,
	loadFromFile = 12,
	newElections = 1,
	loadElections = 2,
	exitPreMenu = 3,
	normalElections = 1,
	simpleElections = 2,
	simpleDistrict = 1,
	divDistrict = 2
};

//print the first menu
void Election::printPreMenu()
{
	cout << "-- Welcome ! --" << endl;
	cout << "Please Choose an Option:" << endl << endl;
	cout << "1. Create New Elections" << endl;
	cout << "2. Load Elections" << endl;
	cout << "3. Exit" << endl;
	int res;
	cin >> res;
	try {
		//if the user chose to start new election
		if (res == newElections) {
			date = date.ElecDate(); //ask for date
			electionTypeConsole();
			if (electionType == 0)
				throw("Incorrect Option."); //Eror input
			else
			{
				if (electionType == simpleElections) //for simple election 
					creatOneDis();
				MainMenu(); //print main menu
			}
		}
		else if (res == loadElections)
		{
			loadfile();
			MainMenu();
		}
		else if (res == exitPreMenu)
			exit(0);
		else
			throw("Incorrect Option.");	}
	catch (const char* msg) { cout << "Error: " << msg << endl, exit(-1); }
	
}

int Election::printMenu()
{

	cout << "Choose an option:" << endl;
	cout << "1.  Add district" << endl;
	cout << "2.  Add citizen" << endl;
	cout << "3.  Add party" << endl;
	cout << "4.  Add citizen as party representative" << endl;
	cout << "5.  View all districts" << endl;
	cout << "6.  View all citizens" << endl;
	cout << "7.  View all parties" << endl;
	cout << "8.  Vote" << endl;
	cout << "9.  View election results " << endl;
	cout << "10. Exit" << endl;
	cout << "11. Save Elections To File" << endl;
	cout << "12. Load Elections From File" << endl;

	int res;
	cin >> res;
	return res;
}

void Election::electionTypeConsole()
{
	cout << "Choose an option: " << endl;
	cout << "1.  Normal elections" << endl;
	cout << "2.  Simple elections" << endl;
	int res;
	cin >> res;
	if (res != normalElections && res != simpleElections)
	{
		throw("Wrong input.");
		electionType = 0;
	}
	else
		electionType = res;
}

void Election::MainMenu()
{
	int choise = 0;
	while (true)
	{
		cout << endl << endl;
		choise = printMenu();
		if (choise == addDistrict)
			AddDistrict();
		else if (choise == addCitizen)
			AddCitizen();
		else if (choise == addParty)
			AddParty();
		else if (choise == addRep)
			AddRep();
		else if (choise == printDistricts)
			PrintDistricts();
		else if (choise == printCitizens)
			PrintCitizens();
		else if (choise == printParties)
			PrintParties();
		else if (choise == vote)
			Voting();
		else if (choise == printResults)
		{
			cout << "The Elections Results for " << date.GetDay() << "/";
			cout << date.GetMonth() << "/" << date.GetYear() << "  Are:" << endl << endl;
			showResult();
		}
		else if (choise == exitChoise)
			break;
		else if (choise == saveToFile)
 			savefile();
		else if (choise == loadFromFile)
			loadfile();
		else
			throw("Incorrect Option.");
	}
}


//save rep to file
void Election::saveRep(ostream& out)
{
	for (auto itr : dlist.getList())
	{
		int x = itr->getNumOfReps();
		out.write(rcastcc(&x), sizeof(x));
	}
}
 //save election to file
void Election::savefile()
{
	int countVotes = dlist.countAllVotes();

	cout << "Enter file name:" << endl;
	string name;
	cin >> name;
	char* nname = new char[name.length()];
	strcpy(nname, name.c_str());
	ofstream myfile(nname);
	date.saveDate(myfile);
	dlist.saveAllDis(myfile);
	clist.saveAllCitizens(myfile);
	plist.saveAllParties(myfile);
	clist.SaveAllVotes(myfile, countVotes);
	cout << endl << endl << "Elections Saved Successfully." << endl;
	myfile.close();
}

//load elections from file
void Election::loadfile()
{
	ifstream infile;
	cout << "Please enter the name of the file you would like to load:  (including file format)" << endl;
	string name;
	cin >> name;
	char* nname = new char[name.length()];
	strcpy(nname, name.c_str());
	infile.open(nname);
	int dcount, ccount, pcount, vcount, repcount, day, month, year;
	infile.read(rcastc(&day), sizeof(day));
	infile.read(rcastc(&month), sizeof(month));
	infile.read(rcastc(&year), sizeof(year));
	Date date;
	date.setDate(day, month, year);
	infile.read(rcastc(&dcount), sizeof(dcount));
	for (int i = 0; i < dcount; i++)
		LoadDistrict(infile);
	infile.read(rcastc(&ccount), sizeof(ccount));
	for (int i = 0; i < ccount; i++)
		LoadCitizen(infile, year);
	infile.read(rcastc(&pcount), sizeof(pcount));
	for (int i = 0; i < pcount; i++)
	{
		LoadParty(infile);
		infile.read(rcastc(&repcount), sizeof(repcount));
		for (int i = 0; i < repcount; i++)
			LoadRep(infile);
	}
	infile.read(rcastc(&vcount), sizeof(vcount));
	for (int i = 0; i < vcount; i++)
		LoadVote(infile);

	infile.close();
}
//init array
void Election::initPVotes(PVotes* arr, int size)
{
	for (int i = 0; i <= size; i++)
	{
		arr[i].serial = 0;
		arr[i].reps = 0;
		arr[i].votes = 0;
	}
}

//add district to dlist
void Election::AddDistrict()
{
	string name;
	int numOfRep, type;

	if(electionType == normalElections)
	{
		cout << "Enter name of district: " << endl;
		cin >> name;
		cout << "Enter the number of representatives in the district:" << endl;
		cin >> numOfRep;
		if (numOfRep < 0)
			throw("Negative number of representatives.");
		type = AskForDisType();
		createDistrict(name, numOfRep, type);
	}
}
//create new citizen
void Election::AddCitizen()
{
		string name;
		long int id;
		int born, dnum;
		cout << "Please Enter name and ID:" << endl;
		cin >> name >> id;
		cout << "Please enter Born year and District Number:" << endl;
		cin >> born;
		cin >> dnum;
	    CreateCitizen(name, id, born, dnum,date.GetYear());
	
}

//create new party
void Election::AddParty()
{
	string name;
	long int leaderId;
	cout << "Please Enter name for the party And id of the Candidate:" << endl;
	cin >> name >> leaderId;
	CreateParty(name, leaderId);
}

//create new rep
void Election::AddRep()
{
	long int idRep;
	int partyNum, disNum;
	cout << "Please enter representative ID number" << endl;
	cin >> idRep;
	cout << "Please enter Party number and his District Number" << endl;
	cin >> partyNum;
	cin >> disNum;
	CreateRep(idRep, partyNum, disNum);
}

//create new citizen and add it to the right district
void Election::CreateCitizen(string name, long int id, int born, int dnum,int year)
{

	if (electionType == simpleElections)
	{
		dnum = 1;
	}
	try {
		//find the right dis
		District* p = dlist.ReturnPointerToRightDis(dnum);
		//create new ciziten
		Citizen* tmp = clist.CreateCitizen(Person(name, id, born),dnum,p,year);
		if (p == nullptr || tmp ==nullptr)
			throw("Memmory allocation failed.");
		//add the new cizitien to clist
		clist.AddToCTail(tmp);
		//add the new citizen to the right dis
		dlist.AddCitToRightDis(tmp, dnum);
	}
	//catch errors
	catch (const char* msg) {
		cout << "Error: " << msg << endl;
		exit(1);
	}
	cout << endl << " Citizen " << name << " has been succesfully added." << endl;
}

//create new perty
void Election::CreateParty(string name, long int leaderId)
{
	try {
		Citizen* leader;
		Party* newParty = plist.CreateParty(name);
		if (newParty == nullptr)
		throw("Memmory allocation failed.");
		//find the leader by id
		leader = clist.findCitizen(leaderId);
		//inset the right leader
		newParty->SetLeader(leader);
		//add the party to plist
		plist.AddToTail(newParty);
		cout << "Party has been successfuly created." << endl;
		return;
	}
	//catch errors
	catch (const char* msg) {
		cout << "Error: " << msg << endl;
		exit(1);
	}
	throw(" Party Can not be created.");
}

//create new rep
void Election::CreateRep(long int idRep, int partyNum, int disNum)
{
	if (electionType == simpleElections)
		disNum = 1;
	Citizen* rep;
	//find the citizen according the rep id
	rep = clist.findCitizen(idRep);
	//set the right rep
	rep->setRepresentative(partyNum);
	//add rep to the  right party
	plist.AddRepToRightParty(rep, partyNum);
	//add rep to the right dis
	dlist.AddRepToRightDis(rep, disNum);
	cout << "Representative added successfully." << endl;

}

//create new district
void Election::createDistrict(string name, int reps, int type)
{
	if (type == simpleDistrict) //Normal
	{
		try {
			SimpleDis* newDistrict;
			newDistrict = dlist.CreateSimDistrict(District(name, reps, 1));
			dlist.AddToDTail(newDistrict);
		}
		//catch errors
		catch (const char* msg) {
			cout << "Error: " << msg << endl;
			exit(1);
		}
		cout << "District Successfully loaded." << endl;
	}
	else
	{
		try {
			//divided
			DivDis* newDistrict;
			newDistrict = dlist.CreateDivDistrict(District(name, reps, 2));
			dlist.AddToDTail(newDistrict);
		}
		//catch errors
		catch (const char* msg) {
			cout << "Error: " << msg << endl;
			exit(1);
		}
		cout << "District Successfully loaded." << endl;
	}
}

//receiving the dis type
int Election::AskForDisType()
{
	int res = 0;
	cout << "Which District would you like to have?" << endl;
	cout << "1. Normal District" << endl;
	cout << "2. Divided District" << endl;
	while (true)
	{
		cin >> res;
		if (res == simpleDistrict || res == divDistrict)
			return res;
		else
			throw("Wrong input");
	}
}

void Election::PrintDistricts()
{
	dlist.print();
}

void Election::PrintCitizens()
{
	cout << endl << "Citizen List:" << endl;
	clist.print();
}

void Election::PrintParties()
{
	plist.printList();
}

//receiving vote
void Election::Voting()
{
	if (plist.getCount() == 0)
	{
		cout << "There are no parties yet." << endl;
		return;
	}
	else
	{
		long int ID;
		int PNUM;
		cout << "Please Enter ID and Party Serial:" << endl;
		cin >> ID >> PNUM;
		CreateVote(ID, PNUM);
	}
}

//update vote
void Election::CreateVote(long int ID, int PNUM)

{
	try
	{
		Citizen* tmp;
		tmp = clist.findCitizen(ID);
		if (tmp->getChoice() != 0)
			throw("Citizen already Voted");
		else 
		{
			(tmp->setChoice(PNUM, plist.getCount()));
			District* p = dlist.findDisByNum(tmp->getDisNum());
			p->UpdateVotePeopleByone();
			cout << tmp->getName() << " voted successfully." << endl;

		}
	}
	catch (const char* msg)
	{
		cout << "Error: " << msg << endl;
	}
}

//create only one district
void Election::creatOneDis()
{
	int numRep;
	string name;
	name.append("The one");
	cout << "Enter the number of representatives in the district:" << endl;
	cin >> numRep;
	DivDis* newDistrict;
	newDistrict = dlist.CreateDivDistrict(District(name, numRep, 0));
	dlist.AddToDTail(newDistrict);
}


//load party from file
void Election::LoadParty(istream& in)
{
	string name;
	char* str;
	int serial, namelen;
	long int leaderId;
	in.read(rcastc(&namelen), sizeof(namelen));
	str = new char[namelen];
	in.read(rcastc(str), namelen);
	in.read(rcastc(&serial), sizeof(serial));
	in.read(rcastc(&leaderId), sizeof(leaderId));
	str[namelen -1] = '\0';
	name.append(str);
	CreateParty(name, leaderId);
}

//load district from file
void Election::LoadDistrict(istream& in)
{
	string name;
	char* str;
	int reps, type, namelen;

	in.read(rcastc(&namelen), sizeof(namelen));
	str = new char[namelen];
	in.read(rcastc(str), namelen);
	in.read(rcastc(&reps), sizeof(reps));
	in.read(rcastc(&type), sizeof(type));
	str[namelen] = '\0';
	name.append(str);

	createDistrict(name, reps, type); 
}

void Election::LoadCitizen(istream& in,int year)
{
	string name;
	char* str;
	long int id;
	int birth, dnum, namelen;

	in.read(rcastc(&namelen), sizeof(namelen));
	str = new char[namelen];
	in.read(rcastc(str), namelen);
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&birth), sizeof(birth));
	in.read(rcastc(&dnum), sizeof(dnum));
	str[namelen] = '\0';
	name.append(str);
	CreateCitizen(name, id, birth, dnum,year);

}

void Election::LoadRep(istream& in)
{
	long int id;
	int partyNum, disNum;
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&partyNum), sizeof(partyNum));
	in.read(rcastc(&disNum), sizeof(disNum));
	CreateRep(id, partyNum, disNum);
}

void Election::LoadVote(istream& in)
{
	long int id;
	int partyNum;
	in.read(rcastc(&id), sizeof(id));
	in.read(rcastc(&partyNum), sizeof(partyNum));
	CreateVote(id, partyNum);


}


void Election::showResult()
{
	if (dlist.getCount() == 0 || plist.getCount() == 0)
		throw("Results unavailable yet.\nTry Adding some district/party.");
	for (auto itr : dlist.getList())
	{
		itr->collectVotesHelper(plist.getCount());
		itr->printResults(plist.getList());
	}
	int parrSize = plist.getCount();
	DynamicArray<PVotes> parr(parrSize + 1, 0);
	int f;
	for (auto itr : dlist.getList())
	{
		for (f = 1; f <= parrSize; f++)  //For Every District Collecting votes for each party
		{
			parr[f].serial = f;
			parr[f].votes += itr->getVotesCell(f);
			parr[f].reps += itr->getRepsCell(f);
		}
	}
	mergeSort(parr, 1, parrSize);
	cout << "--Top Party Candidates:--" << endl << "--------------------------" << endl;
	for (f = 1; f <= parrSize; f++)
	{
		plist.printPartyAndLeaderNamebySerial(parr[f].serial);
		cout << " Representatives:\t" << parr[f].reps << "\tVotes: " << parr[f].votes << endl;
	}

}



void Election::mergeSort(DynamicArray<PVotes>& arr, int l, int r) {

	if (l < r) {
		int m = l + (r - 1) / 2;
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}

void Election::merge(DynamicArray<PVotes>& arr, int l, int m, int r)
{
	int n1, n2;
	n1 = m - l + 1;
	n2 = r - m;
	//Create temp arrays;
	DynamicArray<PVotes> L(n1);
	DynamicArray<PVotes> R(n2);

	/*DynamicArray<PVotes>* L= new DynamicArray<PVotes>(n1);
	DynamicArray<PVotes>* R = new DynamicArray<PVotes>(n2);*/
	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];
	// Merge the temp arrays back into arr[l..r]
	int i = 0, j = 0, k = l;

	while (i < n1 && j < n2) {
		if (L.returnidx(i).reps >= R.returnidx(j).reps) {
			arr[k].reps = L[i].reps;
			arr[k].votes = L[i].votes;
			arr[k].serial = L[i].serial;
			i++;
		}
		else {
			arr[k].reps = R[j].reps;
			arr[k].votes = R[j].votes;
			arr[k].serial = R[j].serial;
			j++;
		}
		k++;
	}
	// Copy the remaining elements of
	 //L[], if there are any
	while (i < n1) {
		arr[k].reps = L[i].reps;
		arr[k].votes = L[i].votes;
		arr[k].serial = L[i].serial;
		i++;
		k++;
	}
	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k].reps = R[j].reps;
		arr[k].votes = R[j].votes;
		arr[k].serial = R[j].serial;
		j++;
		k++;
	}

}
// template function to perform merge sort on array, arr
