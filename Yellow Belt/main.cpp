#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
//#include "test_runner.h"
//#include "C:\Maxim\Visual Studio\Projects\Testing framework\TestRunner.h"

#include <iostream>
#include <stdexcept>
#include <memory>

using namespace std;

string ParseEvent(istream& is) {
	string ev;
	while (is.peek() == ' ')
		is.ignore(1);
	getline(is, ev);
	return ev;
}

//void TestDatabase() {
//	istringstream empty_is("");
//	auto empty_condition = ParseCondition(empty_is);
//	auto empty_predicate = [empty_condition](const Date& date, const string& event) {
//		return empty_condition->Evaluate(date, event);
//	};
//
//	// Add 2 - Del 1 - Add deleted again
//	{
//		Database db;
//		Date d(2019, 1, 1);
//		db.Add(d, "e1");
//		db.Add(d, "e2");
//		istringstream is(R"(event == "e1")");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.RemoveIf(predicate), 1, "Db Add2-Del-Add 1");
//		db.Add(d, "e1");
//		AssertEqual(db.FindIf(empty_predicate).size(), 2, "Db Add2-Del-Add 2");
//	}
//
//	// Add
//	{
//		Database db;
//		Date d(2019, 1, 1);
//		db.Add(d, "e1");
//		db.Add(d, "e1");
//		istringstream is("date == 2019-01-01");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.FindIf(predicate).size(), 1, "Db Add Duplicates 1");
//	}
//
//	// Last
//	{
//		Database db;
//		Date d(2019, 1, 1);
//		Date d1(2019, 1, 2);
//		Date d2(2018, 12, 22);
//		db.Add(d1, "e1");
//		db.Add(d2, "e2");
//
//		AssertEqual(db.Last(d), "2018-12-22 e2", "Db Last 1");
//		Date d3(2018, 12, 24);
//		db.Add(d3, "e3");
//		AssertEqual(db.Last(d), "2018-12-24 e3", "Db Last 2");
//
//		// Get last event for date before first event 
//		try {
//			Date d4(2017, 2, 2);
//			db.Last(d4);
//			Assert(false, "Db Last 3");
//		}
//		catch (invalid_argument e) {
//			// Pass
//		}
//		 //Delete event and get last
//		istringstream is2("date == 2018-12-24");
//		auto condition = ParseCondition(is2);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		db.RemoveIf(predicate);
//		AssertEqual(db.Last(d), "2018-12-22 e2", "Db Last 4");
//
//		AssertEqual(db.Last(d1), "2019-01-02 e1", "Db Last 5");
//		db.Add(d2, "e4");
//		AssertEqual(db.Last(d2), "2018-12-22 e4", "Db Last 6");
//	}
//
//	// Del
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		istringstream is("date == 2018-01-07");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.RemoveIf(predicate), 2, "Db Del 1");
//	}
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.RemoveIf(predicate), 4, "Db Del 2");
//	}
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		AssertEqual(db.RemoveIf(empty_predicate), 4, "Db Del 3");
//	}
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		istringstream is(R"(event == "e1")");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.RemoveIf(predicate), 1, "Db Del 4");
//	}
//
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		istringstream is(R"(event == "e1" OR date == 2019-01-01)");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.RemoveIf(predicate), 2, "Db Del 5");
//	}
//
//	// Find
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		istringstream is("date == 2018-01-07");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.FindIf(predicate).size(), 2, "Db Find 1");
//	}
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.FindIf(predicate).size(), 4, "Db Find 2");
//	}
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		AssertEqual(db.FindIf(empty_predicate).size(), 4, "Db Find 3");
//	}
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		istringstream is(R"(event == "e1")");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.FindIf(predicate).size(), 1, "Db Find 4");
//	}
//
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		db.Add({ 2018, 1, 7 }, "e3");
//		db.Add({ 2018, 1, 7 }, "e4");
//		istringstream is(R"(event == "e1" OR date == 2019-01-01)");
//		auto condition = ParseCondition(is);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.FindIf(predicate).size(), 2, "Db Find 5");
//	}
//
//	// Add - Del - Add - Del
//	{
//		Database db;
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");
//
//		db.Add({ 2019, 1, 1 }, "e1");
//		db.Add({ 2019, 1, 1 }, "e2");
//		AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");
//	}
//}
//void TestAll() {
//	TestRunner tr;
//	tr.RunTest(TestDatabase, "TestDatabase");
//}


int main() {
	//TestAll();

	Database db;

	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "Add") {
			const auto date = ParseDate(is);
			const auto event = ParseEvent(is);
			db.Add(date, event);
		}
		else if (command == "Print") {
			db.Print(cout);
		}
		else if (command == "Del") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};
			int count = db.RemoveIf(predicate);
			cout << "Removed " << count << " entries" << endl;
		}
		else if (command == "Find") {
			auto condition = ParseCondition(is);
			auto predicate = [condition](const Date& date, const string& event) {
				return condition->Evaluate(date, event);
			};

			const auto entries = db.FindIf(predicate);
			for (const auto& entry : entries) {
				cout << entry << endl;
			}
			cout << "Found " << entries.size() << " entries" << endl;
		}
		else if (command == "Last") {
			try {
				cout << db.Last(ParseDate(is)) << endl;
			}
			catch (invalid_argument&) {
				cout << "No entries" << endl;
			}
		}
		else if (command.empty()) {
			continue;
		}
		else {
			throw logic_error("Unknown command: " + command);
		}
	}

	return 0;
}

//void TestParseEvent() {
//	{
//		istringstream is("event");
//		AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
//	}
//	{
//		istringstream is("   sport event ");
//		AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
//	}
//	{
//		istringstream is("  first event  \n  second event");
//		vector<string> events;
//		events.push_back(ParseEvent(is));
//		events.push_back(ParseEvent(is));
//		AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
//	}
//}
//
//void TestDelete()
//{
//	{
//		Database db;
//		istringstream is("2017-06-01 1st of June");
//		auto date = ParseDate(is);
//		auto event = ParseEvent(is);
//		db.Add(date, event);
//		istringstream is1("2017-07-08 8th of July");
//		date = ParseDate(is1);
//		event = ParseEvent(is1);
//		db.Add(date, event);
//		istringstream is2("2017-07-08 Someone's birthday");
//		date = ParseDate(is2);
//		event = ParseEvent(is2);
//		db.Add(date, event);
//		istringstream is3("date == 2017-07-08");
//		auto condition = ParseCondition(is3);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		AssertEqual(db.RemoveIf(predicate), 2);
//	}
//}
//
//void TestCleanUp()
//{
//	{
//		Database db;
//		istringstream is("2017-06-01 1st of June");
//		auto date = ParseDate(is);
//		auto event = ParseEvent(is);
//		db.Add(date, event);
//		istringstream is1("2017-07-08 8th of July");
//		date = ParseDate(is1);
//		event = ParseEvent(is1);
//		db.Add(date, event);
//		istringstream is2("2017-07-08 Someone's birthday");
//		date = ParseDate(is2);
//		event = ParseEvent(is2);
//		db.Add(date, event);
//		istringstream is3("");
//		auto condition = ParseCondition(is3);
//		auto predicate = [condition](const Date& date, const string& event) {
//			return condition->Evaluate(date, event);
//		};
//		db.RemoveIf(predicate);
//		db.CleanUp();
//	}
//}
//
//void TestAll() {
//	TestRunner tr;
//	tr.RunTest(TestParseEvent, "TestParseEvent");
//	tr.RunTest(TestParseCondition, "TestParseCondition");
//	tr.RunTest(TestDelete, "TestDelete");
//	tr.RunTest(TestCleanUp, "TestCleanUp");
//}