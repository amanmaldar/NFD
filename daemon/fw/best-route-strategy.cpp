/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2014-2018,  Regents of the University of California,
 *                           Arizona Board of Regents,
 *                           Colorado State University,
 *                           University Pierre & Marie Curie, Sorbonne University,
 *                           Washington University in St. Louis,
 *                           Beijing Institute of Technology,
 *                           The University of Memphis.
 *
 * This file is part of NFD (Named Data Networking Forwarding Daemon).
 * See AUTHORS.md for complete list of NFD authors and contributors.
 *
 * NFD is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NFD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NFD, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "best-route-strategy.hpp"
#include "algorithm.hpp"

// Performance metrics initialization
nfd::cs::fibMetrics fibm;
nfd::cs::perfMeasure pm_3;
std::string interestName_3 ("blank");


namespace nfd {
namespace fw {

NFD_LOG_INIT(TrackLat);

// declare a global start time const
auto t1 = std::chrono::high_resolution_clock::now();
auto t2 = std::chrono::high_resolution_clock::now();
std::chrono::duration <double> diff;


BestRouteStrategyBase::BestRouteStrategyBase(Forwarder& forwarder)
  : Strategy(forwarder)
{
}

void
BestRouteStrategyBase::afterReceiveInterest(const Face& inFace, const Interest& interest,
                                            const shared_ptr<pit::Entry>& pitEntry)
{
  if (hasPendingOutRecords(*pitEntry)) {
    // not a new Interest, don't forward
    return;
  }
  	 interestName_3 = interest.getName().toUri();
	NFD_LOG_DEBUG("afterReceiveInterest interest=" << interest.getName() << " " << interestName_3);
	
  	// Action - Reset
	if (interestName_3.find("/ndn/metrics/zero") != std::string::npos) {
		fibm = pm_3.clearFibMetrics(fibm);
		NFD_LOG_DEBUG("afterReceiveInterest zero interest=" << interest.getName());
	}			
			
	// Action - show
	if (interestName_3.find("/ndn/metrics/show") != std::string::npos) {
		fibm.nFibHits--;
		NFD_LOG_DEBUG("afterReceiveInterest show interest=" << interest.getName());
		pm_3.printFibMetrics(fibm);	
	} 
  
  // add FIB lookup timer here
   t1 = std::chrono::high_resolution_clock::now();
  const fib::Entry& fibEntry = this->lookupFib(*pitEntry);
	t2 = std::chrono::high_resolution_clock::now();
    diff = t2-t1;
  	fibm.fibTotalHitLat += diff.count();
	fibm.nFibHits++;
  for (const auto& nexthop : fibEntry.getNextHops()) {
    Face& outFace = nexthop.getFace();
    if (!wouldViolateScope(inFace, interest, outFace) &&
        canForwardToLegacy(*pitEntry, outFace)) {
      this->sendInterest(pitEntry, outFace, interest);
      return;
    }
  }

  this->rejectPendingInterest(pitEntry);
}

NFD_REGISTER_STRATEGY(BestRouteStrategy);

BestRouteStrategy::BestRouteStrategy(Forwarder& forwarder, const Name& name)
  : BestRouteStrategyBase(forwarder)
{
  ParsedInstanceName parsed = parseInstanceName(name);
  if (!parsed.parameters.empty()) {
    BOOST_THROW_EXCEPTION(std::invalid_argument("BestRouteStrategy does not accept parameters"));
  }
  if (parsed.version && *parsed.version != getStrategyName()[-1].toVersion()) {
    BOOST_THROW_EXCEPTION(std::invalid_argument(
      "BestRouteStrategy does not support version " + to_string(*parsed.version)));
  }
  this->setInstanceName(makeInstanceName(name, getStrategyName()));
}

const Name&
BestRouteStrategy::getStrategyName()
{
  static Name strategyName("/localhost/nfd/strategy/best-route/%FD%01");
  return strategyName;
}

} // namespace fw
} // namespace nfd
