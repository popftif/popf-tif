#include <iostream>
#include "HBWSolver.h"

using namespace std;

int main(int argc, char **argv) {
    std::cout << "Hello, world!" << std::endl;
    HBWSolver solver;
    solver.parseParameters("/home/chiara/Planning/HBW/tfdm/parameters/10_paramsproblem6_8.pddl");
    solver.columns["c0"].p=5;
    solver.columns["c1"].p=9;
    solver.columns["c2"].p=9;
    solver.columns["c3"].p=4;
    
    solver.calculateHeight();
    map<string,Column>::iterator clIt=solver.columns.begin();
    map<string,Column>::iterator clEnd=solver.columns.end();
    for(;clIt!=clEnd;++clIt){
        cout << clIt->second.name << " " << clIt->second.d << endl;
    }
    return 0;
}
