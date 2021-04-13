#include "Date.h"
#include <iostream>
#include <string>
#include <fstream>
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

const int Date::DAYS_IN_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

int Date::daysInMonth(int month)
{
	if ((month < 1) || (month > 12))
		return -1;
	return DAYS_IN_MONTH[month - 1];
}

void Date::setDate(int day, int month, int year)
{
	if ((year <= 1899) || (year >= 2100)) {
		throw(" Wrong year input.");

	}
	this->year = year;

	if ((month <= 0) || (month >= 13)) {
		throw(" Wrong month input.");
	}
	this->month = month;


	if ((day <= 0) || (day > daysInMonth(month)))
	{
		throw(" Wrong day input.");
	}
	this->day = day;


}

void Date::saveDate(ostream& out) const
{
	int dday, mmonth, yyear;
	dday = GetDay();
	mmonth = GetMonth();
	yyear = GetYear();

	out.write(rcastc(&dday), sizeof(dday));
	out.write(rcastc(&mmonth), sizeof(mmonth));
	out.write(rcastc(&yyear), sizeof(yyear));
}

Date& Date::ElecDate()
{
	Date date;
	cout << "Please Provide us the date of the elections:( with spaces)" << endl;
	int d, m, y;
	cin >> d >> m >> y;
	try { (date.setDate(d, m, y)); }
	catch (const char* msg)
	{
		cout << "Error: " << msg << endl;
		exit(1);
	}
	return date;
}
