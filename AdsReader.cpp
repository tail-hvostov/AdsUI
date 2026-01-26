#include "AdsReader.hpp"

#include <stdio.h>
#include <atomic>
#include <thread>
#include <memory>
#include <cstring>
#include <stdexcept>

#include "ADS1256.hpp"

namespace {
	ADSR::AdsStats global_stats;
	std::atomic_flag access_flag;

	std::atomic<UDOUBLE> vals[ADSR::INPUT_COUNT];
	std::atomic<unsigned int> measurements;

	std::unique_ptr<std::thread> measurement_thread;

	void measurement_thread_proc() {
		while (measurements_needed.load()) {
			for (int i = 0; i < ADSR::INPUT_COUNT; i++) {
				vals[i].store(ADS1256_GetChannalValue(i));
			}
			measurements++;
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
		for (int i = 0; i < INPUT_COUNT; i++) {
			stats.average_in[i] = vals[i].load() * REF_U / 0x7fffff;
		}
		stats.measurements = measurements.load();
	}
}
