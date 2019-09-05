#include "search_server.h"
#include "iterator_range.h"
#include "parse.h"
//#include "C:\Maxim\Visual Studio\Projects\YandexCourse\YandexCourse\Resources\profile.h"
#include "profile.h"
#include <algorithm>
#include <iterator>
#include <sstream>
#include <deque>
#include <iostream>

vector<string> SplitIntoWords(const string& line) {
	istringstream words_input(line);
	return {istream_iterator<string>(words_input), istream_iterator<string>()};
}

InvertedIndex::InvertedIndex(istream &document_input) {
	for (string current_document; getline(document_input, current_document);) {
		docs.push_back(move(current_document));
		size_t docid = docs.size() - 1;
		for (string_view word : SplitIntoWordsView(docs.back())) {
			auto &docids = index[word];
			if (!docids.empty() && docids.back().docid == docid) {
				++docids.back().hitcount;
			}
			else {
				docids.push_back({ docid, 1 });
			}
		}
	}
}

void SearchServer::UpdateDocumentBase(istream& document_input) {
	InvertedIndex new_index(document_input);
	index = move(new_index);
}

void SearchServer::AddQueriesStream(
  istream& query_input, ostream& search_results_output
) {
	LOG_DURATION("Query time");
	vector<size_t> docid_count(index.index_size());
	for (string current_query; getline(query_input, current_query); ) {
		fill(docid_count.begin(), docid_count.end(), 0);
		const auto words = SplitIntoWordsView(current_query);

		for (const auto &word : words) {
			for (const auto&[docid, hit_count] : index.Lookup(word)) {
				docid_count[docid] += hit_count;
			}
		}

		vector<pair<size_t, size_t>> search_results;
		for (size_t i = 0; i < docid_count.size(); ++i)
			if (docid_count[i] != 0)
				search_results.push_back({ i, docid_count[i] });

		partial_sort(
			begin(search_results),
			begin(search_results) + min<size_t>(5, search_results.size()),
			end(search_results),
			[](pair<size_t, size_t> lhs, pair<size_t, size_t> rhs) 
				{
					int64_t lhs_docid = lhs.first;
					auto lhs_hit_count = lhs.second;
					int64_t rhs_docid = rhs.first;
					auto rhs_hit_count = rhs.second;
					return make_pair(lhs_hit_count, -lhs_docid) > make_pair(rhs_hit_count, -rhs_docid);
				});

		search_results_output << current_query << ':';
		for (auto [docid, hitcount] : Head(search_results, 5)) {
			search_results_output << " {"
			<< "docid: " << docid << ", "
			<< "hitcount: " << hitcount << '}';
		}
		search_results_output << endl;
	}
}

const vector<InvertedIndex::Entry>& InvertedIndex::Lookup(const string_view word) const 
{
	static const vector<Entry> empty;
	if (auto it = index.find(word); it != index.end()) {
		return it->second;
	}
	else {
		return empty;
	}
}



