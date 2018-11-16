#include "global.hpp"


using namespace std;
namespace nfd {
namespace cs {

	
		
		//const char *path="/home/lenovo/Dropbox/Thesis/Logs/minindn3/status_2.txt";
		//const char *path_prefix_len="/home/lenovo/Dropbox/Thesis/Logs/minindn3/5000.txt";
		const char *path="/home/amaldar/Logs/status_2.txt";
		const char *path_prefix_len="/home/amaldar/Logs/5000.txt";
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
			
			 //std::time_t now = std::time(0);
			 //char* dt = ctime(&now);
   
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "\n------------------ Network_Metrics:------------------------\n"
					<< 							fixed
					//<< "    		 Total_Exp_Resp_Time = " << nm.responseTime/1000 <<" mS\n"
					<< "       	      Avg. Response Time = " << art/1000 <<" mS\n"
					//<< "	      	   Total_Exp_Fwd_Lat = " << nm.fwdLatencyTag/1000 <<" mS\n"
					<< "    	 Avg. Forwarding Latency = " << afd/1000 <<" mS\n"
					//<< "    	 Total_ProcessLat_OnPath = " << nm.processLat/1000 <<" mS\n"
					<< "         Avg. Processing Latency = " << apl/1000 << " mS\n"
					<< "	   Total Interests Satisfied = " << nm.nSatisfiedInterests << "\n"
					<< "	              Avg. Hop Count = " << ((nm.nInData!=0) ? (float(nm.intHopsTag)/float(nm.nInData)):0) <<"\n";
				
				ofs	<< "\n					Device_Metrics:\n"
					<< "   	 	     nInInterest Packets = " << nm.nInInterests << "\n"
					<< "   	 	    nOutInterest Packets = " << nm.nOutInterests << "\n"
					<< "   	 	     	 nInData Packets = " << nm.nInData << "\n"
					<< "   	 	     	nOutData Packets = " << nm.nOutData << "\n";
				
				ofs	<< "\n					Throughput:\n"
					<< "   	 	     			intSize = " << nm.intSize << "\n"
					<< "   	 	     			dataSize = " << nm.dataSize << "\n";
					
			ofs.close();
			
			
		
		}
		// std::setprecision(2)
		
		networkMetrics perfMeasure::clearNwMetrics(networkMetrics &nm){
			nm.responseTime = 0;
			nm.fwdLatencyTag = 0; 

			nm.processLat = 0;
			nm.nSatisfiedInterests=0;
			nm.intHopsTag =0;
			nm.nInData = 0;
			nm.nOutData = 0;
			nm.nInInterests= 0;
			nm.nOutInterests = 0;
			nm.dataSize = 0;
			nm.intSize = 0;
			
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "\nNetwork_Metrics Reset\n";

			ofs.close();
			
			return nm;
			
		}
		
		void perfMeasure::printCsMetrics(csMetrics csm){
		auto avgCsHitLat = ((csm.nCsMiss!=0) ? csm.csTotalMissLat/csm.nCsMiss:0)*1000000;
		auto avgCsMissLat = ((csm.nCsHits!=0) ? csm.csTotalHitLat/csm.nCsHits:0)*1000000;
		auto avgCsLookup = ((avgCsHitLat+avgCsMissLat)!=0) ? (csm.csTotalMissLat+csm.csTotalHitLat)/(csm.nCsHits+csm.nCsMiss):0;
				ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "\n				CS_Metrics:\n"
					<< 							fixed
					<< "    				   nCS Hits = " << csm.nCsHits <<"\n"	
					<< "    				   nCS Miss = " << csm.nCsMiss <<"\n"
					<< "    			    CS Hit Rate = " << 100*csm.nCsHits/(csm.nCsHits+csm.nCsMiss) <<" %\n"	
					//<< "       Total_csLookUp_Miss_Time = " << csm.csTotalMissLat * 1000000 <<" uS\n"
					<< "           Avg. CS Miss Latency = " <<  avgCsHitLat <<" uS\n"
					//<< "        Total_csLookUp_Hit_Time = " << csm.csTotalHitLat * 1000000 <<" uS\n"
					<< "            Avg. CS Hit Latency = " << avgCsMissLat <<" uS\n"	
					<< "         Avg. CS Lookup Latency = " << avgCsLookup * 1000000 <<" uS\n";	
				ofs.close();
				
			// Print Packet Distribution
			ofs.open (path_prefix_len, std::fstream::in | std::fstream::out | std::fstream::app);
			ofs << "printing 5000 \n";
			for (auto i=csm.myvector.begin();i!=csm.myvector.end();i++){
				ofs << *i << "\n";
			}
			ofs << "done";
			if (!csm.prefixLenDist.empty()){
				ofs << "\nPrefix Length Distribution: <PrefixLength=#Packets> \n";				
				for(auto& x : csm.prefixLenDist) {			   
				ofs << " <" << x.first << "=" << x.second << "> ";
				} 	
			}	
			ofs.close();
		}
		
		csMetrics perfMeasure::clearCsMetrics(csMetrics &csm){
			csm.nCsHits  = 0;
			csm.nCsMiss = 0;
			csm.csTotalMissLat= 0;
			csm.csTotalHitLat = 0;
			csm.myvector.clear();
			csm.prefixLenDist.clear();
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "CS_Metrics Reset\n";
			ofs.close();
			return csm;
		}
		
		void perfMeasure::printPitMetrics(pitMetrics pitm){
		auto avgPitMissLat = ((pitm.nPitMiss!=0) ? pitm.pitTotalMissLat/pitm.nPitMiss:0)*1000000 ;
		auto avgPitHitLat = ((pitm.nPitHits!=0) ? pitm.pitTotalHitLat/pitm.nPitHits:0)*1000000;
		auto avgPitLookupLat = ((avgPitMissLat+avgPitHitLat)!=0) ? (pitm.pitTotalMissLat+pitm.pitTotalHitLat)/(pitm.nPitHits+pitm.nPitMiss):0;
				ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "\n				PIT_Metrics:\n"
					<< 							fixed
					<< "    				   nPIT Hits = " << pitm.nPitHits <<"\n"	
					<< "    				   nPIT Miss = " << pitm.nPitMiss <<"\n"
					<< "    			    PIT Hit Rate = " << 100*pitm.nPitHits/(pitm.nPitHits+pitm.nPitMiss) <<" %\n"	
					//<< "       Total_pitLookUp_Miss_Time = " << pitm.pitTotalMissLat * 1000000 <<" uS\n"
					<< "           Avg. PIT Miss Latency = " << avgPitMissLat <<" uS\n"
					//<< "        Total_pitLookUp_Hit_Time = " << pitm.pitTotalHitLat * 1000000 <<" uS\n"
					<< "            Avg. PIT Hit Latency = " << avgPitHitLat <<" uS\n"	
					<< "     Avg. PIT Processing Latency = " << avgPitLookupLat*1000000 <<" uS\n";	
				ofs.close();
		}
		
		pitMetrics perfMeasure::clearPitMetrics(pitMetrics &pitm){
			pitm.nPitHits  = 0;
			pitm.nPitMiss = 0;
			pitm.pitTotalMissLat= 0;
			pitm.pitTotalHitLat = 0;
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "PIT_Metrics Reset\n";
			ofs.close();
			return pitm;
		}

		void perfMeasure::printFibMetrics(fibMetrics fibm){
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "\n				FIB_Metrics:\n"
					<< 							fixed
					<< "    				  nFIB Hits = " << fibm.nFibHits <<"\n"	
					//<< "       Total_fibLookUp_Hit_Time = " << fibm.fibTotalHitLat * 1000000 <<" uS\n"
					<< "             Forwarding Latency = " << ((fibm.nFibHits!=0) ? fibm.fibTotalHitLat/fibm.nFibHits:0)*1000000 <<" uS\n";

			ofs.close();
		}
		
		fibMetrics perfMeasure::clearFibMetrics(fibMetrics &fibm){
			fibm.nFibHits  = 0;
			
			fibm.fibTotalHitLat = 0;
			
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "Fib_Metrics Reset\n";
			ofs.close();
			return fibm;
		}


		
		


}
}
