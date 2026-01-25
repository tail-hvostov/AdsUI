#include "AdsReader.hpp"

#include <stdio.h>
#include <atomic>

namespace {
	ADSR::AdsStats global_stats;
	std::atomic_flag access_flag;
}

namespace ADSR {
	void start() {
		puts("start");
	}

	void stop() {
		puts("stop");
	}

	void retrieve(AdsStats& stats) {
		while (access_flag.test_and_set());
		stats = global_stats;
		for (int i = 0; i < INPUT_COUNT; i++) {
			stats.average_v[i] /= stats.measurements;
		}
		std::memset(&global_stats, 0, sizeof(global_stats));
		access_flag.clear();
	}
}