/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2014  <copyright holder> <email>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef TIMEWINDOWSCHECKER_H
#define TIMEWINDOWSCHECKER_H
#include <list>

// #include "RPGBuilder.h"
#include "FFSolver.h"
#include "FFEvent.h"
#include "minimalstate.h"

using namespace std;

namespace Planner{
    
class TimewindowsChecker
{
    /** @brief find events that are timewindows
     *  @param header partial plan
     *  @param theState state that we are checking
     *  @retval int is the nuber of events
     *  @retval FFEvent is the timewindow
    */
public:
    static list<pair<int, FFEvent> > openOneShotTimewindowActions(list<FFEvent> & header, MinimalState theState);
    // void static addActionToHeader
    static void addTemporalConstraint(TemporalConstraints &cons, list<FFEvent> &header, int idTW, int idActToPass);
    static list<FFEvent> addActionToHeader(list<FFEvent> &header, list<StartEvent> &open, ActionSegment & actID);
    static bool checkRelaxedPlanTimeWindows(list<FFEvent> header, list<pair<double, list<ActionSegment> > > relaxedPlan, MinimalState theState, list<StartEvent> startEventQueue);
    static bool heuristicCheck;
    static bool relaxedCheck;
};
};

#endif // TIMEWINDOWSCHECKER_H
