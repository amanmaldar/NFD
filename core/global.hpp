#ifndef NFD_DAEMON_FW_GLOBAL_HPP
#define NFD_DAEMON_FW_GLOBAL_HPP

#include "stdint.h"
#include <ctime> 
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <chrono>
#include <iomanip>

//std::string interestName ("blank");




namespace nfd {
namespace cs {

	struct networkMetrics {
		uint64_t responseTime;
		uint64_t fwdLatencyTag;
		uint64_t nInData;
	}
		
	class perfMeasure{
	
	public:
		void printNwMetrics(networkMetrics nm);
		void clearNwMetrics(networkMetrics &nm);
	};


	
	

}
}
#endif