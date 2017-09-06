/************************************************************************
 * Copyright 2009, 2011, Strathclyde Planning Group,
 * Department of Computer and Information Sciences,
 * University of Strathclyde, Glasgow, UK
 * http://planning.cis.strath.ac.uk/
 *
 * Amanda Coles, Andrew Coles, Maria Fox, Derek Long - POPF
 * Maria Fox, Richard Howey and Derek Long - VAL
 * Stephen Cresswell - PDDL Parser
 *
 * This file is part of POPF.
 *
 * POPF is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * POPF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with POPF.  If not, see <http://www.gnu.org/licenses/>.
 *
 ************************************************************************/

#ifndef PLANNERTEMPORALANALYSIS_H
#define PLANNERTEMPORALANALYSIS_H

#include "RPGBuilder.h"

#include <set>
using std::set;

namespace Planner
{

class TemporalAnalysis;

class TILTimeline {
    
public:
    
    friend class TemporalAnalysis;
    
    struct AddedOrDeleted {
        
        bool added;
        bool deleted;
        
        AddedOrDeleted()
            : added(false), deleted(false) {
        }
                    
        AddedOrDeleted(const bool & b)
            : added(b), deleted(!b) {
        }
                                    
    };
    
    typedef map<double, AddedOrDeleted> TimelineData;
    
    typedef TimelineData::const_iterator const_iterator;
    
private:
    
    /** @brief Time-stamped TIL events on the fact */
    TimelineData happenings;

    bool onlyEverAddedByTILs;
    bool onlyEverDeletedByTILs;
    
    const_iterator firstAdder;
    const_iterator firstDeletor;
    const_iterator lastDeletor;
    
public:
    
    TILTimeline()
        : onlyEverAddedByTILs(true), onlyEverDeletedByTILs(true) {
    }
    
    const bool & isOnlyEverAddedByTILs() const {
        return onlyEverAddedByTILs;    
    }
    
    const bool & isOnlyEverDeletedByTILs() const {
        return onlyEverDeletedByTILs;    
    }
  
    inline const_iterator begin() const {
        return happenings.begin();
    }
  
    inline const_iterator end() const {
        return happenings.end();
    }

    inline const const_iterator & getFirstAdder() const {
        return firstAdder;
    }
      
    inline const const_iterator & getFirstDeletor() const {
        return firstDeletor;
    }
    
    inline const const_iterator & getLastDeletor() const {
        return lastDeletor;
    }
    
    const_iterator firstAdderSuitableForTime(const double & t) const {
        const_iterator toReturn = happenings.upper_bound(t); // find the next point on the timeline after t
        if (toReturn != happenings.begin()) { // but actually we want the point before then, so roll backwards
            --toReturn;
        }
        for (; toReturn != happenings.end() && !toReturn->second.added; ++toReturn) ; // roll forwards until we're after an adder
        return toReturn;
    }
    
    const_iterator firstDeletorAfterTime(const double & t) const {
        const_iterator toReturn = happenings.upper_bound(t);
        for (; toReturn != happenings.end() && !toReturn->second.deleted; ++toReturn) ;
        return toReturn;
    }
    
    const_iterator firstDeletorAtOrAfterTime(const double & t) const {
        const_iterator toReturn = happenings.lower_bound(t);
        for (; toReturn != happenings.end() && !toReturn->second.deleted; ++toReturn) ;
        return toReturn;
    }
        
};

class TIFTimeline {

public:
    
    friend class TemporalAnalysis;
    
    typedef set<double> TimelineData;
    
    typedef TimelineData::const_iterator const_iterator;
    
private:

    TimelineData happenings;
    
    bool onlyEverChangedByTIFs;
        
public:

    TIFTimeline()
        : onlyEverChangedByTIFs(true) {
    }
    
    const bool & isOnlyEverChangedByTIFs() const {
        return onlyEverChangedByTIFs;    
    }
    
    inline const_iterator begin() const {
        return happenings.begin();
    }
  
    inline const_iterator end() const {
        return happenings.end();
    }

    const_iterator firstChangeAfterTime(const double & t) const {        
        return happenings.upper_bound(t);
    }

    const_iterator changeAtOrAfterTime(const double & t) const {
        return happenings.lower_bound(t);
    }
    
};

class TemporalAnalysis
{

private:
    static vector<bool> startEndSkip;
    
    static map<int, list<pair<double, double> > > windows;
    static vector<vector<pair<double, double> > > actionTSBounds;
    static LiteralSet initialState;
            
    static void recogniseHoldThroughoutDeleteAtEndIdiom(LiteralSet & factsIdentified);
    
    #ifdef POPF3ANALYSIS
    static bool endNumericEffectsAreCompressionSafe(const list<int> & effects,
                                                    vector<bool> & allInteractionWithVarIsCompressionSafe);
    static void markCompressionSafetyConditions(const int & actID, const list<int> & effects,
                                                vector<set<int> > & actionsDependingOnVarBeingCompressionSafe);
    static void markAffectedVariablesAsNotCompressionSafe(const list<int> & effects,
                                                          vector<bool> & allInteractionWithVarIsCompressionSafe,
                                                          set<int> & newlyUnsafe);
    #endif

    /** @brief A timeline on the given TIL-manipulated fact */
    static map<int, TILTimeline> timelineOnTILs;
    
    /** @brief A timeline on variables altered by Timed Initial Fluents (TIFs) */
    static map<int, TIFTimeline> timelineOnTIFs;    
    

    static double upperBoundOnVariableIfNextTILIsAtTime(const int & variable,
                                                        const bool & epsilonSeparation,
                                                        const double & nextTILTimestamp);
    
    static double upperBoundOnNumericPreconditionsIfNextTILIsAtTime(const list<int> & pres,
                                                                    const bool & epsilonSeparation,
                                                                    const double & nextTILTimestamp);
            
    static double upperBoundOnFactsIfNextTILIsAtTime(const list<Literal*> & facts,
                                                     const bool & epsilonSeparation,
                                                     const double & nextTILTimestamp);
    
public:

           
    static void dummyDeadlineAnalysis();
    static void processTILDeadlines();
    static void findGoalDeadlines(list<Literal*> &, list<double> &);
    static void findActionTimestampLowerBounds();
    static void findCompressionSafeActions();
    
    static void buildTimelinesOnTILs();
    static void buildTimelinesOnTIFs();
    
    static vector<vector<pair<double, double> > > & getActionTSBounds() {
        return actionTSBounds;
    }
    
    static const list<pair<double, double> > * factIsVisibleInWindows(const Literal* const l) {
        map<int, list<pair<double, double> > >::const_iterator wItr = windows.find(l->getStateID());
        if (wItr == windows.end()) return 0;
        return &(wItr->second);
    }
    
    static void suggestNewStartLowerBound(const int & a, const double & d) {
        if (actionTSBounds[a][0].first < d) {
            actionTSBounds[a][0].first = d;
        }
    }

    static void suggestNewEndLowerBound(const int & a, const double & d) {
        if (actionTSBounds[a][1].first < d) {
            actionTSBounds[a][1].first = d;
        }
    }

    static bool actionIsNeverApplicable(const int & a);
    static bool okayToStart(const int & a, const double & ts) {
        return (ts <= actionTSBounds[a][0].second);
    }

    static bool okayToEnd(const int & a, const double & ts) {
        return (ts <= actionTSBounds[a][1].second);
    }

    static bool canSkipToEnd(const int & i) {
        return startEndSkip[i];
    };
    
    static const TILTimeline * timelineOnTILFact(const int & fID) {
        map<int, TILTimeline>::const_iterator tItr = timelineOnTILs.find(fID);
        if (tItr == timelineOnTILs.end()) {
            return 0;
        }
        return &(tItr->second);
    }
    
    
    /** @brief Work out the latest point at which the given action can be applied, due to inevitable orderings before the next TIL.
     * 
     * Upper bounds are introduced by:
     *  - A precondition p, where a future TIL deletes p;
     *  - A precondition on a variable v, where a future TIL changes the value of v.
     * 
     * @param theAction  An action in the plan
     * @param nextTIL    The ID of the next TIL that could be added in the plan after <code>theAction</code>.  @see <code>RPGBuilder::getTILVec()</code>
     * @return           The upper-bound on the timestamp of <code>theAction</code>, due to pending TIL happenings.
     */ 
    static double upperBoundOnActionIfNextTILIs(const ActionSegment & theAction, const int & nextTIL);

    /** @brief In a goal state, check whether pending TILs or TIFs could negate the goals.
     * 
     * This returns true if:
     * - There is a goal fact that will be deleted (and not then re-added) by future TILs; or,
     * - There is a goal numeric condition that is changed by a future TIFs.
     * 
     * @retval <code>true</code>   Future TILs might negate the goals;
     * @retval <code>false</code>  Future TILs will not negate the goals.
     */
    static bool futureTILsMightInterfereWithGoals(const int & nextTIL);
    
};

}

#endif
