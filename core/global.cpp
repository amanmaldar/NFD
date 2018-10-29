#include "global.hpp"

using namespace std;
namespace nfd {
namespace cs {


		void perfMeasure::printNwMetrics(networkMetrics nm){
			const char *path="/home/lenovo/Dropbox/Thesis/Logs/minindn3/status_2.txt";
			std::ofstream ofs;
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "CS_Metrics\n"
					<< "    TotalRespTime="<< nm.responseTime << "\n"
					<< "    AvgRespTime="<< nm.responseTime/nm.nInData << "\n"
					<< "    TotalFwdLatency=" << nm.fwdLatencyTag <<"\n"
					<< "    AvgFwdLatency=" << nm.fwdLatencyTag/nm.nInData <<"\n"
					<< "    TotalInDataPackets=" << nm.nInData << "\n";
			ofs.close();
		
		}
		
		void perfMeasure::clearNwMetrics(networkMetrics &nm){
			nm.responseTime = 0;
			*nm->fwdLatencyTag = 0; 
			*nm.nInData = 0;
		}


		
		


}
}
