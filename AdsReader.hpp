#ifndef _ADS_READER_HPP_
#define _ADS_READER_HPP_

namespace ADSR {
	const int INPUT_COUNT = 8;

	struct AdsStats {
		unsigned int measurements;
		double average_v[INPUT_COUNT];
	};

	void start();
	void stop();
	void retrieve(AdsStats& stats);
};

#endif