#pragma once
#include <string>
#include <iostream>
using namespace std;

enum ID {IDLen = 9};
class Person
{
protected:
	string name;
	long int id;
	int yearOfBirth;

public:
	Person();
	Person(const Person& per);
	Person(string n, long int id, int year);
	~Person() = default;

	//getters
	void CheckID();
	const string getName(){ return name; }
	string getName() const  { return name; }
	long int getId() const { return id; }
	int getYearOfBirth() const { return yearOfBirth; }

};


