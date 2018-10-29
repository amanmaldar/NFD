#include "global.hpp"

using namespace std;
namespace nfd {
namespace cs {

		const char *path="/home/lenovo/Dropbox/Thesis/Logs/minindn3/status_2.txt";
		std::ofstream ofs;

		void perfMeasure::printNwMetrics(networkMetrics nm){
		
			if (nm.nInData != 0)
			{
				auto art = nm.responseTime/nm.nInData ;
				auto afd = nm.fwdLatencyTag/nm.nInData ;
			}
			else{
				auto art = 0;
				auto afd = 0;
			}
			
		
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "Network_Metrics\n"
					<< "    TotalRespTime="<< nm.responseTime << "\n"
					<< "    AvgRespTime="<< art << "\n"
					<< "    TotalFwdLatency=" << nm.fwdLatencyTag <<"\n"
					<< "    AvgFwdLatency=" << afd <<"\n"
					<< "    TotalInDataPackets=" << nm.nInData << "\n";
			ofs.close();
		
		}
		
		networkMetrics perfMeasure::clearNwMetrics(networkMetrics &nm){
			nm.responseTime = 0;
			nm.fwdLatencyTag = 0; 
			nm.nInData = 0;
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "Network_Metrics Reset\n";
			ofs.close();
			
			return nm;
			
		}


		
		


}
}
