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


#ifndef DOTSEARCHSPACE_H
#define DOTSEARCHSPACE_H
#include <map>
#include <list>
#include <string>
#include <ostream>

using namespace std;



class DotSearchSpace
{
    
public:
    struct Node{
        Node(int i, string n, int h) : id(i), name(n), heuristic(h){};
        int id;
        string name;
        list<int> children;
        int heuristic;
    };
    typedef map<int,Node> Graph;
    static Graph graph;
    static string nameFile;
    static string nameGnuplot;
    static string namePdf;
    static bool addColor;
    static bool addEdge;
    static bool addHeuristic;
    static void printDotFile(ostream &o);
    static void printDotFile(string nameFile);
    static void printDotFile();
    static void addNode(int i, string n, int h, int idParent);
    static void printGnuplotFile(ostream &o);
    static void printGnuplotFile();
    static int changeSearch;
    static bool writeFluents;
private:
    static Graph init_map(){
        Graph graph;
        return graph;        
    }
};

#endif // DOTSEARCHSPACE_H
