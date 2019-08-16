#include "date.h"
#include <iostream>
#include <tuple>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

inline int Date::GetYear() const
{
	return year;
}
inline int Date::GetMonth() const
{
	return month;
}
inline int Date::GetDay() const
{
	return day;
}

bool Date::operator==(const Date& other) const
{
	return tie(this->year, this->month, this->day) == tie(other.year, other.month, other.day);
}

bool Date::operator!=(const Date& other) const
{
	return !(*this == other);
}

bool Date::operator<(const Date& other) const
{
	return tie(this->year, this->month, this->day) < tie(other.year, other.month, other.day);
}

bool Date::operator>(const Date& other) const
{
	return tie(this->year, this->month, this->day) > tie(other.year, other.month, other.day);
}

bool Date::operator>=(const Date& other) const
{
	return !(*this < other);
}

bool Date::operator<=(const Date& other) const
{
	return !(*this > other);
}

ostream& operator<<(ostream& stream, const Date& date)
{
	stream << setfill('0');
	stream << setw(4) << date.GetYear() << '-' << setw(2) << date.GetMonth() << '-' << setw(2) << date.GetDay();
	return stream;
}

Date ParseDate(istream& is)
{
	string y, m, d;
	getline(is, y, '-');
	getline(is, m, '-');
	getline(is, d, ' ');
	return { stoi(y), stoi(m), stoi(d) };
}