#pragma once
using namespace std;
#include "CitizenList.h"
#include "Date.h"
#include "DistrictList.h"
#include "PartyList.h"
#include "SimpleDis.h"
//#include "DynamicArray.h"

struct PVotes {
	int serial;
	int votes;
	int reps;
};

class Election
{
private:
	DistrictList dlist;
	PartyList plist;
	CitizenList clist;
	Date date;
	int electionType;

public:

	void AddDistrict();
	void AddCitizen();
	void AddParty();
	void AddRep();

	void CreateCitizen(string name, long int id, int born, int dnum,int year);
	void createDistrict(string name, int reps, int type);
	void CreateParty(string name, long int leaderId);
	void CreateRep(long int idRep, int partyNum, int disNum);
	void CreateVote(long int ID, int PNUM);
	void CheckIDAndAge(string id, int year)const;
	


	int AskForDisType();
	void PrintDistricts();
	void PrintCitizens();
	void PrintParties();

	void printPreMenu();
	int printMenu();
	void electionTypeConsole();
	void MainMenu();
	void Voting();
	void showResult();
	void creatOneDis();
	void initPVotes(PVotes* arr, int size);

	void mergeSort(DynamicArray<PVotes>& arr, int l, int r);
	void merge(DynamicArray<PVotes>&arr, int l, int m, int r);

	void loadfile();
	void LoadParty(istream& in);
	void LoadDistrict(istream& in);
	void LoadCitizen(istream& in,int year);
	void LoadRep(istream& in);
	void LoadVote(istream& in);
	void saveRep(ostream& out);

	void savefile();

};