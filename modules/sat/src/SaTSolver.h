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


#ifndef SATSOLVER_H
#define SATSOLVER_H

#include "ExternalSolver.h"
#include <string>
#include <vector>

using namespace std;


class SaTSolver : public ExternalSolver
{
public:
    SaTSolver();
    ~SaTSolver();
    virtual void loadSolver(string* parameters, int n);
    virtual map<string,double> callExternalSolver(map<string,double> initialState, bool isHeuristic);
    virtual  list<string> getParameters();
    virtual  list<string> getDependencies();
    int getNCities(){
	static int c = 0;
	static bool first = true;
	if (first){
	    c = cities.size();
	    first = true;
	}
	return c;
    }
    map<string,int> getCities(){
	return cities;
    }
    map<string,list<string> > getDestinations(){
	return destinations;
    }
    double getPs(){
	return psstart;
    }
private:
    list<string> affected;
    list<string> dependencies;
    void parseParameters(string parameters);
    map<string,list<string> > destinations;
    map<string,int> cities;
    map<string, double> gamma;
    pair<double,map<string, double> > calculateProbabilities(map<string,bool> isActive, map<string,double> probabilities, double totalProbability, map<string,string> heuristicApproximation, double &expectedTime, double t, map<string,double> & hExpected, map<string,double> nTimePattern);
    bool isCompatible(string city, list<string> compatibility);
    vector<string> findParameters(string line, int&n);
    double maxT;
    double psstart;
    /*
    double totalV;
    double totalrho;
    double totalM;
    map<string,Column> columns;
    void calculateHeight();
    void calculateMaxWeight(string name);
  */
};

#endif // SATSOLVER_H
