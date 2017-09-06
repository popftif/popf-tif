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


#include "DotSearchSpace.h"
#include "Color.h"
#include <fstream>

void DotSearchSpace::addNode(int i, string n, int h, int idParent){
    Node child(i,n,h);
    graph.insert(make_pair(i,child));
    if(idParent>0){
        graph.find(idParent)->second.children.push_back(i);
    }
}

void DotSearchSpace::printDotFile(ostream &o)
{
    
    o<<"digraph SearchSpace{\n";
        if(addColor)
            o << "node [style = filled]\n";
        int hMax = graph.begin()->second.heuristic;
        Graph::iterator gIt = graph.begin();
        Graph::iterator gEnd = graph.end();
        for(;gIt!=gEnd;++gIt){
            list<int> children = gIt->second.children;
            list<int>::iterator cIt = children.begin();
            list<int>::iterator cEnd = children.end();
            Node node = gIt->second;
            if(addHeuristic || addColor){
                o << "\t" << node.id << " [ ";
                    if(addHeuristic)
                        o << "label=\"O: "<< node.id <<  ",\\nH: " << node.heuristic << "\"";
                    if(addColor){
                        int heuristic = node.heuristic;
                        Color color (75,0,130);
                        if(heuristic >-1){
                            color = createColor(heuristic ,0, hMax, 255,0); 
                        }else{
                            color = Color(150,150,150);
                        }
                        if(addHeuristic)
                            o << ",";
                        o << "color=\"" << color.getHex() << "\"";
                    }
                o<< "];\n";
            }
            for(;cIt!=cEnd;++cIt){
                Node child = graph.find(*cIt)->second;
                o << node.id << " -> " << child.id;
                if(addEdge)
                    o << " [label = \"" << child.name << "\"]";
                o << "\n";
            }
        }
        o << "}\n";
}

void DotSearchSpace::printDotFile(string nameFile)
{ 
    ofstream file(nameFile.c_str(),std::ofstream::out);
    printDotFile(file);
    file.close();
}

void DotSearchSpace::printDotFile()
{
    printDotFile(nameFile);
}

void DotSearchSpace::printGnuplotFile(ostream& o)
{
    o << "outputname = \""<< namePdf << "\"\n";
    o << "set terminal postscript eps color enhanced  font 'Verdana,14' size 8cm,6cm\n"; 
    o << "set output '| epstopdf --filter --outfile='.outputname\n";
    o << "set style line 1 lt 1 lw 3.5 lc rgb \"#25578F\" pt 7 ps 1\n";
    o << "set style line 2 lt 1 lw 3.5 lc rgb \"#D11F29\" pt 2 ps 1\n";
    o << "set style line 3 lt 1 lw 3.5 lc rgb \"#499943\" pt 5 ps 1\n";
    o << "set style line 4 lt 1 lw 3.5 lc rgb \"#F39F2C\" pt 5 ps 1\n";
    o << "set style line 5 lt 1 lw 3.5 lc rgb \"#4B0082\" pt 5 ps 1\n";
    o << "set style line 11 lt 1 lw 3.5 lc rgb '#444444' \n";
    o << "set style line 12 lt 2 lw 3.5 lc rgb '#444444' \n";
    o << "set border 3 back ls 11\n";
    o << "set tics nomirror\n";
    o << "set arrow from graph 1,0 to graph 1.02,0 size screen 0.025,15,60 filled ls 11\n";
    o << "set arrow from graph 0,1 to graph 0,1.05 size screen 0.025,15,60 filled ls 11\n";
    o << "set key top left\n";
    o << "set title \"Heuristic\"\n";
    o << "set xlabel \"# states\"\n";
    o << "set ylabel \"heuristic\"\n";


    Graph::iterator gIt = graph.begin();
    Graph::iterator gEnd = graph.end();
    int min = graph.begin()->second.heuristic;
    bool changed = false;
    int indexChange = -1;
    for(int i=0;gIt!=gEnd;++gIt,++i){
        
        if(!gIt->second.children.empty() || gIt->second.heuristic==0){
            if(!changed && gIt->second.id >= changeSearch){
                changed = true;
                min = gIt->second.heuristic;
                indexChange = i;
            }
            if (gIt->second.heuristic<min)
                min = gIt->second.heuristic;            
        }
    }
    if(changeSearch!=-1){
        o << "set arrow from " << indexChange << ",graph(0,0) to "<< indexChange <<  ",graph(1,1) size screen 0.025,15,60 nohead filled ls 12\n";
        
    }
    
    
    o << "plot \"-\"  title \"heuristic\" with lines ls 1, \"-\" title \"min heuristic\" with lines ls 2\n";
    gIt = graph.begin();
    

    for(int i=0;gIt!=gEnd;++gIt,++i){
        if(!gIt->second.children.empty() || gIt->second.heuristic==0 )
            o << i << " " << gIt->second.heuristic << "\n";
    }
    o << "e\n";
    min = graph.begin()->second.heuristic;
    gIt = graph.begin();
    changed = false;
    for(int i=0;gIt!=gEnd;++gIt,++i){

        if(!gIt->second.children.empty() || gIt->second.heuristic==0){
            if(!changed && gIt->second.id >= changeSearch){
                changed = true;
                min = gIt->second.heuristic;
                indexChange = i;
            }
            if (gIt->second.heuristic<min)
                min = gIt->second.heuristic;
            o << i << " " << min << "\n";
            
        }
    }
    o << "e\n";
    
}

void DotSearchSpace::printGnuplotFile()
{
    nameGnuplot = nameFile.substr(0,nameFile.find("."));
    namePdf = nameGnuplot+".pdf";
    nameGnuplot += ".g";
    
    ofstream file(nameGnuplot.c_str(),std::ofstream::out);
    printGnuplotFile(file);
    file.close();
}




DotSearchSpace::Graph DotSearchSpace::graph = init_map();
string DotSearchSpace::nameFile;
string DotSearchSpace::nameGnuplot;
string DotSearchSpace::namePdf;
bool DotSearchSpace::addColor = false;
bool DotSearchSpace::addEdge = false;
bool DotSearchSpace::addHeuristic = false;
bool DotSearchSpace::writeFluents = false;
int DotSearchSpace::changeSearch = -1;
