#include <string>
#include <vector>
#include <map>

class Counter {
	private:
		std::string str;
		int count;

	public:
		Counter(const std::string& v) : str(v), count(1) {}
		int getCount();
		void increment();
};

typedef std::map<std::string, Counter> CounterMap;

class StreamSummary {
	private:
		int _countersNo;
		CounterMap _counter_map;

	public:
		StreamSummary(int countersNo) : _countersNo(countersNo) {}
		StreamSummary() : StreamSummary(500) {}

		void offer(const std::string& s);
		std::vector<Counter> getTop();

		int estimateCount(const std::string& s);
		
		/**
		 * Возвращает отсортированный по убыванию частоты список позиций
		 */
		std::vector<std::pair<std::string, int>> top();

		/**
		 * Возвращает количество отслеживаемых позиций в потоке
		 */
		int getCountersCount();
};
