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


#include "Color.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#include <sstream> 

using namespace std;

Color::Color(){
    red = 0.;
    green = 0.;
    blue = 0.;
    hex = fromRGB2Hex(red, green, blue);
}
Color::Color(int r, int g, int b){
    red = r;
    green = g;
    blue = b;
    hex = fromRGB2Hex(red, green, blue);
}

string Color::fromRGB2Hex(int red, int green, int blue){
    return '#' + byte2Hex(red%256) + byte2Hex(green%256) + byte2Hex(blue%256);
}
string Color::byte2Hex(int number){
    stringstream toReturn;
    toReturn << std::setfill ('0') << std::setw (2) << std::hex << number;
    return toReturn.str();
}

void makeColorGradien(double frequency1, double frequency2, double frequency3, double phase1, double phase2, double phase3, double center, double width, int len, Color color[]){
    for(int i=0; i<len; ++i){
        int red = sin(frequency1*i+phase1)*width + center;
        int green = sin(frequency2*i+phase2)*width + center;    
        int blue = sin(frequency3*i+phase3)*width + center;
        color[i] = Color(red, green, blue);
        cout << color[i].getRed() << " " << color[i].getGreen() << " " << color[i].getBlue() << endl;
    }
    
}

void makeColorGradien(double frequency, double phase1, double phase2, double phase3, double center, double width, int len, Color color[]){
    
    makeColorGradien(frequency, frequency, frequency, phase1, phase2, phase3, center, width, len, color);
}

void makeColorGradien(double frequency, double phase, double center, double width, int len, Color color[]){
    
    makeColorGradien(frequency, phase, 2*phase+acos(-1)/3., phase+4*acos(-1)/3., center, width, len, color);
}

void makeColorGradien(double frequency, double center, double width, int len, Color color[]){
    
    makeColorGradien(frequency, 0, center, width, len, color);
}

void makeGreyGradien(double frequency, double phase, double center, double width, int len, Color color[]){
    
    makeColorGradien(frequency, phase, phase, phase, center, width, len, color);
}

Color createColor(double i, double min, double max, double center, double width){
    double ratio = 2*(i-min)/(max-min)/3.;
    int red = 0;
    int green = 0;
    int blue = 0;
    int c = 0;
    if(ratio<=1./6. && ratio>=0){
        red = 255-c;
        green = int(6*ratio*255)+c;
        blue = 0+c;
    }
    if(ratio > 1./6. && ratio <= 1./3.){
        red = int((-6*ratio+2)*255)+c;
        green = 255-c;
        blue = 0+c;
    }
    if(ratio <= 1./2 && ratio > 1./3.){
        green = 255-c;
        blue = int((6*ratio-2)*255)+c;
        red = 0+c;
    }
    if(ratio>1./2) {
        green = int((-6*ratio+4)*255)+c;
        blue = 255-c;         
        red = 0+c;
    }

    return Color(red, green, blue);
}

Color createColor2(double i, double min, double max, double center, double width){
    double angle = i *2*acos(-1)/(max-min);
    int red = sin(angle)*width + center;
    int green = sin(angle+2*acos(-1)/3.)*width + center;
    int blue = sin(angle+4*acos(-1)/3.)*width + center;
    return Color(red, green, blue);
}
