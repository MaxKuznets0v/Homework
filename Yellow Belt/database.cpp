#include "database.h"
#include "date.h"
#include <string>

void Database::Add(const Date& date, const string& event)
{
	if (!(EventBase.count(date) && EventBase.at(date).count(event)))
	{
		DateBase[date].push_back(event);
		EventBase[date].insert(event);
	}
}

void Database::Print(ostream& os) const
{
	for (const auto& item : DateBase)
		for (const auto& elem : DateBase.at(item.first))
			os << item.first << " " << elem << endl;
}
string Database::Last(const Date& date) const
{
	if (DateBase.empty())
		throw invalid_argument("");
	ostringstream os;
	auto lastDate = DateBase.lower_bound(date);
	if (lastDate != DateBase.begin() && lastDate->first != date)
		--lastDate;
	if (lastDate->first <= date)
	{
		os << lastDate->first;
		return os.str() + " " + lastDate->second.back();
	}
	throw invalid_argument("");
}


ostream& operator<<(ostream& os, pair<Date, string> p)
{
	os << p.first << " " << p.second;
	return os;
}

void Database::CleanUp()
{
	map<Date, vector<string>> tmp = DateBase;
	for (auto it = DateBase.rbegin(); it != DateBase.rend(); ++it)
	{
		if (EventBase[it->first].size() == 0)
			EventBase.erase(it->first);
		if (DateBase[it->first].empty())
			tmp.erase(it->first);
	}
	DateBase = tmp;
}