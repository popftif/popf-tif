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


#include "DynamicSolver.h"
#include "ExternalSolver.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <iostream>
#include <deque>
#include <set>
#include <algorithm>
#include <sys/time.h>
#include <assert.h>
#include <limits>
#include <regex>


using namespace std;

#define DEBUG_MOD (0)
#define INFINITE_COST (100000000)
#define NESTING_DEPTH (10)
#define MAX_DOUBLE (100000000) //numeric_limits<double>::max())


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

double pointPointDistance(vector3d p1, vector3d p2) {
    return std::sqrt(square(p1.x-p2.x)+square(p1.y-p2.y)+square(p1.z-p2.z));
}

void calculateExtremeScanPositions(patchInfo& patinf, string satname, double maxpitch, double satvelo) {
    // the planning problem preselects patches that are within feasible
    // roll-bouds. The latest possible scan position can be
    // conservatively estimated by assuming maximal pitch.  there are
    // two possible "last" positions depending if entry or exit of the
    // patch are more constraining
    if (DEBUG_MOD >= 3) cout<< "Calculating the Last scan position for patch " << patinf.name << " scanned by satellite " << satname << endl;
    assert(!patinf.lastXknown);
    if (patinf.belongstoknown)
        assert(satname==patinf.belongsto);
    else {
        patinf.setScanningSatellite(satname);
    }
    //  if(DEBUG_MOD >=3) cout << "patch info:" << patinf << endl;
    
    double entrylastX = patinf.entry.x + std::sqrt(square(std::tan(maxpitch) * patinf.entry.z)- square(patinf.entry.y));
    if(DEBUG_MOD >= 4) cout<< "Calculating entry Last: " << patinf.entry.x << " + sqrt((tan(" << maxpitch << ") * " << patinf.entry.z << ")² - "<<patinf.entry.y<< "²) = " << entrylastX << endl;
    
    double exitlastX = patinf.exit.x + std::sqrt(square(std::tan(maxpitch) * patinf.exit.z)- square(patinf.exit.y));
    assert(patinf.scandurationknown);
    exitlastX -= satvelo * patinf.scanduration;// ((patinf.exit-patinf.entry).length()/scanvelo);
    if(DEBUG_MOD >= 4) cout<< "Calculating exit Last: " << patinf.exit.x << " + sqrt((tan(" << maxpitch << ") * " << patinf.exit.z << ")² - "<<patinf.exit.y<< "²) - (" << satvelo << " * " << patinf.scanduration <<") = " << exitlastX << endl;
    
    double lastX = min(entrylastX, exitlastX);
    if(DEBUG_MOD >= 3) cout<< "Last scan X position of satellite = min (" << entrylastX << ", " << exitlastX << ") = " << lastX << endl;
    patinf.setlastX(lastX);
    
    double entryfirstX = patinf.entry.x - std::sqrt(square(std::tan(maxpitch) * patinf.entry.z)- square(patinf.entry.y));
    if(DEBUG_MOD >= 4) cout<< "Calculating entry First: " << patinf.entry.x << " - sqrt((tan(" << maxpitch <<") * " << patinf.entry.z << ")² - "<<patinf.entry.y<<"²) * "  << " = " << entryfirstX << endl;
    double exitfirstX = patinf.exit.x - std::sqrt(square(std::tan(maxpitch) * patinf.exit.z)- square(patinf.exit.y));
    exitfirstX -= satvelo * patinf.scanduration;
    if(DEBUG_MOD >= 4) cout<< "Calculating exit First: " << patinf.exit.x << " - sqrt((tan(" << maxpitch <<") * " << patinf.exit.z << ")² - "<<patinf.exit.y<<"²) - (" << satvelo << " * " << patinf.scanduration <<") = " << exitfirstX << endl;
    
    double firstX = max(entryfirstX, exitfirstX);
    if(DEBUG_MOD >= 3) cout<< "first scan X position of satellite = max (" << entryfirstX << ", " << exitfirstX << ") = " << firstX << endl;
    patinf.setfirstX(firstX);
    
}

bool calcManeuverParameters(double ang0, double angEnd, double omega0, double omegaEnd, double angAccMax, double deltaT) {
    //      function [ acc1,acc2,ts, isFeasible] = calcManeuverParameters( ang0,...
    //                                                         angEnd,...
    //                                                         omega0,...
    //                                                         omegaEnd,...
    //                                                         angAccMax,...
    //                                                         dt )
    //      % Calculate delta-angle and delta-angular-rate
    
    double dAng = angEnd-ang0;
    double dOmega  = omegaEnd-omega0;
    
    //      % Begin with maximum angular acceleration
    double acc1= angAccMax;
    
    //      % Calculate switching time
    
    double ts = (dAng - (0.5*dOmega*deltaT) - (omega0*deltaT))/((0.5 * acc1 * deltaT) - (0.5 * dOmega));
    
    //      % If switching time negative, acc1 has the wrong sign
    
    if (ts<0) {
        acc1 = -angAccMax;
        ts = (dAng - (0.5*dOmega*deltaT) - (omega0*deltaT))/((0.5 * acc1 * deltaT) - (0.5 * dOmega));
    }
    
    if(DEBUG_MOD >= 4) cout << "ts:\t" << ts;
    //	% calculate angular acceleration after switching time
    
    double	acc2 = (dOmega - (acc1*ts))/(deltaT-ts);
    
    if (std::abs(acc2) > angAccMax || ts>deltaT) {
        if(DEBUG_MOD >=2) cout << "maximum angular acceleration or ts exceeded: slew impossible" << endl;
        return false;
    }
    else
        return true;
    
}

// maneuver tests, if a maneuver from "fromPose" to "toPose" is possible
bool maneuver(satelliteState fromPose, satelliteState toPose, double angAccMaxN, double deltaT) {
    pair<satelliteState,satelliteState> fromTo = pair<satelliteState,satelliteState>(fromPose,toPose);
    if (maneuverDatabase.find(fromTo) != maneuverDatabase.end()) {
        maneuverDatabaseLookup++;
        if(DEBUG_MOD >= 2) cout << "Maneuver already in Database (lookup # " << maneuverDatabaseLookup << "), maneuver is";
        bool maneuverPossible = maneuverDatabase[pair<satelliteState,satelliteState>(fromPose,toPose)];
        if (maneuverPossible) {
            //cout << " possible" <<endl;
            return true;
        }
        else {
            //cout << " impossible"<<endl;
            return false;
        }
    } else {
        if(DEBUG_MOD >=3) cout << "Calculate feasibility of maneuver from " << endl << fromPose << endl << "to" << endl << toPose << endl;
        if(DEBUG_MOD >=3) cout << "Time available: " << deltaT << "\t Maximal angular acceleration: " << angAccMaxN << endl;
        bool yawpossible = calcManeuverParameters(fromPose.yaw,toPose.yaw,fromPose.yawRateN,toPose.yawRateN,angAccMaxN, deltaT);
        if(DEBUG_MOD >=3) cout << " -> yawpossible? \t" << (yawpossible?"[X] ":"[ ] ") <<endl;
        bool pitchpossible = calcManeuverParameters(fromPose.pitch,toPose.pitch,fromPose.pitchRateN,toPose.pitchRateN,angAccMaxN, deltaT);
        if(DEBUG_MOD >=3) cout << " -> pitchpossible? \t" << (pitchpossible?"[X] ":"[ ] ") <<endl;
        bool rollpossible = calcManeuverParameters(fromPose.roll,toPose.roll,fromPose.rollRateN,toPose.rollRateN,angAccMaxN, deltaT);
        if(DEBUG_MOD >=3) cout << " -> rollpossible? \t" << (rollpossible?"[X] ":"[ ] ") <<endl;
        bool possible = (yawpossible && pitchpossible && rollpossible);
        maneuverDatabaseInsert++;
        if(DEBUG_MOD >= 2) cout << "Storing "<< (possible?"":"im") <<"possible Maneuver into Database (insert # " << maneuverDatabaseInsert
            << ")" <<endl;
        maneuverDatabase.insert(pair<pair<satelliteState,satelliteState>,bool>(fromTo,possible));
        return possible;
        
    }
}

matrix3d dcm_eulerAngles312(vector3d rollPitchYaw) {
    matrix3d yawTurn= matrix3d(std::cos(-rollPitchYaw.z), -std::sin(-rollPitchYaw.z), 0,
                               std::sin(-rollPitchYaw.z),std::cos(-rollPitchYaw.z),0,
                               0,0,1);
    matrix3d rollTurn = matrix3d(1, 0, 0,
                                 0, std::cos(-rollPitchYaw.x), -std::sin(-rollPitchYaw.x),
                                 0, std::sin(-rollPitchYaw.x), std::cos(-rollPitchYaw.x));
    matrix3d pitchTurn = matrix3d(std::cos(-rollPitchYaw.y), 0, std::sin(-rollPitchYaw.y),
                                  0, 1, 0,
                                  -std::sin(-rollPitchYaw.y), 0, std::cos(-rollPitchYaw.y));
    return (pitchTurn * rollTurn) * yawTurn;
}

/**
 * Calculates the satellite's state when entering or exiting a patch
 */
satelliteState getSatState(satPosAndPatch spap, double vSatSub) {
    if (satPoseDatabase.find(spap) != satPoseDatabase.end()) {
        satPoseDatabaseLookup++;
        if (DEBUG_MOD >=4) cout << "This is lookup # " << satPoseDatabaseLookup << " in the satPoseDatabase" << endl;
        if (DEBUG_MOD >=2) cout << "Returning state " << satPoseDatabase[spap] << endl;
        return satPoseDatabase[spap];
    } else {
        if (DEBUG_MOD >=3) cout << "SatPose for patch >" << spap.patchName << "< from satellite Position >" <<spap.x <<" ("
            <<(spap.entry?"ENTRY":"EXIT")<<") not found in satPoseDatabase.\nCalculating it now...";
        satPoseDatabaseInsert++;
        if (DEBUG_MOD >=4) cout << "(insert # " <<satPoseDatabaseInsert << ")";
        if (DEBUG_MOD >=3) cout	<< endl;
        
        vector3d orbPos_EP = vector3d(spap.x, 0.0, 0.0);
        if (DEBUG_MOD >=4) cout << "orbPos_EP:\t" << orbPos_EP << endl;
        
        assert(patchMap.find(spap.patchName) != patchMap.end());
        patchInfo pinfo = patchMap[spap.patchName];
        if (DEBUG_MOD >=4) {cout << "patchInfo from patchMap:"<< endl; pinfo.print();}
        assert(pinfo.scandurationknown);
        
        vector3d patchCoord_EP;
        if (spap.entry)
            patchCoord_EP = pinfo.entry;
        else
            patchCoord_EP = pinfo.exit;
        
        if (DEBUG_MOD >=4) cout << "patchCoord_EP:\t" << patchCoord_EP << endl;
        
        vector3d patchDir_EP = pinfo.exit - pinfo.entry;
        if (DEBUG_MOD >=4) cout << "patchDir_EP:\t" << patchDir_EP << endl;
        
        //    Get Line Of Sight in Earth fixed Planning Coordinate Frame
        vector3d LoS_EP     = patchCoord_EP-orbPos_EP;
        if (DEBUG_MOD >=4) cout << "LoS_EP:\t\t" << LoS_EP << endl;
        
        //    Calculate yaw angle
        
        double yaw = std::atan(patchDir_EP.y/patchDir_EP.x);
        if (DEBUG_MOD >=4) cout << "yaw:\t\t" << yaw << endl;
        
        //    %Calculate Line of Sight in auxiliary frame (yawed)
        
        vector3d LoS_Yawed  = dcm_eulerAngles312(vector3d(0,0,yaw))*LoS_EP;
        if (DEBUG_MOD >=4) cout << "LoS_Yawed:\t" << LoS_Yawed << endl;
        
        
        //    %Get roll and pitch angles from Line of Sight components in aux. frame.
        
        double     roll       = std::atan(-LoS_Yawed.y/patchCoord_EP.z);
        if (DEBUG_MOD >=4) cout << "roll:\t\t" << roll << endl;
        //
        double     pitch      = std::atan( LoS_Yawed.x/std::sqrt((square(patchCoord_EP.z)+square(LoS_Yawed.y))));
        if (DEBUG_MOD >=4) cout << "pitch:\t\t" << pitch << endl;
        
        //    %Calculate compensation velocity in EP frame
        assert(pinfo.scanvelocityknown);
        vector3d patchScanVel_EP = patchDir_EP.normalized() * pinfo.scanvelocity;
        if (DEBUG_MOD >=4) cout << "patchScanVel_EP:\t" << patchScanVel_EP << endl;
        
        
        vector3d compensationVelocity_EP = patchScanVel_EP-vector3d(vSatSub,0,0);
        if (DEBUG_MOD >=4) cout << "compensationVelocity_EP:\t" << compensationVelocity_EP << endl;
        
        //      %Calculate compensation velocity in body frame
        
        vector3d compensationVelocity_B = dcm_eulerAngles312(vector3d(roll,pitch,yaw)) *compensationVelocity_EP;
        if (DEBUG_MOD >=4) cout << "compensationVelocity_B:\t" << compensationVelocity_B << endl;
        
        //      %Calculate lenghth of los
        double lengthLos = (orbPos_EP-patchCoord_EP).length();
        if (DEBUG_MOD >=4) cout << "lengthLos:\t" << lengthLos << endl;
        
        matrix3d inverse = dcm_eulerAngles312(vector3d(roll,pitch,yaw)).inverse();
        if (DEBUG_MOD >=4) cout << "inverse:\n" << inverse << endl;
        
        //      %Calculate angular rate in body frame and transform into EP frame
        vector3d	omega_EP = inverse *
        vector3d(-compensationVelocity_B.y/lengthLos,
                 compensationVelocity_B.x/lengthLos,
                 0);
        if (DEBUG_MOD >=4) cout << "omega_EP:\t" << omega_EP << endl;
        
        satelliteState newPose(spap.x, roll, pitch, yaw, omega_EP.x, omega_EP.y, omega_EP.z);
        satPoseDatabase.insert(pair<satPosAndPatch,satelliteState>(spap,newPose));
        return satPoseDatabase[spap];
    }
}

satelliteState getSatState(double x, string patchName, bool entryPose, double vsat) {
    return getSatState(satPosAndPatch(x, patchName,entryPose), vsat);
}

/**
 * checks if position, maximal angles and maximal rates of satellite are within bounds
 */
bool stateCheck(satelliteState pose, satelliteInfo info) {
    if(pose.x > info.xHorizon) {
        if (DEBUG_MOD >= 4) cout << "scan Pose exceeds horizon ("<< pose.x <<" > "<< info.xHorizon<<")-> stateCheck failed" << endl;
        return false;
    }
    if(std::abs(pose.roll) > info.rollMaxN) {
        if (DEBUG_MOD >= 4) cout << "roll angle exceeds rollMax (|"<< pose.roll <<"| > "<< info.rollMaxN << ")-> stateCheck failed" << endl;
        return false;
    }
    if(std::abs(pose.pitch) > info.pitchMaxN) {
        if (DEBUG_MOD >= 4) cout << "pitch angle exceeds pitchMax (|"<< pose.pitch <<"| > "<< info.pitchMaxN << ")-> stateCheck failed" << endl;
        return false;
    }
    if(std::abs(pose.rollRateN) > info.angRateXmaxN) {
        if (DEBUG_MOD >= 4) cout << "roll rotation (x) exceeds maximum (|"<< pose.rollRateN <<"| > "<< info.angRateXmaxN << ")-> stateCheck failed" << endl;
        return false;
    }
    if(std::abs(pose.pitchRateN) > info.angRateYmaxN) {
        if (DEBUG_MOD >= 4) cout << "pitch rotation (y) exceeds maximum (|"<< pose.pitchRateN <<"| > "<< info.angRateYmaxN << ")-> stateCheck failed" << endl;
        return false;
    }
    if(std::abs(pose.yawRateN) > info.angRateZmaxN) {
        if (DEBUG_MOD >= 4) cout << "yaw rotation (z) exceeds maximum (|"<< pose.yawRateN <<"| > "<< info.angRateZmaxN << ")-> stateCheck failed" << endl;
        return false;
    }
    if (DEBUG_MOD >= 4) cout << "all constraints within bounds -> stateCheck succeeded" << endl;
    return true;
}



extern "C" ExternalSolver* create_object(){
    return new DynamicSolver();
}

extern "C" void destroy_object(ExternalSolver *externalSolver){
    delete externalSolver;
}

DynamicSolver::DynamicSolver(){
    
}

DynamicSolver::~DynamicSolver(){
    
}

void DynamicSolver::loadSolver(string *parameters, int n){
    string param = parameters[0];
    char const *x[]={"t_scan","t_target","end_pose_reachable","x-pos","yaw-angle","pitch-angle","roll-angle","yaw-rate","pitch-rate","roll-rate", "total-cost"};
    char const *y[]={"is-patching","is-scanning","is-ignoring"};
    parseParameters(param);
    affected = list<string>(x,x+11);
    dependencies = list<string>(y,y+3);
}

map<string,double> DynamicSolver::callExternalSolver(map<string,double> initialState,bool isHeuristic){

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
    string osite;
    int t;
    //cout << "apply solver" << endl;
    for(;iSIt!=isEnd;++iSIt){

        string parameter = iSIt->first;
        double value = iSIt->second;

        vector<string> tokens = splitString(parameter);
        if (tokens[0]=="is-patching" && fabs(value-1) < 0.001){
            isPatching = true;
            patch = tokens[1];
            sat = tokens[2];
            osite = tokens[3];
            if(DEBUG_MOD >= 5) cout << "--- module is targeting " << patch << " " << sat << endl;
            
        }else if (tokens[0]=="is-scanning" && fabs(value-1) < 0.001){
            isScanning = true;
            patch = tokens[1];
            sat = tokens[2];
            osite = tokens[3];
            if(DEBUG_MOD >= 5) cout << "--- module is scanning " << patch << " " << sat << endl;
            
        }else if (tokens[0]=="is-ignoring" && fabs(value-1) < 0.001){
            isIgnoring = true;
            osite = tokens[1];
            if(DEBUG_MOD >= 5) cout << "--- module is ignoring " << osite << " " << endl;
        }else if (tokens[0]=="x-pos"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].x = value;
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
        }else if (tokens[0]=="yaw-rate"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].yawRate = value;
        }else if (tokens[0]=="pitch-rate"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].pitchRate = value;
        }else if (tokens[0]=="roll-rate"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satellitePose newSatellite;
                mapPose[nameSatellite] = newSatellite;
            }
            mapPose[nameSatellite].rollRate = value;
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
        targetEffects(toReturn, patch, sat, osite, mapPose);
        map<string, double> emptyMap;
        scanEffects(emptyMap, patch, sat, osite, mapPose);
        double scanPossible = endPoseAfterScanning(toReturn, patch, sat, osite, mapPose);
        for (auto ep : endPose){
            string nameFluent = ep.first;
            string np = ep.second.first;
            string ns = ep.second.second;
            toReturn[nameFluent]=0;
        }
        toReturn["(end_pose_reachable " + patch + " " + sat + " " + osite +")"] = scanPossible;
    }

    
    if (isScanning){
        if(DEBUG_MOD >= 5) cout << "calculating effects scanning" << endl;
        scanEffects(toReturn, patch, sat, osite, mapPose);
    }
    if (isIgnoring){
        if(DEBUG_MOD >= 5) cout << "calculating effects ignoring" << endl;
        toReturn["(total-cost)"] =  toReturn["(total-cost)"] + 100000;

    }
    

    if(DEBUG_MOD >= 5)
        for (auto tr : toReturn){
            cout << "calling back : " << tr.first << " " << tr.second << endl;
        }

    return toReturn;// change this toReturn;
}

list<string> DynamicSolver::getParameters(){

    return affected;
}

list<string> DynamicSolver::getDependencies(){

    return dependencies;
}

void DynamicSolver::parseParameters(string parameters){
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
            
            std::regex rgxB("(\\(belongsto ([^ ]+) ([^ ]+)\\))");
            std::smatch matchB;
            if (std::regex_search(s.begin(), s.end(), matchB, rgxB)){
                int i = 0;
                if(DEBUG_MOD >= 5) {
                    for (auto m : matchB){
                        cout << i << ": " << m << endl;
                        i++;
                    }
                }
                if (matchB.size()<4)
                    cerr << "error while parsing" << endl;
                else{
                    mapBelongs[matchB[2]]=matchB[3];
                }
            }

        }
    }
    //cout << "found " << mapFluents.size() << endl;
    parseFluents();
}

void DynamicSolver::parseFluents(){
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
            mapPatches[namePatch].entry.x = f.second;
            mapPatches[namePatch].name = namePatch;
            mapPatches[namePatch].belongsto = mapBelongs[namePatch];
            mapPatches[namePatch].belongstoknown = true;
            
        }else if (tokens[0]=="y-entry"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].entry.y = f.second;
        }else if (tokens[0]=="z-entry"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].entry.z = f.second;
        }else if (tokens[0]=="x-exit"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].exit.x = f.second;
        }else if (tokens[0]=="y-exit"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].exit.y = f.second;
        }else if (tokens[0]=="z-exit"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].exit.z = f.second;
        }else if (tokens[0]=="scan-velocity"){
            string namePatch = tokens[1];
            if(mapPatches.find(namePatch)==mapPatches.end()){
                patchInfo newPatch;
                mapPatches[namePatch] = newPatch;
            }
            mapPatches[namePatch].scanvelocity = f.second;
            mapPatches[namePatch].scanvelocityknown = true;
        }else if (tokens[0]=="x-pos"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].xPos = f.second;
            mapSatellites[nameSatellite].name = nameSatellite;
        }else if (tokens[0]=="x-horizon"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].xHorizon = f.second;
        }else if (tokens[0]=="roll-max-N"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].rollMaxN = f.second;
        }else if (tokens[0]=="pitch-max-N"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].pitchMaxN = f.second;
        }else if (tokens[0]=="ang-rate-x-max-N"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].angRateXmaxN = f.second;
        }else if (tokens[0]=="ang-rate-y-max-N"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].angRateYmaxN = f.second;
        }else if (tokens[0]=="ang-rate-z-max-N"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].angRateZmaxN = f.second;
        }else if (tokens[0]=="ang-acc-max-N"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].angAccMaxN = f.second;
        }else if (tokens[0]=="roll-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].roll = f.second;
        }else if (tokens[0]=="pitch-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].pitch = f.second;
        }else if (tokens[0]=="yaw-angle"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].yaw = f.second;
        }else if (tokens[0]=="roll-rate"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].rollRate = f.second;
        }else if (tokens[0]=="pitch-rate"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].pitchRate = f.second;
        }else if (tokens[0]=="yaw-rate"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].yawRate = f.second;
        }else if (tokens[0]=="subTrace-velocity"){
            string nameSatellite = tokens[1];
            if(mapSatellites.find(nameSatellite)==mapSatellites.end()){
                satelliteInfo newSatellite;
                mapSatellites[nameSatellite] = newSatellite;
            }
            mapSatellites[nameSatellite].vSubT = f.second;
        }
        //cout << f.first << " " << f.second << endl;
    }
}
double DynamicSolver::scanTimeOfPatch(map<string, double> & toReturn, string patchName, string satName, string osite, map<string, satellitePose> mapPose){

    patchInfo pat;
    satelliteInfo sat;
    bool fetchSuccess =fetchWorldState(patchName,satName,osite,mapPose,pat,sat);
    assert(fetchSuccess);
    
    if(DEBUG_MOD >= 4) cout << "Calculating scanvelocity in detail: " << endl;
    if(DEBUG_MOD >= 4) cout << "pat.exit: " << pat.exit << endl;
    if(DEBUG_MOD >= 4) cout << "pat.entry: " << pat.entry << endl;
    
    double scanduration = std::sqrt(square(pat.exit.x - pat.entry.x) + square(pat.exit.y - pat.entry.y) + square(pat.exit.z-pat.entry.z));
    if(DEBUG_MOD >= 4) cout << "root : " << scanduration << endl;
    
    scanduration /= pat.scanvelocity;
    if(DEBUG_MOD >= 4) cout << "Calculated scan velocity : " << scanduration << endl;
    
    if (patchMap.find(pat.name) == patchMap.end()) {
        patchMapInsert++;
        if(DEBUG_MOD >= 2) cout << "Inserting new patch into database (insert #" << patchMapInsert << ")" << endl;
        patchMap.insert(pair<string,patchInfo>(pat.name,pat));
    }
    patchMap[pat.name].setScanduration(scanduration);
    patchMap[pat.name].setScanningSatellite(sat.name);
    if (DEBUG_MOD >= 2) cout << "Inserting into patchMap: " << pat.name << " with duration " << scanduration <<endl;
    
    if(DEBUG_MOD >= 2) cout<< "Calculation of scanTimeOfPatch yields " << endl;
    if(DEBUG_MOD == 1) cout << " = ";
    if(DEBUG_MOD) cout << scanduration <<endl;
    if(DEBUG_MOD >= 2) cout<< "--------------------------------------------------------------------------------" << endl;
    if (scanduration<=0) scanduration = 1;
    return scanduration;
}

void DynamicSolver::scanEffects(map<string, double> & toReturn, string patch, string satName, string osite, map<string, satellitePose> mapPose){
    
    double tScan = scanTimeOfPatch(toReturn, patch, satName, osite, mapPose);
    toReturn["(t_scan " + patch + " " + satName + " " + osite +")"] =  tScan;
    toReturn["(total-cost)"] =  toReturn["(total-cost)"] + tScan;

    if(DEBUG_MOD >= 2) cout<< "################################################################################\n##########  ";
    if(DEBUG_MOD) cout<<"Module Call: scanEffects ";
    if(DEBUG_MOD >= 2) cout<< "                                 ##########\n################################################################################" << endl;
    modulecalls++;
    if(DEBUG_MOD >=3) cout<<"Module Calls so far: "<< modulecalls << endl;
    
    
    patchInfo pat;
    satelliteInfo sat;
    bool fetchSuccess =fetchWorldState(patch,satName,osite,mapPose,pat,sat);
    if(DEBUG_MOD >=3) cout<<"Module Calls so far: "<< modulecalls << endl;

    assert(fetchSuccess);
    
    assert(patchMap[pat.name].scandurationknown);
    double endPos = sat.xPos + (patchMap[pat.name].scanduration * sat.vSubT); // in the time needed for scanning the patch, the satellite moves forward on the groundtrack with its groundtrack speed vSat
    if(DEBUG_MOD>=2) cout << "Ending scan maneuver at " << endPos << endl;
    
    if (patchMap.find(pat.name) == patchMap.end()) {
        assert(false);
    }
    satelliteState resultPose = getSatState(endPos, pat.name, false, sat.vSubT);
    
    
    // scan possible?
    assert(stateCheck(resultPose,sat));
    if(DEBUG_MOD >= 1) {cout << "Writing back " << resultPose << endl;}
    toReturn["(x-pos " + satName + ")"] =  resultPose.x;
    toReturn["(yaw-angle " + satName + ")"] =  resultPose.yaw;
    toReturn["(pitch-angle " + satName + ")"] =  resultPose.pitch;
    toReturn["(roll-angle " + satName + ")"] =  resultPose.roll;
    toReturn["(yaw-rate " + satName + ")"] =  resultPose.yawRateN;
    toReturn["(pitch-rate " + satName + ")"] =  resultPose.pitchRateN;
    toReturn["(roll-rate " + satName + ")"] =  resultPose.rollRateN;

    
}


void DynamicSolver::targetEffects(map<string, double> & toReturn, string patchName, string satName, string osite, map<string, satellitePose>& mapPose){
    
    double tTarget = targetingTimeOfPatch(toReturn, patchName, satName, osite, mapPose);
    
    toReturn["(t_target " + patchName + " " + satName + " " + osite + ")"] =  tTarget;
    toReturn["(total-cost)"] =  toReturn["(total-cost)"] + tTarget;

    patchInfo pat;
    satelliteInfo sat;
    bool fetchSuccess =fetchWorldState(patchName,satName,osite,mapPose,pat,sat);

    assert(fetchSuccess);
    
    satelliteState currentState(sat);
    if(DEBUG_MOD >= 3) cout << "Fetching target x-Position from database..." << endl;
    stateAndPatchname apD_entry(currentState, pat.name);
    assert(approachPointDatabase.find(apD_entry) != approachPointDatabase.end());
    double x_approached = approachPointDatabase[apD_entry];
    if(DEBUG_MOD >= 3) cout << "Looking up target position after approaching x-Point " << x_approached << endl;
    satPosAndPatch spD_entry(x_approached, pat.name, true);
    assert(satPoseDatabase.find(spD_entry) != satPoseDatabase.end());
    satelliteState resultPose = satPoseDatabase[spD_entry];
    if(DEBUG_MOD >= 2) cout << "Result pose found in Database : " << sat.name << endl;
    
    assert(stateCheck(resultPose,sat));
    if(DEBUG_MOD >= 1) {cout << "Writing back " << resultPose << endl;}
    toReturn["(x-pos " + satName + ")"] =  resultPose.x;
    toReturn["(yaw-angle " + satName + ")"] =  resultPose.yaw;
    toReturn["(pitch-angle " + satName + ")"] =  resultPose.pitch;
    toReturn["(roll-angle " + satName + ")"] =  resultPose.roll;
    toReturn["(yaw-rate " + satName + ")"] =  resultPose.yawRateN;
    toReturn["(pitch-rate " + satName + ")"] =  resultPose.pitchRateN;
    toReturn["(roll-rate " + satName + ")"] =  resultPose.rollRateN;
    mapPose[satName].x=resultPose.x;
    mapPose[satName].yaw=resultPose.yaw;
    mapPose[satName].roll=resultPose.roll;
    mapPose[satName].pitch=resultPose.pitch;
    mapPose[satName].yawRate=resultPose.yawRateN;
    mapPose[satName].pitchRate=resultPose.pitchRateN;
    mapPose[satName].rollRate=resultPose.rollRateN;


}

double DynamicSolver::targetingTimeOfPatch(map<string, double> & toReturn, string patchName, string satName, string osite, map<string, satellitePose> mapPose){
    if(DEBUG_MOD >= 2) cout<< "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n$$$$$$$$$$  ";
    if(DEBUG_MOD) cout<<"Module Call: targetingTimeOfPatch ";
    if(DEBUG_MOD >= 2) cout<< "                        $$$$$$$$$$\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    modulecalls++;
    if(DEBUG_MOD >=3) cout<<"Module Calls so far: "<< modulecalls << endl;
    patchInfo pat;
    satelliteInfo sat;
    fetchWorldState(patchName,satName,osite,mapPose,pat,sat);
    satelliteState currentPose(sat);
    if (DEBUG_MOD>=4) {cout << "Begin Calculation... " <<endl;}
    vector3d dPatch(pat.exit-pat.entry);
    vector3d dSat(sat.vSubT, 0, 0); // direction vector of Satellite Ground track
    
    if (patchMap.find(pat.name) == patchMap.end()) {
        patchMapInsert++;
        if(DEBUG_MOD >= 1) cout << "Inserting new patch into database (insert #" << patchMapInsert << ")" << endl;
        patchMap.insert(pair<string,patchInfo>(pat.name,pat));
        double scanduration = std::sqrt(square(pat.exit.x - pat.entry.x) + square(pat.exit.y - pat.entry.y) + square(pat.exit.z-pat.entry.z));
        scanduration /= pat.scanvelocity;
        if(DEBUG_MOD >= 4) cout << "Calculated scan velocity : " << scanduration << endl;
        patchMap[pat.name].setScanduration(scanduration);
        patchMap[pat.name].setScanningSatellite(sat.name);
    }
    
    if (patchMap[pat.name].lastXknown) {
        if (DEBUG_MOD >= 2) cout << "Use lastX from Database: " << patchMap[pat.name].lastX << endl;
    } else {
        if(DEBUG_MOD >=4) cout << "Have to calculate last possible Scanpoint..." << endl;
        calculateExtremeScanPositions(patchMap[pat.name], sat.name, sat.pitchMaxN, sat.vSubT);
    }
    double xFirst = sat.xPos;
    double xLast = patchMap[pat.name].lastX;
    if (xFirst > xLast) {
        if(DEBUG_MOD >=2) cout << "Patch is not approachable; " << xFirst << " > " << xLast << endl;
        if(DEBUG_MOD >=2) cout << "returning infinite cost..." << endl;
        return INFINITE_COST;
    }
    if (xFirst < patchMap[pat.name].firstX) {
        if(DEBUG_MOD >=2) cout << "firstX: " << patchMap[pat.name].firstX << endl;
        xFirst = patchMap[pat.name].firstX;
    }
    if(DEBUG_MOD >=3) cout << "Determining lower bounds approach pose: " << endl;
    satelliteState entryPose = getSatState(xFirst, pat.name, true, sat.vSubT);
    
    // initial maneuver possible?
    
    if(DEBUG_MOD >=4) cout << "Looking for maneuver from " << currentPose <<" to " << entryPose << "." << endl;
    double deltaT = (entryPose.x - currentPose.x) / sat.vSubT; //TODO lookup deltaT for more exact results since subtrack speed is not constant
    if(stateCheck(entryPose,sat) && maneuver(currentPose, entryPose, sat.angAccMaxN, deltaT)) {
        if(DEBUG_MOD >= 3) cout <<" Maneuver from current orbit position to earliest possible patch approach pose is possible (patch is possibly far in the future)" << endl;
        if(DEBUG_MOD >= 3) cout <<" Returning maneuver time " << deltaT << endl;
        approachPointInsert++;
        if(DEBUG_MOD >= 3)		cout << "Store approach Point in Database, from " << currentPose << " to " << pat.name << " at x: "<< entryPose.x << " (insert #" << approachPointInsert << ")" << endl;
        stateAndPatchname apD_entry(currentPose, pat.name);
        approachPointDatabase.insert(pair<stateAndPatchname, double>(apD_entry, entryPose.x));
        if(DEBUG_MOD >= 2) cout<< "--------------------------------------------------------------------------------" << endl;
        return deltaT;
    }
    if(DEBUG_MOD >= 3) cout << " Maneuver from current orbit position to earliest patch approach pose is not possible. Determining feasible maneuver with the help of nested intervals..." << endl;
    
    satelliteState lastPose = getSatState(xLast, pat.name, true, sat.vSubT);
    if(DEBUG_MOD >=4) cout << "Looking for maneuver from " << currentPose << " to last Pose " << lastPose << "." << endl;
    deltaT = (lastPose.x - currentPose.x) / sat.vSubT; //TODO lookup deltaT for more exact results since subtrack speed is not constant
    if(!stateCheck(lastPose,sat) || !maneuver(currentPose, lastPose, sat.angAccMaxN, deltaT)) {
        //cout <<" Maneuver from current orbit position to last possible patch approach pose is impossible" << endl;
        //cout <<" Scanning patch impossible, return infinity " << endl;
        if(DEBUG_MOD >= 2) cout<< "--------------------------------------------------------------------------------" << endl;
        return INFINITE_COST;
    }
    if(DEBUG_MOD >= 3) cout << " Maneuver time to last x-Pos " << xLast << " is " << deltaT << " (upper bound)"<< endl;
    int currentdepth = 1;
    double xMiddle;
    while (currentdepth <= NESTING_DEPTH) {
        if(DEBUG_MOD >= 4) cout << "Begin nested intervals, depth " << currentdepth << "/" << NESTING_DEPTH << endl;
        if(DEBUG_MOD >= 3) cout << "Determining Middlepose, xFirst = " << xFirst << "  xLast = " << xLast << endl;
        xMiddle = (xFirst + xLast)/2;
        satelliteState middlePose = getSatState(xMiddle, pat.name, true, sat.vSubT);
        if(DEBUG_MOD >=4) cout << "Looking for maneuver from " << currentPose << " to middle Pose " << middlePose << "." << endl;
        deltaT = (middlePose.x - currentPose.x) / sat.vSubT; //TODO lookup deltaT for more exact results since subtrack speed is not constant
        if(stateCheck(middlePose,sat) && maneuver(currentPose, middlePose, sat.angAccMaxN, deltaT)) {
            if(DEBUG_MOD >= 3)cout <<" Maneuver from current orbit position to interval middle is possible, using it as new xLast" << endl;
            xLast = xMiddle;
            lastPose = middlePose; // save middle Pose as new Last Pose
        } else {
            if(DEBUG_MOD >= 3)cout <<" Maneuver from current orbit position to interval middle is impossible, using it as new xFirst" << endl;
            xFirst = xMiddle;
        }
        currentdepth++;
    }
    if (DEBUG_MOD) {cout << "Done with interval nesting. xLast = " << xLast << endl;}
    
    double t_last = (lastPose.x - currentPose.x) / sat.vSubT; //TODO lookup deltaT for more exact results since subtrack speed is not constant
    if (DEBUG_MOD) {cout << "Returning best maneuver time: " << t_last << endl;}
    approachPointInsert++;
    if(DEBUG_MOD >= 2)cout << "Store approach Point in Database, from " << currentPose << " to " << pat.name << " at x: "<< lastPose.x << " (insert #" << approachPointInsert << ")" << endl;
    stateAndPatchname apD_entry(currentPose, pat.name);
    approachPointDatabase.insert(pair<stateAndPatchname, double>(apD_entry, lastPose.x));
    
    if(DEBUG_MOD >= 2) cout<< "--------------------------------------------------------------------------------" << endl;
    assert(t_last > 0);
    return t_last;
}

double DynamicSolver::endPoseAfterScanning(map<string, double> & toReturn, string patch, string satName, string osite, map<string, satellitePose> mapPose)
{
    if(DEBUG_MOD >= 2) cout<< "********************************************************************************\n**********  ";
    if(DEBUG_MOD) cout<<"Module Call: endPoseAfterScanning ";
    if(DEBUG_MOD >= 2) cout<< "                        **********\n********************************************************************************" << endl;
    modulecalls++;
    if(DEBUG_MOD >=3) cout<<"Module Calls so far: "<< modulecalls << endl;
    if ( false ) {
        scanTimeHeuristic++;
        if (DEBUG_MOD >=3) {cout << "Starting calculation (#"<< scanTimeHeuristic<<") in HEURISTIC Mode" << endl;}
    } else {
        scanTimeCalls++;
        if(DEBUG_MOD >= 3) cout << "PRECISE (non heuristic) cost calculation (#" << scanTimeCalls << ")"<<endl;
    }
    
    patchInfo pat;
    satelliteInfo sat;
    bool fetchSuccess = fetchWorldState(patch,satName,osite,mapPose,pat,sat);
    assert(fetchSuccess);
    
    satelliteState currentPose(sat);
    
    /**
     * Start of Calculations
     */
    if (DEBUG_MOD>=4) {cout << "Begin Calculation... " <<endl;}
    vector3d dPatch(pat.exit-pat.entry);
    
    double tScan;
    
    if (patchMap.find(pat.name) == patchMap.end()) {
        assert(false);
        patchMapInsert++;
        if(DEBUG_MOD >= 1) cout << "Inserting new patch into database (insert #" << patchMapInsert << ")" << endl;
        patchMap.insert(pair<string,patchInfo>(pat.name,pat));
        double scanduration = std::sqrt(square(pat.exit.x - pat.entry.x) + square(pat.exit.y - pat.entry.y) + square(pat.exit.z-pat.entry.z));
        scanduration /= pat.scanvelocity;
        if(DEBUG_MOD >= 4) cout << "Calculated scan velocity : " << scanduration << endl;
        patchMap[pat.name].setScanduration(scanduration);
        patchMap[pat.name].setScanningSatellite(sat.name);
    }
    patchInfo databasePatch = patchMap[pat.name];
    
    if (databasePatch.scandurationknown) {
        tScan=databasePatch.scanduration;
        if(DEBUG_MOD >=4) cout << " Using tScan from patch database : " << tScan << " (self calculated would be " << (dPatch.length() / databasePatch.scanvelocity) << ")"<< endl;
    } else {
        assert(false);
        tScan = dPatch.length() / pat.scanvelocity;
        pat.setScanduration(tScan);
    }
    double endPos = sat.xPos + (tScan * sat.vSubT); // in the time needed for scanning the patch, the satellite moves forward on the groundtrack with its groundtrack speed vSat
    
    if(DEBUG_MOD>=2) cout << "Ending scan maneuver at " << endPos << endl;
    
    if (patchMap.find(pat.name) == patchMap.end()) {
        assert(false);
    }
    //			patchMapInsert++;
    //			if(DEBUG_MOD >= 1) cout << "Inserting new patch into database (insert #" << patchMapInsert << ")" << endl;
    //			patchMap.insert(pair<string,patchInfo>(pat.name,pat));
    //			double scanduration = std::sqrt(square(pat.exit.x - pat.entry.x) + square(pat.exit.y - pat.entry.y) + square(pat.exit.z-pat.entry.z));
    //			scanduration /= pat.scanvelocity;
    //			if(DEBUG_MOD >= 4) cout << "Calculated scan velocity : " << scanduration << endl;
    //			patchMap[pat.name].setScanduration(scanduration);
    //			patchMap[pat.name].setScanningSatellite(sat.name);
    //		}
    
    satelliteState exitPose = getSatState(endPos, pat.name, false, sat.vSubT);
    
    
    
    // scan maneuver possible?
    if (stateCheck(exitPose,sat)) {
        if(DEBUG_MOD >=4) cout << "Looking for maneuver from " << currentPose << " to " << exitPose << "." << endl;
        /**
         * this maneuvercheck is optional, and should always return true...
         */
        if(maneuver(currentPose, exitPose, sat.angAccMaxN, tScan)) {
            //cout <<" Maneuver from current orbit position to endposition of patch " << pat.name << " is possible " << endl;
            //cout << "End Pose is: " << exitPose << endl;
            //cout <<" Returning true " << endl;
            return 1;
        }
    }
    //cout << "Maneuver impossible, return infinity " << endl;
    return 0;
}

bool DynamicSolver::fetchWorldState(string patch, string sat, string osite, map<string, satellitePose> mapPose, patchInfo & patinfo, satelliteInfo & satinfo) {
    // initializing vectors with 0
    patinfo = patchInfo("",vector3d(MAX_DOUBLE,MAX_DOUBLE,MAX_DOUBLE),vector3d(MAX_DOUBLE,MAX_DOUBLE,MAX_DOUBLE));
    satinfo = satelliteInfo();
    
    patinfo.name = patch;
    satinfo.name = sat;
    if (DEBUG_MOD >= 2) cout << "Extracted name of patch >";
    if (DEBUG_MOD >= 1) cout << patinfo.name;
    if (DEBUG_MOD >= 2) cout << "< and name of satellite >";
    if (DEBUG_MOD == 1) cout << " ";
    if (DEBUG_MOD >= 1) cout << satinfo.name;
    if (DEBUG_MOD == 1) cout << " ";
    if (DEBUG_MOD >= 2) cout << "<" << endl;
    
    patinfo = mapPatches[patch];
    satinfo = mapSatellites[sat];
    satellitePose satpose = mapPose[sat];
    satinfo.xPos = satpose.x;
    satinfo.roll = satpose.roll;
    satinfo.pitch = satpose.pitch;
    satinfo.yaw = satpose.yaw;
    satinfo.rollRate = satpose.rollRate;
    satinfo.pitchRate = satpose.pitchRate;
    satinfo.yawRate = satpose.yawRate;

    bool patchFetch = ((patinfo.name != "")
                       && (patinfo.entry.x < MAX_DOUBLE)
                       && (patinfo.entry.y < MAX_DOUBLE)
                       && (patinfo.entry.z < MAX_DOUBLE)
                       && (patinfo.exit.x < MAX_DOUBLE)
                       && (patinfo.exit.y < MAX_DOUBLE)
                       && (patinfo.exit.z < MAX_DOUBLE)
                       && patinfo.scanvelocityknown
                       );
    bool satelliteFetch = ((satinfo.name != "")
                           && (satinfo.xPos < MAX_DOUBLE )
                           && (satinfo.xHorizon < MAX_DOUBLE )
                           && (satinfo.rollMaxN < MAX_DOUBLE )
                           && (satinfo.pitchMaxN < MAX_DOUBLE )
                           && (satinfo.angRateXmaxN < MAX_DOUBLE )
                           && (satinfo.angRateYmaxN < MAX_DOUBLE )
                           && (satinfo.angRateZmaxN < MAX_DOUBLE )
                           && (satinfo.angAccMaxN < MAX_DOUBLE )
                           && (satinfo.roll < MAX_DOUBLE )
                           && (satinfo.pitch < MAX_DOUBLE )
                           && (satinfo.yaw < MAX_DOUBLE )
                           && (satinfo.rollRate < MAX_DOUBLE )
                           && (satinfo.pitchRate < MAX_DOUBLE )
                           && (satinfo.yawRate < MAX_DOUBLE )
                           && (satinfo.vSubT < MAX_DOUBLE )
                           );

        if(DEBUG_MOD>=2) {  cout << " x-entry of patch found: \t" << patinfo.entry.x << endl;}
        if(DEBUG_MOD>=2) {  cout << " y-entry of patch found: \t" << patinfo.entry.y << endl;}
        if(DEBUG_MOD>=2) {  cout << " z-entry of patch found: \t" << patinfo.entry.z << endl;}
         if(DEBUG_MOD>=2) {  cout << " x-exit of patch found: \t" << patinfo.exit.x << endl;}
        if(DEBUG_MOD>=2) {  cout << " y-exit of patch found: \t" << patinfo.exit.y << endl;}
        if(DEBUG_MOD>=2) {  cout << " z-exit of patch found: \t" << patinfo.exit.z << endl;}
        if(DEBUG_MOD>=2) {cout << " satellite scan velocity:\t" << patinfo.scanvelocity << endl;}
    if(DEBUG_MOD>=2) {  cout << " satellite x-position:\t\t" << satinfo.xPos << endl;}
    if(DEBUG_MOD>=2) {  cout << " satellite horizon (x):\t\t" << satinfo.xHorizon << endl;}
    if(DEBUG_MOD>=2) {  cout << " maximal angular rate (x):\t" << satinfo.angRateXmaxN << " rad"<< endl;}
    if(DEBUG_MOD>=2) {  cout << " maximal angular rate (y):\t" << satinfo.angRateYmaxN << " rad"<< endl;}
    if(DEBUG_MOD>=2) {  cout << " maximal angular rate (z):\t" << satinfo.angRateZmaxN << " rad"<< endl;}
    if(DEBUG_MOD>=2) {  cout << " maximal angular acceleration :\t" << satinfo.angAccMaxN << " rad"<< endl;}
    if(DEBUG_MOD>=2) {  cout << " roll angle of satellite: \t" << satinfo.roll << " rad" << endl;}
    if(DEBUG_MOD>=2) {  cout << " pitch angle of satellite: \t" << satinfo.pitch << " rad" << endl;}
    if(DEBUG_MOD>=2) {  cout << " yaw angle of satellite: \t" << satinfo.yaw << " rad"<< endl;}
    if(DEBUG_MOD>=2) {  cout << " roll rate of satellite: \t" << satinfo.rollRate << " rad/s" << endl;}
    if(DEBUG_MOD>=2) {  cout << " pitch rate of satellite: \t" << satinfo.pitchRate << " rad/s" << endl;}
    if(DEBUG_MOD>=2) {  cout << " yaw rate of satellite: \t" << satinfo.yawRate << " rad/s"<< endl;}
    if(DEBUG_MOD>=2) {  cout << " maximal Pitch Angle:\t\t" << satinfo.pitchMaxN << endl;}
    if(DEBUG_MOD>=2) {  cout << " maximal Roll Angle:\t\t" << satinfo.rollMaxN << endl;}
    if(DEBUG_MOD>=2) {  cout << " Satellite velocity (subtrace): " << satinfo.vSubT << endl;}
    
    if ((DEBUG_MOD >= 1) && !satelliteFetch) {
        cout << "Fetching satellite failed..." << endl;
        cout << " name\t" << ((satinfo.name != "")?"[X]":"[ ]") << endl;
        cout << " xPos\t" << ((satinfo.xPos < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " xHorizon\t" << ((satinfo.xHorizon < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " rollMax\t" << ((satinfo.rollMaxN < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " pitchMaxN\t" << ((satinfo.pitchMaxN < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " angRateXmaxN\t" << ((satinfo.angRateXmaxN < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " angRateYmaxN\t" << ((satinfo.angRateYmaxN < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " angRateZmaxN\t" << ((satinfo.angRateZmaxN < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " angAccMaxN\t" << ((satinfo.angAccMaxN < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " roll\t" << ((satinfo.roll < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " pitch\t" << ((satinfo.pitch < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " yaw\t" << ((satinfo.yaw < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " rollRate\t" << ((satinfo.rollRate < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " pitchRate\t" << ((satinfo.pitchRate < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " yawRate\t" << ((satinfo.yawRate < MAX_DOUBLE)?"[X]":"[ ]") << endl;
        cout << " vSubT\t" << ((satinfo.vSubT < MAX_DOUBLE)?"[X]":"[ ]") << endl;
    }
    if (DEBUG_MOD >= 4) cout << "Fetches success: patch " << (patchFetch?"[X]":"[ ]") << " satellite " << (satelliteFetch?"[X]":"[ ]") << endl;
    return patchFetch && satelliteFetch;
    
}

