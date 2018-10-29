#include "global.hpp"

using namespace std;
namespace nfd {
namespace cs {


	static void ndnPerf::printMetrics(std::string action){
		
		if (!action.compare("reset")){
			ndnPerf::responseTime = 0;
			ndnPerf::fwdLatencyTag = 0; 
			ndnPerf::nInData = 0;
		}
		
		const char *path="/home/lenovo/Dropbox/Thesis/Logs/minindn3/status_2.txt";
		std::ofstream ofs;
		ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "CS_Metrics\n"
					<< "    TotalRespTime="<< ndnPerf::responseTime << "\n"
					<< "    AvgRespTime="<< ndnPerf::responseTime/ndnPerf::nInData << "\n"
					<< "    TotalFwdLatency=" << ndnPerf::fwdLatencyTag <<"\n"
					<< "    AvgFwdLatency=" << ndnPerf::fwdLatencyTag/ndnPerf::nInData <<"\n"
					<< "    TotalInDataPackets=" << ndnPerf::nInData << "\n";
			ofs.close();
}
		}


}
}
