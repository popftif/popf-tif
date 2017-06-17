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


#include "SaTSolver.h"
#include "ExternalSolver.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

extern "C" ExternalSolver* create_object(){
    return new SaTSolver();
}

extern "C" void destroy_object(ExternalSolver *externalSolver){
    delete externalSolver;
}

SaTSolver::SaTSolver(){
    
}

SaTSolver::~SaTSolver(){
    
}

void SaTSolver::loadSolver(string *parameters, int n){
    
    string satParamers = parameters[0];
    char const *x[]={"probability","total-probability","heuristic-approximation","expected-time"};//,"heuristic-expected"};
    char const *y[]={"previous-probability","previous-total-probability","previous-expected-time","n-pattern"};//,"n-pattern-active"};
    parseParameters(satParamers);
    affected = list<string>(x,x+4);
    dependencies = list<string>(y,y+4);
}

map<string,double> SaTSolver::callExternalSolver(map<string,double> initialState,bool isHeuristic){
    
    map<string, double> toReturn;
    map<string, double>::iterator iSIt = initialState.begin();
    map<string, double>::iterator isEnd = initialState.end();
    map<string, bool> isActive;
    map<string, double> probabilities;
    map<string, string> probabilitiesResult;
    map<string, string> heuristicApproximation;
    map<string, double> heuristicExpected;
    map<string, double> nTimePattern;
    double totalProbability;
    double expectedTime;
    double t;
    //cout << "apply solver" << endl;
    for(;iSIt!=isEnd;++iSIt){
        
        string parameter = iSIt->first;
        string function = iSIt->first;
        double value = iSIt->second;
        function.erase(0,1);
        function.erase(function.length()-1,function.length());
        int n=function.find(" ");
        //cout << parameter << " " << value << endl;
        if(n!=-1){
            string arg=function;
            function.erase(n,function.length()-1);
            arg.erase(0,n+1);
            if(function=="is-doing"){
                isActive[arg] = value>0.5?true:false;
                //cout << parameter << " " << value << endl;
            }else if(function=="previous-probability"){
                probabilities[arg] = value;
                //cout << parameter << " " << value << endl;
            }else if(function=="probability"){
                probabilitiesResult[arg] = parameter;
                toReturn[parameter] = value;
            }else if(function=="heuristic-approximation"){
                probabilitiesResult[arg] = parameter;
                heuristicApproximation[arg] = parameter;
                toReturn[parameter] = value;
            }/*else if (function=="heuristic-expected"){
		toReturn[parameter] = value;
		heuristicExpected[parameter] = value;
	    }else if (function=="n-pattern-active"){
		nTimePattern[arg] = value;
		}*/
        }else{
            if(function=="previous-total-probability"){
                totalProbability = value;
                //cout << function << " " << value << endl;
            }else if(function=="previous-expected-time"){
                expectedTime = value;
                //cout << function << " " << value << endl;
            }else if(function=="n-pattern"){
                t = value;
                //cout << function << " " << value << endl;
            }
        }
    }
    pair<double, map<string,double> > results = calculateProbabilities(isActive,probabilities,totalProbability,heuristicApproximation,expectedTime,t, heuristicExpected, nTimePattern);
    if (ExternalSolver::verbose){
        cout << "(total-probability) " << results.first << endl;
        cout << "(expected-time) " << expectedTime << endl;
    }
    //cout << "total-provability " << results.first << endl;
    toReturn["(total-probability)"] = results.first;
    toReturn["(expected-time)"] = expectedTime;
    toReturn["(heuristic-approximation)"] = results.first>0.001?results.first:0.001;
    
    map<string,double> resultsP = results.second;
    for(pair<string,double> r : resultsP){
        string name = r.first;
        double value = r.second;
        toReturn[probabilitiesResult[name]] = value;
        if (ExternalSolver::verbose){
            cout << probabilitiesResult[name] << " " << value << endl;
        }
        //cout << name << " " << probabilitiesResult[name] << " " << value << endl;
    }
    for (pair<string,double> h : heuristicExpected){
	toReturn[h.first] = h.second;
	//cout << h.first << " " << h.second << endl;
    }
    //cout << endl;
    return toReturn;
}

list<string> SaTSolver::getParameters(){
    
    return affected;
}

list<string> SaTSolver::getDependencies(){
    
    return dependencies;
}

vector<string> SaTSolver::findParameters(string line, int &n){
    int nPos = 0;
    while(nPos!=-1){
        nPos=line.find(" ",nPos+1);
        n++;
    }
    vector<string> toReturn(n);
    nPos = 0;
    int i=0;
    while(nPos!=-1){
        int extra = i==0?0:1;
        int nPrevious = nPos+extra;
        nPos=line.find(" ",nPos+1);
        string tmp =line.substr(nPrevious,nPos-nPrevious);
        if (nPos==-1){
            tmp=tmp.substr(0,tmp.length());
        }
        //cout << tmp << endl;;
        toReturn[i]=tmp;
        i++;
    }
    
    if(toReturn[0].find(" ")){
        toReturn[0]=toReturn[0].substr(0,toReturn[0].find(" "));
    }
    
    return toReturn;
}

void SaTSolver::parseParameters(string parameters){
    
    //cout << "reading " << parameters << endl;
    string line;
    ifstream parametersFile(parameters.c_str());
    if (parametersFile.is_open()){
        while (getline(parametersFile,line)){
            int n=0;
            vector<string> tokens = findParameters(line,n);
            if (n==1){
                maxT = atof(tokens[0].c_str());
            }
            if (n>2){
                string pattern = tokens[0];
                double g = atof(tokens[1].c_str());
                gamma[pattern] = g;
                for (int i=2;i<n;++i){
                    //cout << g << " " << tokens[i] << endl;
                    string d = tokens[i];
                    string lower;
                    const char* myOutput = d.c_str();
                    for(int i = 0; myOutput[i] != '\0'; i++){
                        lower+= tolower(myOutput[i]);
                    }
                    if (lower!=""){
                        destinations[pattern].push_back(lower);
                        if (cities.find(lower)!=cities.end()){
                            cities[lower]++;
                        }else{
                            cities.insert(make_pair(lower,1));
                        }
                    }
                    
                }
            }
            
        }
    }
}
/*
 // this doesn't work with my compiler :(
 
 void SaTSolver::parseParameters(string parameters){
 
 //cout << "reading " << parameters << endl;
 string line;
 ifstream parametersFile(parameters.c_str());
 if (parametersFile.is_open()){
 while (getline(parametersFile,line)){
 stringstream ss(line);
 istream_iterator<string> begin(ss);
 istream_iterator<string> end;
 vector<std::string> tokens(begin, end);
 if (tokens.size()>2){
 string pattern = tokens[0];
 double g = atof(tokens[1].c_str());
 gamma[pattern] = g;
 for (int i=2;i<tokens.size();++i){
 
 string d = tokens[i];
 destinations[pattern].push_back(d);
 
 }
 }
 
 }
 }
 }
 */

pair<double,map<string, double> > SaTSolver::calculateProbabilities(map<string,bool> isActive, map<string,double> probabilities, double totalProbability, map<string,string> heuristicApproximation,double &expectedTime, double t, map<string,double> & hExpected, map<string,double> nTimePattern){
    
    string pattern = "";
    for (pair<string,bool> p : isActive){
        if (p.second){
            pattern = p.first;
            break;
        }
    }
    
    double g = gamma[pattern];
    list<string> compatible = destinations[pattern];
    
    double sum = 0;
    for (pair<string,double>pr : probabilities){
        string city = pr.first;
        double value = pr.second;
        bool isPossibleDestination = isCompatible(city,compatible);
        if (isPossibleDestination){
            sum += value;
            //cout << city << " " << value << endl;

        }
    }
    //cout << "sum " << sum << endl;
    //cout << "totalProbability " << totalProbability << endl;
    //cout << "g " << g << endl;
    // calculate new values
    
    double newTotalProbability = totalProbability + sum*g*(1-totalProbability);
    //cout << "newTotalProbability " << newTotalProbability << endl;
    expectedTime += t/maxT*(newTotalProbability-totalProbability);
    psstart = sum*g;
    map<string,double> toReturn;
    
    for (pair<string,double>pr : probabilities){
        string city = pr.first;
        double value = pr.second;
        bool isPossibleDestination = isCompatible(city,compatible);
        if (isPossibleDestination){
            toReturn[city] = value*(1-g)/(1-sum*g);
        }else{
            toReturn[city] = value/(1-sum*g);
        }
    }
    for (pair<string,string> h : heuristicApproximation){
        string patternH = h.first;
        double gH = gamma[patternH];
        list<string> compatibleH = destinations[patternH];
        double vH = 0;
        for (string cH : compatibleH){
            vH += toReturn[cH];
            //cout << patternH << " " << cH << " " << toReturn[cH] << endl;
        }
        //cout << vH << endl;
        vH = vH*(1-newTotalProbability)*gH;
        //cout << "***" << patternH << " " << vH << endl;
	hExpected["(heuristic-expected " + patternH + ")"] = nTimePattern[patternH]/maxT*vH;
        toReturn[patternH] = vH;
    }
    return make_pair(newTotalProbability,toReturn);
}

bool SaTSolver::isCompatible(string city, list<string> compatibility){
    return find(compatibility.begin(), compatibility.end(), city) != compatibility.end();
}
