#pragma once
#include "Citizen.h"
#include <string>
#include <fstream>

class Date
{
private:
	static const int DAYS_IN_MONTH[12];
	int day;
	int month;
	int year;
public:
	Date() : day(0), month(0), year(0) { ; }
	~Date(){}
	static int daysInMonth(int month);
	void setDate(int day, int month, int year);
	void SetDay(int d) { day = d; }
	void SetMonth(int m) { month = m; }
	void SetYear(int y) { year = y; }
	void saveDate(ostream& out) const;
	int GetDay()   const { return day; }
	int GetMonth() const { return month; }
	int GetYear()  const { return year; }
	Date& ElecDate();
};


