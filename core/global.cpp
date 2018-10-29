#include "global.hpp"

using namespace std;
namespace nfd {
namespace cs {

		const char *path="/home/lenovo/Dropbox/Thesis/Logs/minindn3/status_2.txt";
		std::ofstream ofs;

		void perfMeasure::printNwMetrics(networkMetrics nm){
		
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "Network_Metrics\n"
					<< "    TotalRespTime="<< nm.responseTime << "\n"
					<< "    AvgRespTime="<< nm.responseTime/nm.nInData << "\n"
					<< "    TotalFwdLatency=" << nm.fwdLatencyTag <<"\n"
					<< "    AvgFwdLatency=" << nm.fwdLatencyTag/nm.nInData <<"\n"
					<< "    TotalInDataPackets=" << nm.nInData << "\n";
			ofs.close();
		
		}
		
		void perfMeasure::clearNwMetrics(networkMetrics &nm){
			nm.responseTime = 0;
			nm.fwdLatencyTag = 0; 
			nm.nInData = 0;
			
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "Network_Metrics\n"
					<< "    TotalRespTime="<< nm.responseTime << "\n"
					<< "    AvgRespTime="<< nm.responseTime << "\n"
					<< "    TotalFwdLatency=" << nm.fwdLatencyTag <<"\n"
					<< "    AvgFwdLatency=" << nm.fwdLatencyTag <<"\n"
					<< "    TotalInDataPackets=" << nm.nInData << "\n";
			ofs.close();
			
		}


		
		


}
}
