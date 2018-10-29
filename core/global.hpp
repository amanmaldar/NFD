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

class ndnPerf{
	public:
		static uint64_t responseTime;
		static uint64_t fwdLatencyTag;
		static uint64_t nInData;
	public:
	static void printMetrics(std::string action);
}
	
	

}
}
#endif