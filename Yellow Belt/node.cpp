#include "node.h"
#include "date.h"
#include <string>
using namespace std;

bool EmptyNode::Evaluate(const Date& d, const string& ev)
{
	return true; 
}

bool DateComparisonNode::Evaluate(const Date& d, const string& ev)
{
	switch (comp)
	{
	case Comparison::Equal:
		return d == date;
	case Comparison::Greater:
		return d > date;
	case Comparison::GreaterOrEqual:
		return d >= date;
	case Comparison::Less:
		return d < date;
	case Comparison::LessOrEqual:
		return d <= date;
	case Comparison::NotEqual:
		return d != date;
	default:
		return false;
	}
}

bool EventComparisonNode::Evaluate(const Date& d, const string& ev)
{
	switch (comp)
	{
	case Comparison::Equal:
		return event == ev;
	case Comparison::Greater:
		return ev > event;
	case Comparison::GreaterOrEqual:
		return ev >= event;
	case Comparison::Less:
		return ev < event;
	case Comparison::LessOrEqual:
		return ev <= event;
	case Comparison::NotEqual:
		return ev != event;
	default:
		return false;
	}
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event)
{
	return oper == LogicalOperation::And ? left->Evaluate(date, event) && right->Evaluate(date, event) :
		left->Evaluate(date, event) || right->Evaluate(date, event);
}