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
	return vector<pair<string, int>>();
}
