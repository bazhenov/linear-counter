#include "stream_summary.hpp"

using namespace std;

int Counter::getCount() {
	return count;
}

void Counter::increment() {
	count++;
}

void StreamSummary::offer(const string& s) {
	auto v = _counter_map.find(s);
	if ( v == _counter_map.end() ) {
		_counter_map.insert(make_pair(s, Counter(s)));
	} else {
		v->second.increment();
	}
}

int StreamSummary::getCountersCount() {
	return _counter_map.size();
}

vector<Counter> StreamSummary::getTop() {
}

int StreamSummary::estimateCount(const std::string& s) {
	auto v = _counter_map.find(s);
	if ( v == _counter_map.end() ) {
		return -1;
	}
	return v->second.getCount();
}

vector<pair<string, int>> StreamSummary::top() {
	auto it = _counter_map.begin();
	vector<pair<string, int>> result;
	for (; it != _counter_map.end(); it++) {
		result.push_back(make_pair(it->first, it->second.getCount()));
	}
	return result;
}
