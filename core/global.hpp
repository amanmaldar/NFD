#ifndef NFD_CORE_GLOBAL_HPP
#define NFD_CORE_GLOBAL_HPP

#include "stdint.h"
#include <ctime> 
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <iostream>



namespace nfd {
namespace cs {

	struct csMetrics {

		uint64_t nCsHits;
		uint64_t nCsMiss;
        double csTotalHitLat;
        double csTotalMissLat;	

	};
	
	struct pitMetrics {

		uint64_t nPitHits;
		uint64_t nPitMiss;
        double pitTotalHitLat;
        double pitTotalMissLat;	

	};
	
	
	struct fibMetrics {

		uint64_t nFibHits;
		double fibTotalHitLat;
	};
	struct networkMetrics {


		uint64_t responseTime;
		uint64_t fwdLatencyTag;
		uint64_t nInData;
		uint64_t processLat;
		
		

	};
	void sayHello();
	double wtime();
		
	class perfMeasure{
	
	public:
		void printNwMetrics(networkMetrics nm);
		networkMetrics clearNwMetrics(networkMetrics &nm);
		void printCsMetrics(csMetrics csm);
		csMetrics clearCsMetrics(csMetrics &csm);
		
		void printPitMetrics(pitMetrics pitm);
		pitMetrics clearPitMetrics(pitMetrics &pitm);
		
		void printFibMetrics(fibMetrics fibm);
		fibMetrics clearFibMetrics(fibMetrics &fibm);

	};


	
	

}
}
#endif