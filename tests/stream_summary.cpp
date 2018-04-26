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
	EXPECT_EQ("first", top[0].first);
	EXPECT_EQ(3, top[0].second);

	EXPECT_EQ("second", top[1].first);
	EXPECT_EQ(2, top[1].second);
}

TEST(StreamSummary, frequency) {
	StreamSummary s;
	s.offer("first");
	EXPECT_EQ(s.estimateCount("first"), 1);

	s.offer("first");
	EXPECT_EQ(s.estimateCount("first"), 2);
}
