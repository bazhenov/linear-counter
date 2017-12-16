#include <gtest/gtest.h>
#include "stream_summary.hpp"

using namespace std;

TEST(StreamSummary, shouldReturnCountersCount) {
	StreamSummary summary;
	summary.offer("first");
	summary.offer("second");

	ASSERT_EQ(2, summary.getCountersCount());
}

TEST(StreamSummary, shouldBeAbleToTrackCounts) {
	StreamSummary summary;

	string s = "example string";
	for (int i=0; i<5; i++)
		summary.offer(s);

	ASSERT_EQ(5, summary.estimateCount(s));
}

TEST(StreamSummary, shouldBeAbleToReturnValuesInFrequencyDecreasingOrder) {
	StreamSummary s;
	s.offer("first");
	s.offer("first");
	s.offer("second");
	s.offer("second");
	s.offer("first");

	auto top = s.top();
	EXPECT_EQ(2, top.size());
}
