#pragma once 

#include <string>
#include <chrono>

class TimeTrack {
public:
	std::string msg;
	double		t = 0;
	TimeTrack(const char* _msg) {
		msg = _msg;
		t = getTimeStamp();
	}

	~TimeTrack();

	static double getTimeStamp() {
		using namespace std::chrono;
		std::chrono::nanoseconds ns =
			duration_cast<std::chrono::nanoseconds>(system_clock::now().time_since_epoch());
		return ns.count() / 1000000000.0;
	}
};