#pragma once
#include "date.h"
#include <string>
#include <memory>
using namespace std;

enum class Comparison
{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation
{
	Or,
	And
};

class Node
{
public:
	virtual bool Evaluate(const Date& d, const string& ev) = 0;
};

class EmptyNode : public Node
{
public:
	bool Evaluate(const Date& d, const string& ev) override;
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(Comparison cmp, Date dt) : comp(cmp), date(dt) {}
	bool Evaluate(const Date& d, const string& ev) override;
private:
	const Date date;
	Comparison comp;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(Comparison cmp, string value) : comp(cmp), event(value) {}
	bool Evaluate(const Date& d, const string& ev) override;
private:
	const string event;
	Comparison comp;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(LogicalOperation op, shared_ptr<Node> lft, shared_ptr<Node> rght) :oper(op), left(lft), right(rght) {}
	bool Evaluate(const Date& date, const string& event) override;
private:
	LogicalOperation oper;
	shared_ptr<Node> left;
	shared_ptr<Node> right;
};