#include <iostream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
using namespace std;

class Date
{
	int year;
	int month;
	int day;
	int ValidDatePart(int ind, const string& date) const
	{
		string temp;
		for (ind; ind < date.size(); ++ind)
		{
			if (date[ind] == '-' || date[ind] == '+' || date[ind] >= '0' && date[ind] <= '9')
			{
				if ((date[ind] == '-' || date[ind] == '+') && !temp.empty())
					break;
				temp += date[ind];
			}
			else
				return -1;
		}
		return ind;
	}

	bool isValidDate(const string& date) const
	{
		int i = 0;
		i = ValidDatePart(i, date) + 1;
		if (i - 1 == -1)
			return false;
		if (i >= date.size())
			return false;
		i = ValidDatePart(i, date) + 1;
		if (i - 1 == -1)
			return false;
		if (i >= date.size())
			return false;
		i = ValidDatePart(i, date);
		if (i == -1)
			return false;
		return i == date.size();
	}

	int ValidNumberPart(int& ind, const string& date) const
	{
		string temp;
		for (ind; ind < date.size(); ++ind)
		{
			if ((date[ind] == '-' || date[ind] == '+') && !temp.empty())
				break;
			temp += date[ind];
		}
		return stoi(temp);
	}

public:
	explicit Date(string date)
	{
		if (!isValidDate(date))
			throw invalid_argument("Wrong date format: " + date);
		else
		{
			int i = 0;
			int y = ValidNumberPart(i, date);
			++i;
			int m = ValidNumberPart(i, date);
			if (m < 1 || m > 12)
				throw invalid_argument("Month value is invalid: " + to_string(m));
			++i;
			int d = ValidNumberPart(i, date);
			if (d < 1 || d > 31)
				throw invalid_argument("Day value is invalid: " + to_string(d));
			year = y;
			month = m;
			day = d;
		}

	}
	inline int GetYear() const
	{
		return year;
	}
	inline int GetMonth() const
	{
		return month;
	}
	inline int GetDay() const
	{
		return day;
	}
	friend ostream& operator<<(ostream& stream, const Date& obj);
};

ostream& operator<<(ostream& stream, const Date& obj)
{
	stream << setfill('0');
	stream << setw(4) << obj.year << '-' << setw(2) << obj.month << '-' << setw(2) << obj.day;
	return stream;
}

bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.GetYear() < rhs.GetYear())
		return true;
	else if (lhs.GetYear() == rhs.GetYear())
	{
		if (lhs.GetMonth() < rhs.GetMonth())
			return true;
		else if (lhs.GetMonth() == rhs.GetMonth())
			return lhs.GetDay() < rhs.GetDay();
	}
	return false;
}

class Database
{
	map<Date, set<string>> base;
public:
	void AddEvent(const Date& date, const string& event)
	{
		base[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event)
	{
		if (base[date].count(event) != 0)
		{
			base[date].erase(event);
			cout << "Deleted successfully\n";
			return true;
		}
		else
		{
			cout << "Event not found\n";
			return false;
		}
	}
	int DeleteDate(const Date& date)
	{
		int n = base[date].size();
		cout << "Deleted " << n << " events\n";
		base.erase(date);
		return n;
	}

	void Find(const Date& date) const
	{
		if (base.count(date) != 0)
			for (const auto& item : base.at(date))
				cout << item << endl;
	}

	void Print() const
	{
		for (const auto& item : base)
			for (const auto& elem : base.at(item.first))
				cout << item.first << " " << elem << endl;
	}

	string GetWord(string& str) const
	{
		string res;
		bool done = false;
		for (int i = 0; i < str.size(); ++i)
			if (str[i] != ' ')
				res += str[i];
			else
			{
				str.erase(str.begin(), str.begin() + i + 1);
				done = true;
				break;
			}
		if (!done)
			str = "";
		return res;
	}

	bool isValidCommand(string& cmd) const
	{
		return cmd == "Add" || cmd == "Find" || cmd == "Print" || cmd == "Del";
	}

	void MakeAction(const string& cmd, string& other)
	{
		if (cmd == "Print")
			Print();
		else
		{
			try
			{
				Date date(GetWord(other));
				if (cmd == "Add")
					AddEvent(date, GetWord(other));
				else if (cmd == "Del")
				{
					if (other.empty())
						DeleteDate(date);
					else
						DeleteEvent(date, GetWord(other));
				}
				else
					Find(date);
			}
			catch (invalid_argument& ex)
			{
				cout << ex.what() << endl;
			}
		}
	}

};

int main() {
	Database db;

	string command;
	while (getline(cin, command))
	{
		if (command == "")
			continue;
		string cmd = db.GetWord(command);
		if (!db.isValidCommand(cmd))
		{
			cout << "Unknown command: " << cmd << endl;
			continue;
		}
		db.MakeAction(cmd, command);
	}

	return 0;
}