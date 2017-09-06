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


#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <string>

using namespace std;

class Color{
public:
    Color();
    Color(int red, int green, int blue);
    //Color(string hex);
    int getRed(){
        return red;
    };
    int getGreen(){
        return green;
    }
    int getBlue(){
        return blue;
    }
    string getHex(){
        return hex;
    }
private:
    string hex;
    int red;
    int green;
    int blue;
    string fromRGB2Hex(int red, int green, int blue);
    int* fromHex2RGB(string Hex);
    string byte2Hex(int number);
};

void makeColorGradien(double frequency1, double frequency2, double frequency3, double phase1, double phase2, double phase3, double center, double width, int len = 50, Color color[] = NULL);

void makeColorGradien(double frequency, double phase1, double phase2, double phase3, double center, double width, int len = 50, Color color[] = NULL);

void makeColorGradien(double frequency, double phase, double center, double width, int len = 50, Color color[] = NULL);

void makeColorGradien(double frequency, double center, double width, int len = 50, Color color[] = NULL);

void makeGrayGradien(double frequency, double phase, double center, double width, int len = 50, Color color[] = NULL);

Color createColor(double i, double min, double max, double center = 128., double width = 127.);

Color createColor2(double i, double min, double max, double center = 128., double width = 127.);

#endif // COLOR_H
