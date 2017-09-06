/************************************************************************
 * Copyright 2008, Strathclyde Planning Group,
 * Department of Computer and Information Sciences,
 * University of Strathclyde, Glasgow, UK
 * http://planning.cis.strath.ac.uk/
 *
 * Maria Fox, Richard Howey and Derek Long - VAL
 * Stephen Cresswell - PDDL Parser
 *
 * This file is part of VAL, the PDDL validator.
 *
 * VAL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * VAL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VAL.  If not, see <http://www.gnu.org/licenses/>.
 *
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

#include <instantiation.h>
#include <TIM.h>

#include "FlexLexer.h"

extern int yyparse();
extern int yydebug;

using std::ifstream;
using std::ofstream;
using std::cout;
using std::cerr;
using std::ostringstream;
using std::endl;

namespace VAL {
    extern bool Verbose;
    extern parse_category* top_thing;
    
    extern analysis* current_analysis;
    
    extern yyFlexLexer* yfl;
    
    analysis an_analysis;
    
};

extern char * current_filename;


using namespace TIM;
using namespace Inst;
using namespace VAL;

int main(int argc,char * argv[])
{
    if (argc != 4) return 3;
    
    string mustHaveName(argv[1]);
    
    
    performTIMAnalysis(&argv[2]);
    
    
    SimpleEvaluator::setInitialState();
    
    
    #ifndef NDEBUG
    
    
    if (!mustHaveName.empty()) {
        string opname;
        
        int stringPosn = 1;
        
        {
            const int spaceAt = mustHaveName.find(" ", stringPosn);
            if (spaceAt != string::npos) {
                opname = mustHaveName.substr(stringPosn, spaceAt - stringPosn);
                stringPosn = spaceAt + 1;
            } else {
                opname = mustHaveName.substr(1, mustHaveName.size() - 2);
                stringPosn = -1;
            }
        }
        
        operator_list::const_iterator os = current_analysis->the_domain->ops->begin();
        
        for(; os != current_analysis->the_domain->ops->end(); ++os) {
            
            if (opname == (*os)->name->getName()) {
		cout << "Using instantiatedOp::insistOnOp hook for named action\n";
                instantiatedOp::insistOnOp = *os;
                break;
            } else {
                cout << (*os)->name->getName() << " does not match " << opname << endl; 
            }
                        
        }
        
        if (os == current_analysis->the_domain->ops->end()) {
            cout << "Test failed: no operator named " << opname << " can be found in the domain\n";
            exit(3);
        }

        var_symbol_list::const_iterator paramItr = instantiatedOp::insistOnOp->parameters->begin();
        const var_symbol_list::const_iterator paramEnd = instantiatedOp::insistOnOp->parameters->end();
                        
        int parIdx = 1;
        
        while (stringPosn != -1) {
            if (paramItr == paramEnd) {
                cout << "Test failed: too many parameters given for the named operator\n";
                exit(1);
            }
            
            VAL::pddl_type * const paramType = (*paramItr)->type;
            
            ++paramItr;
            
            const int spaceAt = mustHaveName.find(" ", stringPosn);
            string paramname;
            if (spaceAt != string::npos) {
                paramname = mustHaveName.substr(stringPosn, spaceAt - stringPosn);
                stringPosn = spaceAt + 1;                
            } else {
                paramname = mustHaveName.substr(stringPosn, mustHaveName.size() - stringPosn - 1);
                stringPosn = -1;
            }
            
            const vector<VAL::const_symbol*> typesafeOptions = theTC->range(paramType);
            
            if (typesafeOptions.empty()) {
                cout << "No type-safe options are available for parameter " << parIdx << " of " << opname << endl;
                exit(1);
            }
            
            vector<VAL::const_symbol*>::const_iterator sItr = typesafeOptions.begin();
            const vector<VAL::const_symbol*>::const_iterator sEnd= typesafeOptions.end();
            
            for (; sItr != sEnd; ++sItr) {
                if ((*sItr)->getName() == paramname) {
                    instantiatedOp::insistOnOpParameters.push_back(*sItr);
                    cout << "Using instantiatedOp::instOnOpParameters hook for parameter " << parIdx << endl;
                    break;
                }
            }
            
            if (sItr == sEnd) {
                cout << "The entity '" << paramname << "' is not considered to be a type-safe option for parameter " << parIdx << " of " << opname << endl;
                exit(1);
            }
            
            
            ++parIdx;
        }

        
    }
    #endif
    for(operator_list::const_iterator os = current_analysis->the_domain->ops->begin();
         os != current_analysis->the_domain->ops->end(); ++os) {
        
        cout << (*os)->name->getName() << "\n";
        instantiatedOp::instantiate(*os,current_analysis->the_problem,*theTC);
        cout << instantiatedOp::howMany() << " so far\n";
    
    }
    
    instantiatedOp::createAllLiterals(current_analysis->the_problem,theTC);
    
    cout << instantiatedOp::howMany() << " ops before filtering\n";
    instantiatedOp::writeAll(cout);
    
    cout << "Literals instantiated:\n";
    instantiatedOp::writeAllLiterals(cout);
    
    if (!mustHaveName.empty()) {
        cout << "\nLooking for " << mustHaveName << " before filtering:\n";
    
        OpStore::iterator opItr = instantiatedOp::opsBegin();
        const OpStore::iterator opEnd = instantiatedOp::opsEnd();
        
        bool found = false;
        
        for (int i = 0; opItr < opEnd; ++opItr) {
            ostringstream n;
            n << *(*opItr);
            string actName = n.str();
            if (actName == mustHaveName) {
                #ifndef NDEBUG
                instantiatedOp::opBeforeFiltering = *opItr;
                #endif
                cout << " - Found it\n";
                found = true;
            }
        }
        
        if (!found) {
            cout << "Test failed: could not find ground action " << mustHaveName << endl;
            return 1;
        }
    }    
    
    instantiatedOp::filterOps(theTC);
    cout << instantiatedOp::howMany() << " ops after filtering\n";
    //instantiatedOp::writeAll(cout);

    if (!mustHaveName.empty()) {
        cout << "\nLooking for " << mustHaveName << " after filtering:\n";
        
        OpStore::iterator opItr = instantiatedOp::opsBegin();
        const OpStore::iterator opEnd = instantiatedOp::opsEnd();
        
        bool found = false;
        
        for (int i = 0; opItr < opEnd; ++opItr) {
            ostringstream n;
            n << *(*opItr);
            string actName = n.str();
            if (actName == mustHaveName) {
                found = true;
            }
        }
                
        if (!found) {
            cout << "Test failed: could not find ground action " << mustHaveName << " after filtering";
            return 2;
        }
    }
    
	cout << "\nList of all literals:\n";
    
    instantiatedOp::writeAllLiterals(cout);
    
    

    return 0;
}
