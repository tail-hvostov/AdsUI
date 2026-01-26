#include "AdsReader.hpp"

#include <stdio.h>
#include <atomic>
#include <thread>
#include <memory>
#include <cstring>
#include <stdexcept>>

#include "ADS1256.hpp"

namespace {
	ADSR::AdsStats global_stats;
	std::atomic_flag access_flag;
	std::atomic<bool> measurements_needed;
	std::unique_ptr<std::thread> measurement_thread;

	void measurement_thread_proc() {
		while (measurements_needed.load()) {
			puts("measure");
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			while (access_flag.test_and_set());

			global_stats.measurements++;

			access_flag.clear();
		}
	}
}

namespace ADSR {
	void start() {
		if (!measurements_needed.exchange(true)) {
			std::memset(&global_stats, 0, sizeof(global_stats));
			DEV_ModuleInit();
			if(ADS1256_init() == 1){
        		puts("Error!");
        		DEV_ModuleExit();
		        measurements_needed.store(false);
		        throw std::runtime_error("ADS error!");
		    }
			measurement_thread.reset(new std::thread(&measurement_thread_proc));
		}
	}

	void stop() {
		if (measurements_needed.exchange(false)) {
			measurement_thread->join();
			DEV_ModuleExit();
		}
	}

	void retrieve(AdsStats& stats) {
		while (access_flag.test_and_set());
		stats = global_stats;
		if (stats.measurements > 0) {
			for (int i = 0; i < INPUT_COUNT; i++) {
				stats.average_v[i] /= stats.measurements;
			}
		}
		std::memset(&global_stats, 0, sizeof(global_stats));
		access_flag.clear();
	}
}
