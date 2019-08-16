#pragma once
#include "date.h"
#include <set>
#include <map>
#include <vector>
#include <algorithm>

class Database
{
public:
	void Add(const Date& date, const string& event);
	void Print(ostream& os) const;

	template<typename T>
	int RemoveIf(T predicate)
	{
		int count = 0;
		for (auto& ev : DateBase)
		{
			auto partition = stable_partition(ev.second.begin(), ev.second.end(), [ev, predicate](string& str)
			{
				return !predicate(ev.first, str);
			});
			int deleted = distance(partition, ev.second.end());
			if (deleted > 0)
			{
				vector<string> temp = ev.second;
				auto it = --ev.second.end();
				for (it; it > partition;)
				{
					EventBase[ev.first].erase(*it);
					if (it != ev.second.begin())
						--it;
					else
					{
						temp.pop_back();
						break;
					}
					temp.pop_back();
				}
				if (it == partition)
				{
					EventBase[ev.first].erase(*it);
					temp.pop_back();
				}
				ev.second = temp;
				count += deleted;
			}
		}
		CleanUp();
		return count;
	}

	template<typename T>
	vector<pair<Date, string>> FindIf(T predicate) const
	{
		vector<pair<Date, string>> res;
		for (auto& ev : DateBase)
		{
			for (auto& str : ev.second)
			{
				if (predicate(ev.first, str))
					res.push_back({ ev.first, str });
			}
		}
		return res;
	}
	string Last(const Date& date) const;
	void CleanUp();
private:
	map<Date, vector<string>> DateBase;
	map<Date, set<string>> EventBase;
};

ostream& operator<<(ostream& os, pair<Date, string> p);