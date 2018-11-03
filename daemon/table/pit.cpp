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

#include "pit.hpp"

// Performance metrics initialization
nfd::cs::pitMetrics pitm;
nfd::cs::perfMeasure pm_2;


std::string interestName_1 ("blank");
namespace nfd {
namespace pit {

// declare a global start time const
auto t1 = std::chrono::high_resolution_clock::now();
auto t2 = std::chrono::high_resolution_clock::now();
std::chrono::duration <double> diff;


static inline bool
nteHasPitEntries(const name_tree::Entry& nte)
{
  return nte.hasPitEntries();
}

Pit::Pit(NameTree& nameTree)
  : m_nameTree(nameTree)
  , m_nItems(0)
{
}

std::pair<shared_ptr<Entry>, bool>
Pit::findOrInsert(const Interest& interest, bool allowInsert)
{
  // determine which NameTree entry should the PIT entry be attached onto
  const Name& name = interest.getName();
  // Print PIT status
  interestName_1 = interest.getName().toUri();

	// Action - Reset
	if (interestName_1.find("/ndn/metrics/zero") != std::string::npos) {
		pitm = pm_2.clearPitMetrics(pitm);
	}			
			
	// Action - show
	if (interestName_1.find("/ndn/metrics/show") != std::string::npos) {
		pitm.nPitHits--;
		pm_2.printPitMetrics(pitm);	
	} 
		

	
  bool hasDigest = name.size() > 0 && name[-1].isImplicitSha256Digest();
  size_t nteDepth = name.size() - static_cast<int>(hasDigest);
  nteDepth = std::min(nteDepth, NameTree::getMaxDepth());

	// Name Tree lookup is actually happening here. It is common lookup for PIT and FIB
	 t1 = std::chrono::high_resolution_clock::now();
  // ensure NameTree entry exists
  name_tree::Entry* nte = nullptr;
  if (allowInsert) {	// forwarding path/ Before adding interest to PIT, see if FIB has path
    nte = &m_nameTree.lookup(name, nteDepth);
  }
  else {		// return path. find is called on PIT
    nte = m_nameTree.findExactMatch(name, nteDepth);
    if (nte == nullptr) {
      return {nullptr, true};
    }
  }

  // check if PIT entry already exists in name tree
  const auto& pitEntries = nte->getPitEntries();
  auto it = std::find_if(pitEntries.begin(), pitEntries.end(),
    [&interest, nteDepth] (const shared_ptr<Entry>& entry) {
  
      return entry->canMatch(interest, nteDepth);
    });
  if (it != pitEntries.end()) {
  
    // PIT hit scenario. Return the match result
   	t2 = std::chrono::high_resolution_clock::now();
    diff = t2-t1;
  	pitm.pitTotalHitLat += diff.count();
	pitm.nPitHits++;
    return {*it, false};
  }

  if (!allowInsert) {
    BOOST_ASSERT(!nte->isEmpty()); // nte shouldn't be created in this call
    return {nullptr, true};
  }

	// PIT missed
  auto entry = make_shared<Entry>(interest);
  nte->insertPitEntry(entry);	// add entry to Name Tree Entry (nte)
  ++m_nItems;
  // PIT miss scenario
  if (interestName_1.find("nlsr") == std::string::npos){
	  t2 = std::chrono::high_resolution_clock::now();
	  diff = t2-t1;
	  pitm.pitTotalMissLat += diff.count();
	  pitm.nPitMiss++;
  }
  return {entry, true};
}

DataMatchResult
Pit::findAllDataMatches(const Data& data) const
{
  auto&& ntMatches = m_nameTree.findAllMatches(data.getName(), &nteHasPitEntries);

  DataMatchResult matches;
  for (const name_tree::Entry& nte : ntMatches) {
    for (const shared_ptr<Entry>& pitEntry : nte.getPitEntries()) {
      if (pitEntry->getInterest().matchesData(data))
        matches.emplace_back(pitEntry);
    }
  }

  return matches;
}

void
Pit::erase(Entry* entry, bool canDeleteNte)
{
  name_tree::Entry* nte = m_nameTree.getEntry(*entry);
  BOOST_ASSERT(nte != nullptr);

  nte->erasePitEntry(entry);
  if (canDeleteNte) {
    m_nameTree.eraseIfEmpty(nte);
  }
  --m_nItems;
}

void
Pit::deleteInOutRecords(Entry* entry, const Face& face)
{
  BOOST_ASSERT(entry != nullptr);

  entry->deleteInRecord(face);
  entry->deleteOutRecord(face);

  /// \todo decide whether to delete PIT entry if there's no more in/out-record left
}

Pit::const_iterator
Pit::begin() const
{
  return const_iterator(m_nameTree.fullEnumerate(&nteHasPitEntries).begin());
}

} // namespace pit
} // namespace nfd
