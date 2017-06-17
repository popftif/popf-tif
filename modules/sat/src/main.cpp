#include <iostream>
#include "SaTSolver.h"
#include <fstream>
#include <list>

using namespace std;

vector<string> findParameters(string line, int &n){
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

list<pair<string,double> > parsePlan(string plan){
    list<pair<string,double> > toReturn;
    string line;
    ifstream parametersFile(plan.c_str());
    if (parametersFile.is_open()){
        while (getline(parametersFile,line)){
            if (line.find("dospiral")!=-1){
                int n=0;
                vector<string> tokens = findParameters(line,n);
                if (n>4){
                    string timestring = tokens[0];
                    timestring = timestring.substr(0,timestring.length()-1);
                    double time = atof(timestring.c_str());
                    string spiral = tokens[4];
                    spiral = spiral.substr(0,spiral.length()-1);
                    toReturn.push_back({spiral,time+299});
                }
            }
        }
    }else{
        cout << plan << " not found" << endl;
    }
    return toReturn;
}

map<string,double> parseProblem(string problem, map<string,list<string> > spirals, map<string,int> & cities){
    map<string,double> toReturn;
    string line;
    ifstream parametersFile(problem.c_str());
    if (parametersFile.is_open()){
        while (getline(parametersFile,line)){
            if (line.find("n-pattern-active")!=-1){
                int n=0;
                vector<string> tokens = findParameters(line,n);
                if (tokens.size()>4){
                    string spiral = tokens[3].substr(0,tokens[3].size()-1);
                    double t = atof(tokens[4].substr(0,tokens[4].size()-1).c_str());
                    toReturn[spiral]=t;
                }else if (tokens.size()==4){
                    string spiral = tokens[2].substr(0,tokens[2].size()-1);
                    double t = atof(tokens[3].substr(0,tokens[3].size()-1).c_str());
                    toReturn[spiral] = t;
                }else{
                    cout << "Error while parsing problem file, contact Chiara" << endl;
                    cout << line << endl;
                }
            }else if (line.find ("previous-probability")!=-1){
                int n = 0;
                vector<string> tokens = findParameters(line,n);
                if (tokens.size()==5){
                    string city = tokens[3].substr(0,tokens[3].size()-1);
                    if (cities.find(city)==cities.end()){
                        cities.insert({city,cities.size()});
                        //cout << city << " is not in any search pattern!" << endl;
                    }
                }
            }
            
        }
    }
    return toReturn;
}

int main(int argc, char **argv) {
    //std::cout << "Hello, world!" << std::endl;
    SaTSolver testExample;
    string initialParameters;
    string plan;
    string problem;
    
    if (argc > 3){
        problem = argv[1];
        initialParameters = argv[2];
        plan = argv[3];
    }else{
        cout << "Usage:\n"
        << argv[0] << " problem parameters plan" << endl;
        return 1;
    }
    
    list<pair<string,double> > spirals = parsePlan(plan);
    string parameters[] = {initialParameters};
    testExample.loadSolver(parameters,1);
    map<string,int> cities = testExample.getCities();
    map<string,list<string> > allSpirals = testExample.getDestinations();
    map<string,double> initialState;
    
    map<string,double> times = parseProblem(problem,allSpirals,cities);
    int nCities = cities.size();

    initialState["(previous-total-probability)"] = 0;
    initialState["(total-probability)"] = 0;
    initialState["(expected-time)"] = 0;
    initialState["(previous-expexted-time)"] = 0;
    initialState["(n-pattern)"] = 1;
    for (map<string,int>::iterator cIt = cities.begin();cIt!=cities.end();++cIt){
        initialState["(previous-probability " + cIt->first + ")"] = 1./nCities;
        initialState["(probability " + cIt->first + ")"] = 1./nCities;
    }
    for (map<string,list<string> >::iterator sIt = allSpirals.begin();sIt!=allSpirals.end();++sIt){
        initialState["(is-doing " + sIt->first + ")"] = 0;
    }
    
    cout << "0 init 0 0 0" << endl;
    for (list<pair<string,double> >::iterator pIt = spirals.begin(); pIt!=spirals.end();++pIt){
        string name = pIt->first;
        double time = pIt->second;
        //cout << "After applying " << name;
        cout << time << " " << name << " ";
        initialState["(is-doing " + name + ")"] = 1;
        initialState["(n-pattern)"] = times[name];
        
        map<string,double> childState = testExample.callExternalSolver(initialState,false);
        //itialState= testExample.callExternalSolver(initialState,false);
        for (map<string,double>::iterator sIt = childState.begin(); sIt!=childState.end();++sIt){
            //cout <<"\t*" << sIt->first << "\t" << sIt->second << endl;
            int n = 0;
            vector<string> t = findParameters(sIt->first,n);
            if (n > 1){
                string city =  t[1];
                city = city.substr(0,city.length()-1);
                initialState["(previous-probability " + city + ")"] = sIt->second;
            }
            initialState[sIt->first] = sIt->second;
        }
        initialState["(previous-total-probability)"] =  initialState["(total-probability)"];
        initialState["(previous-expected-time)"] = initialState["(expected-time)"];
        
        //cout << "\ttotal Probability\t" << initialState["(total-probability)"] << endl;
        //cout << "\t\t\texpected Time\t\t" << initialState["(expected-time)"] << " " <<  initialState["(total-probability)"] - 0.1*initialState["(expected-time)"]<< endl;
        
        cout << initialState["(total-probability)"] << " " << initialState["(expected-time)"] << " " << initialState["(total-probability)"] - 0.1*initialState["(expected-time)"] << endl;
        //	cout << "\t\t\tP_{S*}\t\t\t" << testExample.getPs() << endl;
        for (map<string,list<string> >::iterator sIt = allSpirals.begin();sIt!=allSpirals.end();++sIt){
            initialState["(is-doing " + sIt->first + ")"] = 0;
        }
        for (map<string,double>::iterator sIt = initialState.begin(); sIt!=initialState.end();++sIt){
            //cout << "\t" << sIt->first << "\t" << sIt->second<<endl;
        }
    }
    return 0;
}
