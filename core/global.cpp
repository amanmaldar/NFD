#include "global.hpp"

using namespace std;
namespace nfd {
namespace cs {

	

		const char *path="/home/lenovo/Dropbox/Thesis/Logs/minindn3/status_2.txt";
		std::ofstream ofs;
		double wtime()
		{
			double time[2];	
			struct timeval time1;
			gettimeofday(&time1, NULL);

			time[0]=time1.tv_sec;
			time[1]=time1.tv_usec;

			return time[0]+time[1]*1.0e-6;
		}
		
		void sayHello(){
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs << "	hello world" << "\n";
			ofs.close();
		}

		void perfMeasure::printNwMetrics(networkMetrics nm){
			
			float art = 0;
			float afd = 0;
			if (nm.nInData != 0)
			{
				art = nm.responseTime/nm.nInData ;
				afd = nm.fwdLatencyTag/nm.nInData ;
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
