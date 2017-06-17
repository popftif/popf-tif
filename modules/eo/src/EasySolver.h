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


#ifndef EasySolver_H
#define EasySolver_H

#include "ExternalSolver.h"
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <cmath>

using namespace std;

#define PI (2*std::acos(0))

//struct patch {
//	int index;
//	double xEntry;
//	double yEntry;
//	double xExit;
//	double yExit;
//	patch(int _index, double _xEntry,	double _yEntry,	double _xExit,	double _yExit)
//	: index(_index), xEntry(_xEntry), yEntry(_yEntry), xExit(_xExit), yExit(_yExit) {}
//};
//
//struct patch_comparator {
//	bool operator()(patch const & a, patch const & b) {
//		return (a.index < b.index);
//	}
//};

struct patchInfo{
    double xEntry;
    double yEntry;
    double xExit;
    double yExit;
    double scanduration;
    patchInfo(){}
    patchInfo(double _xEntry,	double _yEntry,	double _xExit,	double _yExit, double _scanduration) : xEntry(_xEntry), yEntry(_yEntry), xExit(_xExit), yExit(_yExit), scanduration(_scanduration) {}
};

/**
 * Overload of "<<" to allow patchInfo to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, patchInfo const & pInfo)
{
    out << "{(" << pInfo.xEntry << ", " << pInfo.yEntry << "), (" << pInfo.xExit << ", " << pInfo.yExit << "), " << pInfo.scanduration << "s}";
    return out;
}


struct satelliteInfo{
    double xEntry;
    double yEntry;
    double xExit;
    double yExit;
    double xPos;
    double yPos;
    double overgroundHeight;
    double grVelocity;
    double angleVelocity;
    double maxAngle;
    double yawAngle;
    double pitchAngle;
    double rollAngle;
    double scanVelocity;
    satelliteInfo(){}
    satelliteInfo(double _xEntry,	double _yEntry,	double _xExit,	double _yExit, double _scanVelocity) : xEntry(_xEntry), yEntry(_yEntry), xExit(_xExit), yExit(_yExit), scanVelocity(_scanVelocity) {}
};

/**
 * Overload of "<<" to allow patchInfo to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, satelliteInfo const & pInfo)
{
    out << "satellite";
    return out;
}

/**
 * Satellite Pose - might later be modified to also include angle momentum
 */
struct satellitePose {
    double x;
    double y;
    double yaw;
    double roll;
    double pitch;
    satellitePose(double _x, double _y, double _yaw, double _roll, double _pitch)
    : x(_x), y(_y), yaw(_yaw), roll(_roll), pitch(_pitch) {}
    satellitePose(){}
};

/**
 * Overload of "<<" to allow satellite poses to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, satellitePose const & pose)
{
    out << "(" << pose.x << ", " << pose.y << " ["<< pose.yaw*(180/PI) <<"° "<<pose.roll*(180/PI) <<"° "<<pose.pitch*(180/PI)<< "°])";
    return out;
}

struct patchPose {
    string patchname;
    satellitePose satPose;
    patchPose(string _patchname, double _x, double _y, double _yaw, double _roll, double _pitch)
    : patchname(_patchname), satPose(satellitePose(_x, _y, _yaw, _roll, _pitch)) {}
};

/**
 * Overload of "<<" to allow patchPoses to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, patchPose const & paPose)
{
    out << "'" << paPose.patchname << "': " << paPose.satPose;
    return out;
}

struct storedResults {
    satellitePose endPose;
    double maneuverTime;
    storedResults(): endPose(satellitePose(-2,-2,-2,-2,-2)), maneuverTime(-2) {}
};

/**
 * Overload of "<<" to allow patchPoses to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, storedResults const & res)
{
    out << res.endPose << " - " << res.maneuverTime << "s";
    return out;
}

struct patchPose_comparator {
    bool operator()(patchPose const & a, patchPose const & b) {
        if (a.patchname != b.patchname) return a.patchname < b.patchname;
        if (a.satPose.x != b.satPose.x) return a.satPose.x < b.satPose.x;
        if (a.satPose.y != b.satPose.y) return a.satPose.y < b.satPose.y;
        if (a.satPose.yaw != b.satPose.yaw) return a.satPose.yaw < b.satPose.yaw;
        if (a.satPose.roll != b.satPose.roll) return a.satPose.roll < b.satPose.roll;
        return a.satPose.pitch < b.satPose.pitch;
	   }
};


/**
 * two dimensional vector with the default vector operations
 */
struct vector2d{
    double x;
    double y;
    vector2d(double _x, double _y): x(_x), y(_y){};
    double operator*(vector2d const & right) { // scalar product
        return x*right.x + y*right.y;
    }
    vector2d operator*(double const & scalar) { // scalar multiplication / dilation
        return vector2d(x*scalar, y*scalar);
    }
    vector2d operator+(vector2d const & right) { // vector addition
        return vector2d(x + right.x, y + right.y);
    }
    vector2d operator-(vector2d const & right) { // vector subtraction
        return vector2d(x - right.x, y - right.y);
    }
    void normalize() {
        double l = length();
        x /= l;
        y /= l;
    }
    vector2d normalized() {
        return vector2d(x / length(), y / length());
    }
    double length() {
        return std::sqrt(x*x + y*y);
    }
};

/**
 * Overload of "<<" to allow vector2d be printed by cout
 */
std::ostream& operator<< (std::ostream &out, vector2d const & vec)
{
    out << "(" << vec.x << ", " << vec.y << ")";
    return out;
}


static int modulecalls = 0;

static std::map<std::string, patchInfo> patchMap;

static std::map<patchPose, storedResults, patchPose_comparator> approachMap;
static std::map<patchPose, storedResults, patchPose_comparator> scanMap;

static int scanTimeHeuristic = 0;
static int scanTimeCalls = 0;
static int scanTimeDatabase = 0;
static int scanTimeFresh = 0;

static int approachTimeHeuristic = 0;
static int approachTimeCalls = 0;
static int approachTimeDatabase = 0;
static int approachTimeFresh = 0;

class EasySolver : public ExternalSolver
{
public:
    EasySolver();
    ~EasySolver();
    virtual void loadSolver(string* parameters, int n);
    virtual map<string,double> callExternalSolver(map<string,double> initialState, bool isHeuristic);
    virtual  list<string> getParameters();
    virtual  list<string> getDependencies();
private:
    list<string> affected;
    list<string> dependencies;
    void parseParameters(string parameters);
    map<string,patchInfo> mapPatches;
    map<string,satelliteInfo> mapSatellites;
    double scanVelocity;
    map<string,double> mapFluents;
    void parseFluents();
    void scanEffects(map<string,double> &toReturn, string patch, string sat,map<string, satellitePose> mapPose);
    void targetEffects(map<string,double> &toReturn, string patch, string sat,map<string, satellitePose>& mapPose);
    double targetingTimeOfPatch(map<string,double> &toReturn, string patch, string sat,map<string, satellitePose> mapPose);
    double endPoseAfterScanning(map<string,double> &toReturn, string patch, string sat,map<string, satellitePose> mapPose);
};

#endif // EasySolver_H
