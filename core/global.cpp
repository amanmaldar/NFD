#include "global.hpp"

using namespace std;
namespace nfd {
namespace cs {

	

		const char *path="/home/lenovo/Dropbox/Thesis/Logs/minindn3/status_2.txt";
		std::ofstream ofs;

		void sayHello(){
		return;
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs << "	hello world" << "\n";
			ofs.close();
		}

		void perfMeasure::printNwMetrics(networkMetrics nm){
			
			float art = 0;
			float afd = 0;
			float apl = 0;
			if (nm.nInData != 0)
			{
				art = nm.responseTime/nm.nInData ;
				afd = nm.fwdLatencyTag/nm.nInData ;
				apl = nm.processLat/nm.nInData ;
			}
			
		
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "Network_Metrics\n"
					<< "    TotalRespTime="<< nm.responseTime << "\n"
					<< "    AvgRespTime="<< art << "\n"
					<< "    TotalFwdLatency=" << nm.fwdLatencyTag <<"\n"
					<< "    AvgFwdLatency=" << afd <<"\n"
					<< "    TotalProcessLatOnPath=" << nm.processLat << "\n"
					<< "    AvgProcessLatOnPath="<< apl << "\n"
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
