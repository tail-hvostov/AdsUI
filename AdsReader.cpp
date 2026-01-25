#include "AdsReader.hpp"

#include <stdio.h>
#include <atomic>
#include <thread>
#include <memory>

namespace {
	ADSR::AdsStats global_stats;
	std::atomic_flag access_flag;
	std::atomic<bool> measurements_needed;
	std::unique_ptr<std::thread> measurement_thread;

	void measurement_thread_proc() {
		puts("measure");
	}
}

namespace ADSR {
	void start() {
		measurements_needed.store(true);
		measurement_thread.reset(new std::thread(&measurement_thread_proc));
	}

	void stop() {
		measurements_needed.store(false);
		measurement_thread->join();
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