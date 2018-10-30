#ifndef NFD_DAEMON_FW_GLOBAL_HPP
#define NFD_DAEMON_FW_GLOBAL_HPP

#include "stdint.h"
#include <ctime> 
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <chrono>
#include <iomanip>



namespace nfd {
namespace cs {

	struct networkMetrics {
		uint64_t responseTime;
		uint64_t fwdLatencyTag;
		uint64_t nInData;
		int t;
	}nm2;
		
	class perfMeasure{
	
	public:
		void printNwMetrics(networkMetrics nm);
		networkMetrics clearNwMetrics(networkMetrics &nm);
	};


	
	

}
}
#endif