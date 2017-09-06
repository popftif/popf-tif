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


#include "TimewindowsChecker.h"
#include <list>
#include "FFEvent.h"
#include "minimalstate.h"
#include "RPGBuilder.h"
#include "temporalanalysis.h"
#include "temporalconstraints.h"
#include "lpscheduler.h"

using namespace std;


namespace Planner{
list< std::pair<int, FFEvent> > TimewindowsChecker::openOneShotTimewindowActions(list< FFEvent >& header, MinimalState theState)
{

    list<FFEvent>::reverse_iterator evIt = header.rbegin();
    list<FFEvent>::reverse_iterator evEnd = header.rend();
    set<int> oneShotTimewindowActionEnd;
    list<pair<int, FFEvent> > openOneShotTimewindowAction;
    
    for(int idAct = 0 ;evIt!=evEnd;++evIt,++idAct){
        
        int actID = evIt->action->getID();
        bool isAtEnd = false;
        bool isAtStart = true;
        bool isOneShotTimeWindow = RPGBuilder::isOneshotTimewindow(actID);
        
        if (isOneShotTimeWindow){
            // this is to ensure that the timewindows is open
            if(evIt->time_spec==VAL::E_AT_END){
                
                if (evIt->getEffects){
                    oneShotTimewindowActionEnd.insert(actID);
                }
            }else if(evIt->time_spec==VAL::E_AT_START){
                if(oneShotTimewindowActionEnd.find(actID)==oneShotTimewindowActionEnd.end()){
                    openOneShotTimewindowAction.push_back(make_pair(header.size()-idAct, (*evIt)));
                }
            }else{
                assert("Timewindow action not valid");
            }
        }
    }
    
    return openOneShotTimewindowAction;
    
}

void TimewindowsChecker::addTemporalConstraint(TemporalConstraints &cons, list< FFEvent >& header, int idTW, int idActToPass)
{
    bool epsilonlater = true;
    int lengthPlan = header.size();
    int endAction = lengthPlan+1;
    cons.addOrdering(lengthPlan,endAction,epsilonlater);
    cons.addOrdering(endAction,idTW,epsilonlater);
    cons.addOrdering(idTW-1,endAction,epsilonlater);
    list<FFEvent>::iterator hIt = header.begin();
    list<FFEvent>::iterator hEnd = header.end();
//     const list<Literal*> & prec = RPGBuilder::getStartPropositionAdds()[idActToPass];
    const list<Literal*> & precOverallATP = RPGBuilder::getInvariantPropositionalPreconditions()[idActToPass];
    const list<Literal*> & negEffATP = RPGBuilder::getEndPropositionDeletes()[idActToPass];
    for(int i=0;hIt!=hEnd;++hIt,++i){
        if(hIt->time_spec!=VAL::E_AT_END){
            cons.addOrdering(i,endAction,epsilonlater);            
        }else{
            if(hIt->getEffects){
                cons.addOrdering(i,endAction,epsilonlater);      
            }else{
                // add temporal constraint if actions interferes with overall conditions...
                const list<Literal*> & negEff = RPGBuilder::getEndPropositionDeletes()[hIt->action->getID()];
                list<Literal*>::const_iterator negEffIt = negEff.begin();
                bool ordering = false;
                for(;negEffIt!=negEff.end();++negEffIt){
                    if(find(precOverallATP.begin(),precOverallATP.end(),*negEffIt)!=precOverallATP.end()/* || find(prec.begin(),prec.end(),*negEffIt)!=prec.end()*/ ){
                        ordering = true;
                        break;
                    }
                }
                if(ordering){
                    cons.addOrdering(endAction,i,epsilonlater);    
                    continue;
                }
                const list<Literal*> & precOverall = RPGBuilder::getInvariantPropositionalPreconditions()[hIt->action->getID()];
                list<Literal*>::const_iterator prOIt = precOverall.begin();
                ordering = false;
                for(;prOIt!=precOverall.end();++prOIt){
                    if(find(negEffATP.begin(),negEffATP.end(),*prOIt)!=negEffATP.end()/* || find(prec.begin(),prec.end(),*negEffIt)!=prec.end()*/ ){
                        ordering = true;
                        break;
                    }
                }
                if(ordering)
                    cons.addOrdering(i,endAction,epsilonlater); 
            }
        }
    }
}

list<FFEvent> TimewindowsChecker::addActionToHeader(list< FFEvent >& header, list< StartEvent > & open, ActionSegment & actID)
{
    
    list<FFEvent> newHeader;
    FFEvent extraEvent;
    FFEvent extraEventTwo;
    FFEvent * reusedEndEvent = 0;
    bool eventOneDefined = false;
    bool eventTwoDefined = false;
    const bool rawDebug = false;
    map<double, list<pair<int, int> > > * justApplied = 0;
    map<double, list<pair<int, int> > > actualJustApplied;
    double tilFrom = 0.001;
    int stepID = -1;
    if (actID.second == VAL::E_AT_START) {
        if (rawDebug) cout << "RAW start\n";
        extraEvent = FFEvent(actID.first, open.back().minDuration, open.back().maxDuration);
        eventOneDefined = true;
        assert(extraEvent.time_spec == VAL::E_AT_START);
        //         makeJustApplied(actualJustApplied, tilFrom, state, true);
        if (!actualJustApplied.empty()) justApplied = &actualJustApplied;
        if (!RPGBuilder::getRPGDEs(actID.first->getID()).empty()) { // if it's not a non-temporal action
            const int endStepID = header.size() + 1;
            const int startStepID = endStepID - 1;
            extraEventTwo = FFEvent(actID.first, startStepID, open.back().minDuration, open.back().maxDuration);
            extraEvent.pairWithStep = endStepID;
            eventTwoDefined = true;
            if (!TemporalAnalysis::canSkipToEnd(actID.first->getID())) {
                extraEventTwo.getEffects = false;
            }
            stepID = startStepID;
        } else {
            stepID = header.size() - 1;
        }

    } else if (actID.second == VAL::E_AT_END) {
        if (rawDebug) cout << "RAW end\n";
        if (rawDebug) cout << "Pairing with start at step " << header.size() << ", so activating end at " << header.size() + 1 << "\n";
        if (rawDebug) cout << *actID.first << " " << actID.first->getID() << endl;
        extraEvent = FFEvent(actID.first,open.back().minDuration,open.back().maxDuration);
        extraEventTwo = FFEvent(actID.first,header.size(),open.back().minDuration,open.back().maxDuration);
        eventOneDefined = true;
        eventTwoDefined = true;
    } else {
        extraEvent = FFEvent(actID.divisionID);
        eventOneDefined = true;
        stepID = header.size() - 1;
    }

    
    if (eventOneDefined) newHeader.push_back(extraEvent);
    if (eventTwoDefined) newHeader.push_back(extraEventTwo);
    return newHeader;
}

bool TimewindowsChecker::checkRelaxedPlanTimeWindows(list< FFEvent > header, list< std::pair< double, list< ActionSegment > > > relaxedPlan, MinimalState theState, list< StartEvent > startEventQueue)
{
    list<pair<int, FFEvent> > openTimewindows = openOneShotTimewindowActions(header,theState);
    for(list<pair<int, FFEvent> >::iterator otIt = openTimewindows.begin();otIt!=openTimewindows.end(); ++otIt){
        int idTWA = otIt->second.action->getID();
        bool foundAction = false;
        double timeActToPass;
        int actToPass;
        ActionSegment actSegToPass;
        for(list<pair<double,list<ActionSegment> > >::reverse_iterator rpIt = relaxedPlan.rbegin(); rpIt!=relaxedPlan.rend();++rpIt){
            double time = rpIt->first;
            list<ActionSegment> actions = rpIt->second;
            for(list<ActionSegment>::iterator acIt = actions.begin();acIt!=actions.end();++acIt){
                actToPass = acIt->first->getID();
                if(RPGBuilder::isDependentOnTimewindow(actToPass,idTWA)){
                    foundAction = true;
                    timeActToPass = time;
                    actSegToPass = *acIt;
                    break;
                }
            }
            if (foundAction)
                break;
        }
        if (!foundAction)
            continue;
        list<FFEvent> newEvents;
        TemporalConstraints cons = TemporalConstraints(*theState.temporalConstraints,2);
        list<StartEvent> open = startEventQueue;
        TimewindowsChecker::addTemporalConstraint(cons,header,otIt->first, actToPass);
        newEvents = TimewindowsChecker::addActionToHeader(header,open,actSegToPass);
        ParentData * parent = LPScheduler::prime(header, &cons, open);
        ChildData * child = parent->spawnChildData(open, header, newEvents, false, &cons, header.size()+1);
        if (!LPScheduler::checkTimewindow(child)){
            return false;
        }
    }
    return true;
}

bool TimewindowsChecker::heuristicCheck = false;
bool TimewindowsChecker::relaxedCheck = false;

};