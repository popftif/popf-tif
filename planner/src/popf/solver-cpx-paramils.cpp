/************************************************************************
 * Copyright 2009, 2011, Strathclyde Planning Group,
 * Department of Computer and Information Sciences,
 * University of Strathclyde, Glasgow, UK
 * http://planning.cis.strath.ac.uk/
 *
 * Amanda Coles, Andrew Coles, Maria Fox, Derek Long - POPF
 * Maria Fox, Richard Howey and Derek Long - VAL
 * Stephen Cresswell - PDDL Parser
 *
 * This file is part of POPF.
 *
 * POPF is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * POPF is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with POPF.  If not, see <http://www.gnu.org/licenses/>.
 *
 ************************************************************************/

void setILS(IloCplex * cplex)
{
    if (provided) {
    
        {
            const int pCount = intParams.size();
            for (int p = 0; p < pCount; ++p) {
                cplex->setParam((IloCplex::IntParam) intParams[p].first, intParams[p].second);
            }
        }
        
        {
            const int pCount = boolParams.size();
            for (int p = 0; p < pCount; ++p) {
                cplex->setParam((IloCplex::BoolParam) boolParams[p].first, boolParams[p].second);
            }
        }
        
        {
            const int pCount = numParams.size();
            for (int p = 0; p < pCount; ++p) {
                cplex->setParam((IloCplex::NumParam) numParams[p].first, numParams[p].second);
            }
        }
        
        return;
    }

    
}

