#pragma once

#include <istream>
#include <ostream>
#include <set>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <deque>
using namespace std;

class InvertedIndex {
public:
	struct Entry
	{
		size_t docid, hitcount;
	};
	InvertedIndex() = default;
	explicit InvertedIndex(istream& document_input);
	const vector<Entry>& Lookup(const string_view word) const;

	const deque<string>& GetDocument(size_t id) const {
		return docs;
	}
	size_t index_size()
	{
		return docs.size();
	}

private:
	deque<string> docs;
	map<string_view, vector<Entry>> index;
};

class SearchServer {
public:
  SearchServer() = default;
  explicit SearchServer(istream& document_input)
	  : index(InvertedIndex(document_input))
  {
  }
  void UpdateDocumentBase(istream& document_input);
  void AddQueriesStream(istream& query_input, ostream& search_results_output);

private:
  InvertedIndex index;
};
