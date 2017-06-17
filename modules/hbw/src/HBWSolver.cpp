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


#include "HBWSolver.h"
#include "ExternalSolver.h"
#include <map>
#include <string>
#include "armadillo"

using namespace std;
using namespace arma;

extern "C" ExternalSolver* create_object(){
    return new HBWSolver();
}

extern "C" void destroy_object(ExternalSolver *externalSolver){
    delete externalSolver;
}

HBWSolver::HBWSolver()
{

}

HBWSolver::~HBWSolver()
{

}

void HBWSolver::loadSolver(string* parameters, int n)
{
    string hbwParameters = parameters[0];
    char const *x[]={"height-column"};
    char const *y[]={"weight-column"};
    parseParameters(hbwParameters);
    affected = list<string>(x,x+1);
    dependencies = list<string>(y,y+1);
}

std::map< string, double > HBWSolver::callExternalSolver(std::map< string, double > initialState, bool isHeuristic)
{
    map<string,double> toReturn;
    map<string, double>::iterator iSIt = initialState.begin();
    map<string, double>::iterator isEnd = initialState.end();
    map<string, string> heightResults;
    for(;iSIt!=isEnd;++iSIt){
        string parameter = iSIt->first;
        string function = iSIt->first;
        double value = iSIt->second;
        function.erase(0,1);
        function.erase(function.length()-1,function.length());
        int n=function.find(" ");
        if(n!=-1){
            string arg=function;
            function.erase(n,function.length()-1);
            arg.erase(0,n+1);
            if(function=="weight-column"){
                //cout << arg << " " << value << endl;
                columns[arg].p = value;
            }else if(function=="height-column"){
                heightResults[arg] = parameter;
                //cout << arg << " " << parameter << endl;
            }
            
        }
    }
    calculateHeight();
    map<string,Column>::iterator clIt = columns.begin();
    map<string,Column>::iterator clEnd = columns.end();
    for(;clIt!=clEnd;++clIt){
        string name = clIt->first;
        double value = clIt->second.d;
        toReturn[heightResults[name]] = value;
       // toReturn[heightResults[name]] = value;
        //cout << heightResults[name] << " " << value << endl;
        
    }
    return toReturn;
    
}

list< string > HBWSolver::getParameters()
{
return affected;
}

list< string > HBWSolver::getDependencies()
{
return dependencies;
}

void HBWSolver::parseParameters(string parameters)
{
    string line;
    int iLine = 0;
    ifstream parametersFile (parameters.c_str());
    if (parametersFile.is_open())
    {
       while (getline(parametersFile,line)){
           std::istringstream iss(line);
           string a, b;
           if (!(iss >> a >> b)){
               break;
           }
           if(iLine==0){
               totalV = atof(a.c_str());
               totalrho = atof(b.c_str());
           }else{
               Column col;
               col.name = a;
               col.a = atof(b.c_str());
               col.d = 0;
               col.p = 0;
               columns[col.name]=col;
           }
           iLine++;
       }
    }else{
        cout << "Unable to open the file" << endl;
    }
}



void HBWSolver::calculateHeight()
{
    //cout << "calculating height " << endl;
    mat coefficient;
    mat y;
    int nVariables = columns.size();
    coefficient.reshape(nVariables,nVariables);
    y.reshape(nVariables,1);
    
    map<string,Column>::iterator clIt = columns.begin();
    map<string,Column>::iterator clEnd = columns.end();
    // first constraint
    for(int i=0;i<nVariables;i++,clIt++){
        Column col = clIt->second;
        coefficient.at(0,i) = col.a;
    }
    y.at(0) = totalV;
    //other constraints;
    clIt = columns.begin();
    clIt++;
    for(int i=1;i<nVariables;i++,clIt++){
        Column col2 = clIt->second;
        Column col1 = (--clIt)->second;
        ++clIt;
        //cout << "column1 " << col1.name << " column2 " << col2.name << endl;
        coefficient.at(i,i-1) = totalrho;
        coefficient.at(i,i) = -totalrho;
        y.at(i)=col2.p/col2.a-col1.p/col1.a;
    }
    mat result = inv(coefficient)*y;
    //cout << result<<endl;
    clIt = columns.begin();
    for(int i=0;i<nVariables;i++,clIt++){
        string name = clIt->first;
        columns[name].d = result.at(i);        
    }
}
