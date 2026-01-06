#include "TimeTrack.hpp"

TimeTrack::~TimeTrack() {
	auto end = getTimeStamp();
	auto total = end - t;

	printf("total : %s ", std::to_string(total).c_str());
}
