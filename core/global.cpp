#include "global.hpp"


using namespace std;
namespace nfd {
namespace cs {

	
		
		const char *path="/home/lenovo/Dropbox/Thesis/Logs/minindn3/status_2.txt";
		const char *path_prefix_len="/home/lenovo/Dropbox/Thesis/Logs/minindn3/prefix_len.txt";
		
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
					<< "    		 Total_Exp_Resp_Time = " << nm.responseTime/1000 <<" mS\n"
					<< "       	    Per_Packet_Resp_Time = " << art/1000 <<" mS\n"
					<< "	      	   Total_Exp_Fwd_Lat = " << nm.fwdLatencyTag/1000 <<" mS\n"
					<< "    		  Per_Packet_Fwd_Lat = " << afd/1000 <<" mS\n"
					<< "    	 Total_ProcessLat_OnPath = " << nm.processLat/1000 <<" mS\n"
					<< "   Per_Packet_ProcessLat_OnPath = " << apl/1000 << " mS\n"
					<< "   	 	   Total_InData_Packets = " << nm.nInData << "\n"
					<< "	       nSatisfied_Interests = " << nm.nSatisfiedInterests << "\n"
					<< "	              Avg_Hop_Count = " << ((nm.nInData!=0) ? nm.intHopsTag/nm.nInData:0)<<"\n";
					
			
					
			ofs.close();
			
			
		
		}
		// std::setprecision(2)
		
		networkMetrics perfMeasure::clearNwMetrics(networkMetrics &nm){
			nm.responseTime = 0;
			nm.fwdLatencyTag = 0; 
			nm.nInData = 0;
			nm.processLat = 0;
			nm.nSatisfiedInterests=0;
			nm.intHopsTag =0;

			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "\nNetwork_Metrics Reset\n";

			ofs.close();
			
			return nm;
			
		}
		
		void perfMeasure::printCsMetrics(csMetrics csm){
				ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "\n				CS_Metrics:\n"
					<< 							fixed
					<< "    				   nCS_Hits = " << csm.nCsHits <<"\n"	
					<< "    				   nCS_Miss = " << csm.nCsMiss <<"\n"
					<< "    			   CS_Hit_Ratio = " << 100*csm.nCsHits/(csm.nCsHits+csm.nCsMiss) <<" %\n"	
					<< "       Total_csLookUp_Miss_Time = " << csm.csTotalMissLat * 1000000 <<" uS\n"
					<< "  Per_Packet_csLookUp_Miss_Time = " << ((csm.nCsMiss!=0) ? csm.csTotalMissLat/csm.nCsMiss:0)*1000000 <<" uS\n"
					<< "        Total_csLookUp_Hit_Time = " << csm.csTotalHitLat * 1000000 <<" uS\n"
					<< "   Per_Packet_csLookUp_Hit_Time = " << ((csm.nCsHits!=0) ? csm.csTotalHitLat/csm.nCsHits:0)*1000000 <<" uS\n";	
				
				ofs.close();
				
			// Print Packet Distribution
			ofs.open (path_prefix_len, std::fstream::in | std::fstream::out | std::fstream::app);
			
				
			if (!csm.prefixLenDist.empty()){
				ofs << "<Prefix_Length_#Packets>\n";			
				for(auto& x : csm.prefixLenDist) {			   
					ofs << "<" << x.first << "=" << x.second << ">" << "\n";
				} 
				ofs << "</Prefix_Length_#Packets>\n";			
			}	
			ofs.close();
		}
		
		csMetrics perfMeasure::clearCsMetrics(csMetrics &csm){
			csm.nCsHits  = 0;
			csm.nCsMiss = 0;
			csm.csTotalMissLat= 0;
			csm.csTotalHitLat = 0;
			csm.prefixLenDist.clear();
			ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "CS_Metrics Reset\n";
			ofs.close();
			return csm;
		}
		
		void perfMeasure::printPitMetrics(pitMetrics pitm){
				ofs.open (path, std::fstream::in | std::fstream::out | std::fstream::app);
				ofs	<< "\n				PIT_Metrics:\n"
					<< 							fixed
					<< "    				   nPIT_Hits = " << pitm.nPitHits <<"\n"	
					<< "    				   nPIT_Miss = " << pitm.nPitMiss <<"\n"
					<< "    			   PIT_Hit_Ratio = " << 100*pitm.nPitHits/(pitm.nPitHits+pitm.nPitMiss) <<" %\n"	
					<< "       Total_pitLookUp_Miss_Time = " << pitm.pitTotalMissLat * 1000000 <<" uS\n"
					<< "  Per_Packet_pitLookUp_Miss_Time = " << ((pitm.nPitMiss!=0) ? pitm.pitTotalMissLat/pitm.nPitMiss:0)*1000000 <<" uS\n"
					<< "        Total_pitLookUp_Hit_Time = " << pitm.pitTotalHitLat * 1000000 <<" uS\n"
					<< "   Per_Packet_pitLookUp_Hit_Time = " << ((pitm.nPitHits!=0) ? pitm.pitTotalHitLat/pitm.nPitHits:0)*1000000 <<" uS\n";	
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
					<< "    				  nFIB_Hits = " << fibm.nFibHits <<"\n"	
					<< "       Total_fibLookUp_Hit_Time = " << fibm.fibTotalHitLat * 1000000 <<" uS\n"
					<< " Per_Packet_fibLookUp_Hit_Time = " << ((fibm.nFibHits!=0) ? fibm.fibTotalHitLat/fibm.nFibHits:0)*1000000 <<" uS\n";

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
