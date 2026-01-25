#include "AdsReader.hpp"

#include <stdio.h>

namespace {
	ADSR::AdsStats global_stats;
}

namespace ADSR {
	void start() {
		puts("start");
	}

	void stop() {
		puts("stop");
	}

	void retrieve(AdsStats& stats) {
		puts("retrieve");
	}
}