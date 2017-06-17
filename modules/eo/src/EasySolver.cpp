/*
 <one line to give the program's name and a brief idea of what it does.>
 Copyright (C) 2015  <copyright holder> <email>
 
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


#include "EasySolver.h"
#include "ExternalSolver.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

#define DEBUG_MOD (0)
#define INFINITE_COST (100000)


//#define MAX_DOUBLE (numeric_limits<double>::max())


/**
 * Helper methods
 */

vector<string> splitString(string str)
{
    string buf; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream
    
    vector<string> tokens; // Create vector to hold our words
    
    while (ss >> buf){
        tokens.push_back(buf);
        
    }
    vector<string> toReturn; // Create vector to hold our words
    for (auto tt : tokens){
        string t = tt;
        if (t.substr(0,1)=="("){
            t = t.substr(1,t.length()-1);
        }
        if (t.substr(t.length()-1,1)==")"){
            t = t.substr(0,t.length()-1);
        }
        toReturn.push_back(t);
    }

    return toReturn;
}

double square(double base) {
    return base*base;
}

double pointPointDistance(vector2d p1, vector2d p2) {
    return std::sqrt(square(p1.x-p2.x)+square(p1.y-p2.y));
}

double pointLineDistance(vector2d point, vector2d linePoint, vector2d lineDirection) {
    return ((point.x-linePoint.x)*lineDirection.y - (point.y-linePoint.y)*lineDirection.x)
    / lineDirection.length();
}

double vectorAngle(vector2d first, vector2d second) {
    return std::acos((first*second)/(first.length()*second.length()));
}

double signedVectorAngle (vector2d first, vector2d second) {
    return std::acos(first.x/first.length()) - std::acos(second.x/second.length());
}

/**
 * maneuver calculates the minimal time needed for a ROLL-PITCH maneuver from scan position pScan to start position of Patch pPatch
 * ATTENTION: the yaw angle is already assumed to be correct
 */
pair<double,satellitePose> maneuver(double pitchAngle, double rollAngle, double yawAngle, vector2d pScan, vector2d pPatch, vector2d patchDirection, double orbitHeight, double angleVelocity) {
    // roll:
    if (DEBUG_MOD>=4) {cout << "consider time needed for rolling and pitching towards patch: " << pPatch << " from scan point " << pScan << endl;}
    
    double rollDist = pointLineDistance(pScan,pPatch,patchDirection);
    if (DEBUG_MOD>=4) {cout << "roll distance: " << rollDist << endl;}
    double roll = std::atan(rollDist/orbitHeight);
    if (DEBUG_MOD>=4) {cout << "target roll " << roll*(180/PI) << "° - current roll " << rollAngle*(180/PI) << "° = roll angle to slew: ";}
    double rollSlew(roll - rollAngle), t_roll(0);
    if (DEBUG_MOD>=4) {cout << rollSlew*(180/PI) << "°" << endl;}
    t_roll = std::abs(rollSlew/angleVelocity);
    if (DEBUG_MOD>=3) {cout << "slew time for roll maneuver: " << t_roll << endl;}
    
    double pitchDist = pointLineDistance(pPatch,pScan,vector2d(-patchDirection.y,patchDirection.x));
    if (DEBUG_MOD>=4) {cout << "pitch Distanz: " << pitchDist << endl;}
    double pitch = std::atan(pitchDist/std::sqrt(square(orbitHeight)+square(rollDist)));
    if (DEBUG_MOD>=4) {cout <<  "target pitch " << pitch*(180/PI) << "° - current pitch " << pitchAngle*(180/PI) << "° = pitch angle to slew: ";}
    double pitchSlew(pitch - pitchAngle), t_pitch(0);
    if (DEBUG_MOD>=4) {cout << pitchSlew*(180/PI) << "°" << endl;}
    t_pitch = std::abs(pitchSlew/angleVelocity);
    if (DEBUG_MOD>=3) {cout << "slew time for pitch maneuver: " << t_pitch << endl;}
    
    double t_max = std::max(t_roll, t_pitch);
    if (DEBUG_MOD>=3) {cout << "returning manoever time " << t_max << endl;}
    return pair<double,satellitePose>(t_max,satellitePose(pScan.x, pScan.y, yawAngle, roll, pitch));
}


extern "C" ExternalSolver* create_object(){
    return new EasySolver();
}

extern "C" void destroy_object(ExternalSolver *externalSolver){
    delete externalSolver;
}

EasySolver::EasySolver(){
    
}

EasySolver::~EasySolver(){
    
}

void EasySolver::loadSolver(string *parameters, int n){
    string param = parameters[0];
    char const *x[]={"t_scan","t_target","end_pose_reachable","x-pos","y-pos","yaw-angle","pitch-angle","roll-angle","total-cost"};
    char const *y[]={"is-patching","is-scanning","is-ignoring"};
    parseParameters(param);
    affected = list<string>(x,x+9);
    dependencies = list<string>(y,y+3);
}

map<string,double> EasySolver::callExternalSolver(map<string,double> initialState,bool isHeuristic){

    map<string, double> toReturn;
    map<string, double>::iterator iSIt = initialState.begin();
    map<string, double>::iterator isEnd = initialState.end();
    map<string, pair<string,string> > endPose;
    map<string, satellitePose> mapPose;
    double totalProbability;
    double expectedTime;
    bool isPatching = false;
    bool isScanning = false;
    bool isIgnoring = false;
    string sat;
    string patch;
    int t;
    //cout << "apply solver" << endl;
    for(;iSIt!=isEnd;++iSIt){

        string parameter = iSIt->first;
        double value = iSIt->second;

        vector<string> tokens = splitString(parameter);
        if (tokens[0]=="is-patching" && fabs(value-1) < 0.001  ){
            isPatching = true;
            patch = tokens[1];
            sat = tokens[2];
            if(DEBUG_MOD >= 5) cout << "--- module is targeting " << patch << " " << sat << endl;
            
        }else if (tokens[0]=="is-scanning" && fabs(value-1) < 0.001  ){
            isScanning = true;
            patch = tokens[1];
            sat = tokens[2];
            if(DEBUG_MOD >= 5) cout << "--- module is scanning " << patch << " " << sat << endl;
            
        }else if (tokens[0]=="is-ignoring" && fabs(value-1) < 0.001  ){
            isIgnoring = true;
            patch = tokens[1];
            if(DEBUG_MOD >= 5) cout << "--- module is ignoring " << patch << " " << endl;
        }else if (tokens[0]=="x-pos"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].x = value;
        }else if (tokens[0]=="y-pos"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].y = value;
        }else if (tokens[0]=="yaw-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].yaw = value;
        }else if (tokens[0]=="pitch-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].pitch = value;
        }else if (tokens[0]=="roll-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].roll = value;
        }else if (tokens[0]=="end_pose_reachable"){
            string namePatch = tokens[1];
            string nameSatellite = tokens[2];
            endPose.insert(make_pair(parameter,make_pair(namePatch,nameSatellite)));
        }
        /*
        for (auto p : mapPose){
            cout << p.first << " " << p.second;
        }*/

        /*
        for (string t : tokens){
            cout << "---" << t << "-";
        }
        cout << value<< endl;
         */
    }
    
    for (auto is : initialState){
        toReturn[is.first] = is.second;
    }
    
    // calculate modules
    

    if (isPatching){
        if(DEBUG_MOD >= 5) cout << "calculating effects target" << endl;
        targetEffects(toReturn, patch, sat, mapPose);
        double scanPossible = endPoseAfterScanning(toReturn, patch, sat, mapPose);
        for (auto ep : endPose){
            string nameFluent = ep.first;
            string np = ep.second.first;
            string ns = ep.second.second;
            toReturn[nameFluent]=0;
        }
        toReturn["(end_pose_reachable " + patch + " " + sat + ")"] = scanPossible;
    }

    
    if (isScanning){
        if(DEBUG_MOD >= 5) cout << "calculating effects scanning" << endl;
        scanEffects(toReturn, patch, sat, mapPose);
    }
    if (isIgnoring){
        if(DEBUG_MOD >= 5) cout << "calculating effects ignoring" << endl;
        toReturn["(total-cost)"] =  toReturn["(total-cost)"] + 10000000;

    }
    

    if(DEBUG_MOD >= 5)
        for (auto tr : toReturn){
            cout << "calling back : " << tr.first << " " << tr.second << endl;
        }

    return toReturn;// change this toReturn;
}

list<string> EasySolver::getParameters(){

    return affected;
}

list<string> EasySolver::getDependencies(){

    return dependencies;
}

void EasySolver::parseParameters(string parameters){
    //cout << "parsing parameters" << endl;
    string line;
    ifstream parametersFile(parameters.c_str());
    if (parametersFile.is_open()){
        while (getline(parametersFile,line)){
            const std::string s = line;
            std::regex rgx("\\(= \\((.*)\\) (.*)\\).*");
            std::smatch match;
            if(DEBUG_MOD >= 5) cout << "line: " << line << endl;

            if (std::regex_search(s.begin(), s.end(), match, rgx)){
                int i = 0;
                if(DEBUG_MOD >= 5) {
                    for (auto m : match){
                        cout << i << ": " << m << endl;
                        i++;
                    }
                }
                if (match.size()<3)
                    cerr << "error while parsing" << endl;
                else{
                    string head = match[1];
                    double value = atof(match.str(2).c_str());
                    mapFluents[head]=value;
                }
            }
        }
    }
    //cout << "found " << mapFluents.size() << endl;
    parseFluents();
}

void EasySolver::parseFluents(){
    for ( auto f : mapFluents){
        vector<string> tokens = splitString(f.first);
//        cout << "----- " << endl;
//        for(auto t : tokens){
//            cout << t << " ";
//        } cout << endl;
        if (tokens[0]=="x-entry"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].xEntry = f.second;
        }else if (tokens[0]=="y-entry"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].yEntry = f.second;
        }else if (tokens[0]=="x-exit"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].xExit = f.second;
        }else if (tokens[0]=="y-exit"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].yExit = f.second;
        }else if (tokens[0]=="scan-velocity"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].scanVelocity = f.second;
        }else if (tokens[0]=="x-pos"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].xPos = f.second;
        }else if (tokens[0]=="y-pos"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].yPos = f.second;
        }else if (tokens[0]=="x-entry-map"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].xEntry = f.second;
        }else if (tokens[0]=="y-entry-map"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].yEntry = f.second;
        }else if (tokens[0]=="x-exit-map"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].xExit = f.second;
        }else if (tokens[0]=="y-exit-map"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].yExit = f.second;
        }else if (tokens[0]=="overground-height"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].overgroundHeight = f.second;
        }else if (tokens[0]=="gr-velocity"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].grVelocity = f.second;
        }else if (tokens[0]=="angle-velocity"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].angleVelocity = f.second;
        }else if (tokens[0]=="max-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].maxAngle = f.second;
        }else if (tokens[0]=="yaw-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].yawAngle = f.second;
        }else if (tokens[0]=="pitch-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].pitchAngle = f.second;
        }else if (tokens[0]=="roll-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].rollAngle = f.second;
        }
        //cout << f.first << " " << f.second << endl;
    }
}

void EasySolver::scanEffects(map<string, double> & toReturn, string patch, string sat,map<string, satellitePose> mapPose){
    double xExit = mapPatches[patch].xExit;
    double yExit = mapPatches[patch].yExit;
    double xEntry = mapPatches[patch].xEntry;
    double yEntry = mapPatches[patch].yEntry;
    double vScan = mapSatellites[sat].scanVelocity;
    //cout << xExit << " " << xEntry << " " << yExit << " " << yEntry << " " << vScan << endl;
    //cout << std::sqrt(square(xExit - xEntry) + square(yExit - yEntry)) / vScan << endl;
    
    double tScan = std::sqrt(square(xExit - xEntry) + square(yExit - yEntry)) / vScan;
    toReturn["(t_scan " + patch + " " + sat + ")"] =  tScan;
    toReturn["(total-cost)"] =  toReturn["(total-cost)"] + tScan;
    double xSat = mapPose[sat].x;
    double ySat = mapPose[sat].y;
    double aYaw = mapPose[sat].yaw;
    double aPitch = mapPose[sat].pitch;
    double aRoll = mapPose[sat].roll;
    patchPose currentPose(patch, xSat, ySat, aYaw, aRoll, aPitch);
    satellitePose resultPose(-2,-2,-2,-2,-2);
    if (scanMap.find(currentPose) != scanMap.end()) {
        resultPose=scanMap[currentPose].endPose;
        if (DEBUG_MOD >= 1) cout << "Return satellite pose after scanning patch " << patch <<" from database: " << resultPose << endl;
    }else{
        endPoseAfterScanning(toReturn,patch,sat,mapPose);
        resultPose=scanMap[currentPose].endPose;
        if (DEBUG_MOD >= 1) cout << "Return satellite pose after scanning patch " << patch <<" from database: " << resultPose << endl;
    }
    if(DEBUG_MOD>=1) {cout << "Writing back " << resultPose << endl;}
    toReturn["(x-pos " + sat + ")"] =  resultPose.x;
    toReturn["(y-pos " + sat + ")"] =  resultPose.y;
    toReturn["(yaw-angle " + sat + ")"] =  resultPose.yaw;
    toReturn["(pitch-angle " + sat + ")"] =  resultPose.pitch;
    toReturn["(roll-angle " + sat + ")"] =  resultPose.roll;
}

void EasySolver::targetEffects(map<string, double> & toReturn, string patch, string sat,map<string, satellitePose>& mapPose){
    
    double tTarget = targetingTimeOfPatch(toReturn, patch, sat, mapPose);
    
    toReturn["(t_scan " + patch + " " + sat + ")"] =  tTarget;
    toReturn["(total-cost)"] =  toReturn["(total-cost)"] + tTarget;

    
    double xExit = mapPatches[patch].xExit;
    double yExit = mapPatches[patch].yExit;
    double xEntry = mapPatches[patch].xEntry;
    double yEntry = mapPatches[patch].yEntry;
    double vScan = mapSatellites[sat].scanVelocity;
    double xSat = mapPose[sat].x;
    double ySat = mapPose[sat].y;
    double aYaw = mapPose[sat].yaw;
    double aPitch = mapPose[sat].pitch;
    double aRoll = mapPose[sat].roll;
    patchPose currentPose(patch, xSat, ySat, aYaw, aRoll, aPitch);
    satellitePose resultPose(-2,-2,-2,-2,-2);
    if (approachMap.find(currentPose) != approachMap.end()) {
        resultPose=approachMap[currentPose].endPose;
        if (DEBUG_MOD >= 1) cout << "Return Patch approcach Pose from database: " << resultPose << endl;
    }
    if(DEBUG_MOD >= 1) {cout << "Writing back " << resultPose << endl;}
    toReturn["(x-pos " + sat + ")"] =  resultPose.x;
    toReturn["(y-pos " + sat + ")"] =  resultPose.y;
    toReturn["(yaw-angle " + sat + ")"] =  resultPose.yaw;
    toReturn["(pitch-angle " + sat + ")"] =  resultPose.pitch;
    toReturn["(roll-angle " + sat + ")"] =  resultPose.roll;
    mapPose[sat].x= resultPose.x;
    mapPose[sat].y= resultPose.y;
    mapPose[sat].yaw= resultPose.yaw;
    mapPose[sat].pitch= resultPose.pitch;
    mapPose[sat].roll= resultPose.roll;

}

double EasySolver::targetingTimeOfPatch(map<string, double> & toReturn, string patch, string sat,map<string, satellitePose> mapPose){
    double xEntryPatch(0), yEntryPatch(0), xExitPatch(0), yExitPatch(0), xSat(0), ySat(0), xEntrySat(0), yEntrySat(0),
    xExitSat(0), yExitSat(0), aYaw(0), aPitch(0), aRoll(0), aMax(0), angleVelocity(0), vSat(0), orbitHeight(0);
    xEntryPatch = mapPatches[patch].xEntry;
    yEntryPatch = mapPatches[patch].yEntry;
    xExitPatch = mapPatches[patch].xExit;
    yExitPatch = mapPatches[patch].yExit;
    xSat = mapPose[sat].x;
    ySat = mapPose[sat].y;
    xEntrySat = mapSatellites[sat].xEntry;
    yEntrySat = mapSatellites[sat].yEntry;
    xExitSat = mapSatellites[sat].xExit;
    yExitSat = mapSatellites[sat].yExit;
    aYaw = mapPose[sat].yaw;
    aPitch = mapPose[sat].pitch;
    aRoll = mapPose[sat].roll;
    angleVelocity = mapSatellites[sat].angleVelocity;
    vSat = mapSatellites[sat].grVelocity;
    aMax = mapSatellites[sat].maxAngle;
    orbitHeight = mapSatellites[sat].overgroundHeight;
    patchPose currentPose(patch, xSat, ySat, aYaw, aRoll, aPitch);
    if (approachMap.find(currentPose) != approachMap.end()) {
        approachTimeDatabase++;
        if (DEBUG_MOD >= 1) cout << "Return approach Pose from Database (#"<<approachTimeDatabase<<"): " << approachMap[currentPose].endPose << " after " << approachMap[currentPose].maneuverTime <<"s"<< endl;
        if (approachMap[currentPose].maneuverTime >= 0) return approachMap[currentPose].maneuverTime;
        if (approachMap[currentPose].maneuverTime == -1) return INFINITE_COST;
        cout << "... but no target_time found" << endl;
        //assert(false);
        
    } else {
        approachTimeFresh++;
        if (DEBUG_MOD >= 1) cout << "approach time not found in Database, calculating it now (#" << approachTimeFresh << ")" << endl;
    }
    
    /**
     * Start of Calculations
     */
    if (DEBUG_MOD>=4) {cout << "Begin Calculation... " <<endl;}
    vector2d pSatPos(xSat,ySat);
    vector2d pPatchFrom(xEntryPatch,yEntryPatch);
    vector2d pPatchTo(xExitPatch,yExitPatch);
    vector2d dPatch(pPatchTo-pPatchFrom);
    vector2d pSatEntry(xEntrySat,yEntrySat);
    vector2d pSatExit(xExitSat,yExitSat);
    vector2d dSat(pSatExit-pSatEntry); // direction vector of Satellite Ground track
    
    // YAW
    if (DEBUG_MOD>=4) {cout << "Target yaw angle: ";}
    double yaw = signedVectorAngle(dSat,dPatch);
    if (DEBUG_MOD>=4) {cout << yaw*(180/PI) <<"°"<<endl;}
    if (DEBUG_MOD>=3) {cout << "Target yaw angle " << yaw*(180/PI) << "° - current yaw " << aYaw*(180/PI) << "° = yaw angle to slew: ";}
    double yawSlew(yaw - aYaw), t_yaw(0);
    if (DEBUG_MOD>=3) {cout << yawSlew*(180/PI) << "°"<< endl;}
    if (DEBUG_MOD>=4) {cout << "Minimal slewing time: " <<endl;}
    t_yaw = std::abs(yawSlew/angleVelocity);
    if (DEBUG_MOD>=3) {cout << "t_min = t_yaw = " << t_yaw <<endl;}
    vector2d pEarly = pSatPos + (dSat.normalized() * (vSat * t_yaw));
    if (DEBUG_MOD>=4) {cout << "Groundtrack Position nach Yaw-Manöver: (" << pEarly.x << ", " << pEarly.y << ")" <<endl;}
    
    // angle yawed already, so use current pitch, current roll and target yaw
    pair<double,satellitePose> yawManeuver =maneuver(aPitch, aRoll, yaw, pEarly, pPatchFrom, dPatch, orbitHeight, angleVelocity);
    if (t_yaw >= yawManeuver.first) {
        if (DEBUG_MOD) {cout << "Returning targeting time: "<< t_yaw << endl;}
        storedResults myResult;
        myResult.maneuverTime = t_yaw;
        myResult.endPose = yawManeuver.second;
        if (DEBUG_MOD >= 1) cout << "Inserting into approachMap: " << currentPose << " with result " << myResult<<endl;
        approachMap.insert(pair<patchPose,storedResults>(currentPose,myResult));
        //assert (t_yaw >= 0);
        return t_yaw;
    }
    
    if (DEBUG_MOD>=3) {cout << "yaw time not dominating pitch or roll, continue search for scan point... "<< endl;}
    
    double t_min = t_yaw;
    
    double lineParameter = ((xEntryPatch - xEntrySat) * (yExitSat - yEntrySat)) + ((yEntryPatch - yEntrySat)*(xEntrySat-xExitSat));
    lineParameter /= (square (yExitSat - yEntrySat) + square(xEntrySat - xExitSat));
    vector2d pFoot = pPatchFrom + (vector2d((yExitSat- yEntrySat), (xEntrySat - xExitSat)) * (-1*lineParameter));
    
    if (DEBUG_MOD>=4) {cout << "perpendicular foot calculated as" << pFoot << endl;}
    
    double dFL = 		// distance from footpoint to latest possible scan point
    square(std::tan(aMax)*orbitHeight) - square(pointPointDistance(pFoot, pPatchFrom));
    if(dFL>=0)
    {dFL=std::sqrt(dFL);}
    else
    {
        if (DEBUG_MOD) {cout << "patch out of reach, RETURN -1" << endl;}
        storedResults myResult;
        myResult.maneuverTime = -1;
        if (DEBUG_MOD) cout << "Inserting into approachMap: " << currentPose << " with result " << myResult<<endl;
        approachMap.insert(pair<patchPose,storedResults>(currentPose,myResult));
        if(DEBUG_MOD >= 2) cout<< "--------------------------------------------------------------------------------" << endl;
        return INFINITE_COST;
    }
    //squaredDistancePatch_GroundTrackLine);
    vector2d pLast = pFoot + (dSat.normalized() * dFL);   // last possible Scan point
    //	   double xLast = xFootPoint + distanceFromFootpointToLatestPossibleScanPoint * ((xExitSat - xEntrySat) / std::sqrt(((xExitSat - xEntrySat)*(xExitSat - xEntrySat))+ ((yExitSat - yEntrySat)*(yExitSat - yEntrySat))));
    //	   double yLast = yFootPoint + distanceFromFootpointToLatestPossibleScanPoint * ((yExitSat - yEntrySat) / std::sqrt(((xExitSat - xEntrySat)*(xExitSat - xEntrySat))+ ((yExitSat - yEntrySat)*(yExitSat - yEntrySat))));
    if (DEBUG_MOD>=3) {cout << "last possible scan point: " << pLast << endl;}
    double t_last = pointPointDistance(pLast, pSatPos) / vSat;
    if (DEBUG_MOD>=3) {cout << "maximal slew time befor patch is out of range: " << t_last << endl;}
    if (t_last < t_min) {
        if (DEBUG_MOD) {cout << "patch not scannable any more, RETURN -1" << endl;}
        storedResults myResult;
        myResult.maneuverTime = -1;
        if (DEBUG_MOD) cout << "Inserting into approachMap: " << currentPose << " with result " << myResult<<endl;
        approachMap.insert(pair<patchPose,storedResults>(currentPose,myResult));
        if(DEBUG_MOD >= 2) cout<< "--------------------------------------------------------------------------------" << endl;
        return INFINITE_COST;
    }
    pair<double, satellitePose> midManeuver = maneuver(aPitch, aRoll, yawSlew, pLast, pPatchFrom, dPatch, orbitHeight, angleVelocity);
    if (DEBUG_MOD>=2) {cout << "maneuver time for slewing to pose at last possible scan point " << pLast << " = " << midManeuver.first << endl;}
    if (t_last < midManeuver.first) {
        if (DEBUG_MOD) {cout << "last scan point in range but not reachable anymore, RETURN -1" << endl;}
        storedResults myResult;
        myResult.maneuverTime = -1;
        myResult.endPose = midManeuver.second;
        if (DEBUG_MOD) cout << "Inserting into approachMap: " << currentPose << " with result " << myResult<<endl;
        approachMap.insert(pair<patchPose,storedResults>(currentPose,myResult));
        if(DEBUG_MOD >= 2) cout<< "--------------------------------------------------------------------------------" << endl;
        return INFINITE_COST;
    }
    // now mTime is a known "good" possibility
    satellitePose bestPose = midManeuver.second;
    for (int depth = 5; depth >= 0; --depth) {
        double testTime = (t_last + t_min)/2;
        vector2d middlePoint = pSatPos + (dSat.normalized() * (vSat * testTime));
        if (DEBUG_MOD>=4) {cout << "next iteration... )" << depth << ")"<< endl;}
        if (DEBUG_MOD>=4) {cout << "tMin " << t_min << " = " << (pSatPos + (dSat.normalized() * (vSat * t_min))) << endl;}
        if (DEBUG_MOD>=4) {cout << "tLast " << t_last << " = " << (pSatPos + (dSat.normalized() * (vSat * t_last))) << endl;}
        if (DEBUG_MOD>=3) {cout << "testing new scan point in the middle of the interval: " << middlePoint << endl;}
        midManeuver = maneuver(aPitch, aRoll, yawSlew, middlePoint, pPatchFrom, dPatch, orbitHeight, angleVelocity);
        if (midManeuver.first > testTime) {
            if (DEBUG_MOD>=3) {cout << "slew Time to middle point : " << midManeuver.first << " to long, need more time (time to middle=" << testTime << ")" << endl;}
            t_min = testTime;
        }  else {
            if (DEBUG_MOD>=3) {cout << "slew Time suffices : " << midManeuver.first << " test time was " << testTime << endl;}
            t_last = testTime;
            pLast = middlePoint;
            bestPose = midManeuver.second;
        }
    }
    if (DEBUG_MOD) {cout << "Returning: " << t_last << endl;}
    storedResults myResult;
    myResult.maneuverTime = t_last;
    myResult.endPose = bestPose;
    if (DEBUG_MOD) cout << "Inserting into approachMap: " << currentPose << " with result " << myResult<<endl;
    approachMap.insert(pair<patchPose,storedResults>(currentPose,myResult));
    if(DEBUG_MOD >= 2) cout<< "--------------------------------------------------------------------------------" << endl;
    //assert(t_last > 0);
    return t_last;
}

double EasySolver::endPoseAfterScanning(map<string, double> & toReturn, string patch, string sat,map<string, satellitePose> mapPose)
{
    if(DEBUG_MOD >= 2) cout<< "********************************************************************************\n**********  ";
    if(DEBUG_MOD) cout<<"Module Call: endPoseAfterScanning ";
    if(DEBUG_MOD >= 2) cout<< "                        **********\n********************************************************************************" << endl;
    modulecalls++;
    if(DEBUG_MOD >=3) cout<<"Module Calls so far: "<< modulecalls << endl;
    if (false) {
        scanTimeHeuristic++;
        if (DEBUG_MOD >=3) {cout << "Starting calculation (#"<< scanTimeHeuristic<<") in HEURISTIC Mode" << endl;}
    } else {
        scanTimeCalls++;
        if(DEBUG_MOD >= 3) cout << "PRECISE (non heuristic) cost calculation (#" << scanTimeCalls << ")"<<endl;
    }
    double xExit = mapPatches[patch].xExit;
    double yExit = mapPatches[patch].yExit;
    double xEntry = mapPatches[patch].xEntry;
    double yEntry = mapPatches[patch].yEntry;
    double vScan = mapSatellites[sat].scanVelocity;
    double xEntryPatch(0), yEntryPatch(0), xExitPatch(0), yExitPatch(0), xSat(0), ySat(0), xEntrySat(0), yEntrySat(0),
    xExitSat(0), yExitSat(0), aYaw(0), aPitch(0), aRoll(0), aMax(0), angleVelocity(0), vSat(0), orbitHeight(0);
    xEntryPatch = mapPatches[patch].xEntry;
    yEntryPatch = mapPatches[patch].yEntry;
    xExitPatch = mapPatches[patch].xExit;
    yExitPatch = mapPatches[patch].yExit;
    xSat = mapPose[sat].x;
    ySat = mapPose[sat].y;
    xEntrySat = mapSatellites[sat].xEntry;
    yEntrySat = mapSatellites[sat].yEntry;
    xExitSat = mapSatellites[sat].xExit;
    yExitSat = mapSatellites[sat].yExit;
    aYaw = mapPose[sat].yaw;
    aPitch = mapPose[sat].pitch;
    aRoll = mapPose[sat].roll;
    angleVelocity = mapSatellites[sat].angleVelocity;
    vSat = mapSatellites[sat].grVelocity;
    aMax = mapSatellites[sat].maxAngle;
    orbitHeight = mapSatellites[sat].overgroundHeight;
    patchPose currentPose(patch, xSat, ySat, aYaw, aRoll, aPitch);
    if (scanMap.find(currentPose) != scanMap.end()) {
        if (DEBUG_MOD) cout << " patch/pose already in database: " << scanMap[currentPose].endPose << " after " << scanMap[currentPose].maneuverTime <<"s"<< endl;
        if ((scanMap[currentPose].maneuverTime == -1) || (std::abs(scanMap[currentPose].endPose.pitch)>aMax) || (std::abs(scanMap[currentPose].endPose.roll)>aMax)) {
            if (DEBUG_MOD) cout << "BAD, return infty" << endl;
            return 0;
        }
    }
    vector2d satPos(xSat,ySat);
    vector2d earthExit(xExitSat, yExitSat);
    vector2d earthEntry(xEntrySat, yEntrySat);
    vector2d groundDir = (earthExit - earthEntry);
    groundDir.normalize();
    vector2d patchExit(xExitPatch, yExitPatch);
    vector2d patchEntry(xEntryPatch, yEntryPatch);
    vector2d dPatch = (patchExit-patchEntry);
    double tScan = dPatch.length() / vScan;
    vector2d endPos = satPos + (groundDir*(tScan*vSat)); // in the time needed for scanning the patch, the satellite moves forward on the groundtrack with its groundtrack speed vSat
    if(DEBUG_MOD>=2) cout << "Ending scan maneuver at " << endPos << endl;
    
    // YAW
    if (DEBUG_MOD>=4) {cout << "Target yaw angle: ";}
    double yaw = signedVectorAngle(groundDir,dPatch);
    if (DEBUG_MOD>=4) {cout << yaw*(180/PI) <<"°"<<endl;}
    if (DEBUG_MOD>=3) {cout << "target Yaw " << yaw*(180/PI) << "° - current yaw " << aYaw*(180/PI) << "° = yaw angle to slew: ";}
    double yawSlew(yaw - aYaw);
    if (DEBUG_MOD>=3) {cout << yawSlew*(180/PI) << "°"<< endl;}
    
    pair<double,satellitePose> scanManeuver = maneuver(aPitch, aRoll, yaw, endPos, patchExit, dPatch, orbitHeight, angleVelocity);
    
    if (DEBUG_MOD) {cout << "Post-scan pose: "<< scanManeuver.second << endl;}
    storedResults myResult;
    myResult.maneuverTime = scanManeuver.first;
    myResult.endPose = scanManeuver.second;
    
    if (DEBUG_MOD) cout << "Scan slew time " << myResult.maneuverTime << " while the time available for scanning is " << tScan << endl;
    if (DEBUG_MOD) cout << "Inserting into scanMap: " << currentPose << " with result " << myResult<<endl;
    scanMap.insert(pair<patchPose,storedResults>(currentPose,myResult));
    if ((myResult.maneuverTime <= tScan) && (std::abs(myResult.endPose.pitch)<aMax) &&(std::abs(myResult.endPose.roll)<aMax)) {
        if (DEBUG_MOD) cout << "good,  return true = 1" << endl;
        return 1;
    }
    else
    {
        if (DEBUG_MOD) cout << "BAD, return infty" << endl;
        return 0;
    }
    
}


