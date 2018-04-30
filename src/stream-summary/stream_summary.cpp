#include "stream_summary.hpp"
#include <iostream>

using namespace std;

void Bucket::increment() {
	_count++;
}

unsigned int Bucket::value() {
	return _counter->getCount();
}

unsigned int Counter::getCount() {
	return _count;
}

void StreamSummary::offer(const string& s) {
	auto v = _counter_map.find(s);
	if ( v == _counter_map.end() ) {
		// new element
		shared_ptr<Counter> shared = make_shared<Counter>(1);
		_counter_map.insert(make_pair(s, Bucket(s, shared)));
	} else {
		// existing element
		v->second.increment();
	}
}

int StreamSummary::getCountersCount() {
	return _counter_map.size();
}

vector<Bucket> StreamSummary::getTop() {
}

int StreamSummary::estimateCount(const std::string& s) {
	auto v = _counter_map.find(s);
	if ( v == _counter_map.end() ) {
		return -1;
	}
	return v->second.value();
}

vector<pair<string, unsigned int>> StreamSummary::top() {
	auto it = _counter_map.begin();
	vector<pair<string, unsigned int>> result;
	for (; it != _counter_map.end(); it++) {
		result.push_back(make_pair(it->first, it->second.value()));
	}
	return result;
}
