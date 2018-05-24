#include <string>
#include <vector>
#include <map>
#include <list>

class Bucket;

class Counter {
	private:
		unsigned int _count;
		const std::list<Bucket> _buckets;

	public:
		Counter(unsigned int count) : _count(count), _buckets({}) {}
		unsigned int getCount();
};

class Bucket {
private:
	std::string _value;
	unsigned int _count;
	unsigned int _error;
	const std::shared_ptr<Counter> _counter;

public:
	Bucket(const std::string& value, const std::shared_ptr<Counter> counter) : _value(value), _counter(counter) {}

	void increment();
	unsigned int value();
};

typedef std::map<std::string, Bucket> ValueMap;

class StreamSummary {
private:
	int _countersNo;
	ValueMap _counter_map;

public:
	StreamSummary(int countersNo) : _countersNo(countersNo) {}
	StreamSummary() : StreamSummary(500) {}

	void offer(const std::string& s);
	std::vector<Bucket> getTop();

	int estimateCount(const std::string& s);

	/**
	 * Возвращает отсортированный по убыванию частоты список позиций
	 */
	std::vector<std::pair<std::string, unsigned int>> top();

	/**
	 * Возвращает количество отслеживаемых позиций в потоке
	 */
	int getCountersCount();
};
