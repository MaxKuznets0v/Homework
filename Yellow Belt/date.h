#pragma once
#include <iostream>
#include <sstream>
using namespace std;

class Date
{
	int year,
		month,
		day;
public:
	Date(int y, int m, int d) : year(y), month(m), day(d) {}
	inline int GetYear() const;
	inline int GetMonth() const;
	inline int GetDay() const;
	friend ostream& operator<<(ostream& stream, const Date& date);
	bool operator==(const Date& other) const;
	bool operator!=(const Date& other) const;
	bool operator<(const Date& other) const;
	bool operator>=(const Date& other) const;
	bool operator>(const Date& other) const;
	bool operator<=(const Date& other) const;
};

ostream& operator<<(ostream& stream, const Date& date);

Date ParseDate(istream& is);