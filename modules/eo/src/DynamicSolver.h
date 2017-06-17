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


#ifndef DynamicSolver_H
#define DynamicSolver_H

#include "ExternalSolver.h"
#include <string>
#include <vector>
#include <map>
#include <math.h>
#include <cmath>
#include <assert.h>
#include <limits>

using namespace std;

#define PI (2*std::acos(0))

/**
 * three dimensional vector with the default vector operations
 */
struct vector3d{
    double x;
    double y;
    double z;
    vector3d(){}
    vector3d(double _x, double _y, double _z): x(_x), y(_y), z(_z){};
    double operator*(vector3d const & right) const { // scalar product
        return x*right.x + y*right.y + z*right.z;
    }
    vector3d operator*(double const & scalar) const { // scalar multiplication / dilation
        return vector3d(x*scalar, y*scalar, z*scalar);
    }
    vector3d operator+(vector3d const & right) { // vector addition
        return vector3d(x + right.x, y + right.y, z+ right.z);
    }
    vector3d operator-(vector3d const & right) { // vector subtraction
        return vector3d(x - right.x, y - right.y, z - right.z);
    }
    double length() {
        return std::sqrt(x*x + y*y + z*z);
    }
    void normalize() {
        double l = length();
        x /= l;
        y /= l;
        z /= l;
    }
    vector3d normalized() {
        return vector3d(x / length(), y / length(), z / length() );
    }
};

/**
 * Overload of "<<" to allow vector3d be printed by cout
 */
std::ostream& operator<< (std::ostream &out, vector3d const & vec)
{
    out << "(" << vec.x << ", " << vec.y << ", " << vec.z <<")";
    return out;
}

struct matrix3d{
    double a1, a2, a3;
    double b1, b2, b3;
    double c1, c2, c3;
    matrix3d(){}
    matrix3d(double _a1, double _a2, double _a3,
             double _b1, double _b2, double _b3,
             double _c1, double _c2, double _c3) : a1(_a1), a2(_a2), a3(_a3),
    b1(_b1), b2(_b2), b3(_b3),
    c1(_c1), c2(_c2), c3(_c3) {}
    vector3d row1() const {
        return vector3d(a1, a2, a3);
    }
    vector3d row2() const {
        return vector3d(b1, b2, b3);
    }
    vector3d row3() const {
        return vector3d(c1, c2, c3);
    }
    vector3d col1() const {
        return vector3d(a1, b1, c1);
    }
    vector3d col2() const {
        return vector3d(a2, b2, c2);
    }
    vector3d col3() const {
        return vector3d(a3, b3, c3);
    }
    matrix3d operator*(const matrix3d & right) {//matrix multiplication
        return matrix3d(row1()*right.col1(), row1()*right.col2(), row1()*right.col3(),
                        row2()*right.col1(), row2()*right.col2(), row2()*right.col3(),
                        row3()*right.col1(), row3()*right.col2(), row3()*right.col3());
    }
    vector3d operator*(vector3d const & right) {
        return vector3d(row1()*right, row2()*right, row3()*right);
    }
    matrix3d operator*(double const & scalar) { // scalar multiplication / dilation
        return matrix3d(a1*scalar, a2*scalar, a3*scalar,
                        b1*scalar, b2*scalar, b3*scalar,
                        c1*scalar, c2*scalar, c3*scalar);
        
    }
    matrix3d inverse() {
        double det = 1/(a1*b2*c3-a1*b3*c2-a2*b1*c3+a2*b3*c1+a3*b1*c2-a3*b2*c1);
        matrix3d invM = matrix3d(b2*c3-b3*c2, a3*c2-a2*c3, a2*b3-a3*b2,
                                 b3*c1-b1*c3, a1*c3-a3*c1, a3*b1-a1*b3,
                                 b1*c2-b2*c1, a2*c1-a1*c2, a1*b2-a2*b1);
        return invM * det;
    }
};

/**
 * Overload of "<<" to allow matrix3d be printed by cout
 */
std::ostream& operator<< (std::ostream &out, matrix3d const & mat)
{
    out << "((" << mat.a1 << ",\t" << mat.a2 << ",\t" << mat.a3 << ");\n"
    << " (" << mat.b1 << ",\t" << mat.b2 << ",\t" << mat.b3 << ");\n"
    << " (" << mat.c1 << ",\t" << mat.c2 << ",\t" << mat.c3 << "))\n";
    return out;
}



struct patchInfo{
    std::string name;
    vector3d entry;
    vector3d exit;
    double firstX;
    bool firstXknown;
    double lastX; // last possible scan position
    bool lastXknown;
    double scanvelocity;
    bool scanvelocityknown;
    double scanduration;
    bool scandurationknown;
    std::string belongsto; // (belongsto ?patch ?observationsite)
    bool belongstoknown;
    std::string scannedby; //(scannedby ?patch ?sat)
    bool scannedbyknown;
    patchInfo() : firstXknown(false), lastXknown(false), scanvelocityknown(false), scandurationknown(false), belongstoknown(false), scannedbyknown(false) {}
    patchInfo(string _name, vector3d _entry, vector3d _exit) :
    name(_name),
    entry(_entry),
    exit(_exit),
    firstX(0),
    firstXknown(false),
    lastX(0),
    lastXknown(false),
    scanvelocity(0),
    scanvelocityknown(false),
    scanduration(0),
    scandurationknown(false),
    belongsto(""),
    belongstoknown(false),
    scannedby(""),
    scannedbyknown(false) {}
    void setScanduration(double dura) {
        if(scandurationknown) {
            if (scanduration != dura)
                std::cout << "Inconsistency in scanduration discovered. Try to replace " << scanduration << " with " << dura << ". aborting..." <<std::endl;
            assert(scanduration == dura);
        } else {
            scandurationknown=true;
            scanduration = dura;
        }
    }
    void setScanvelocity(double velo) {
        if(scanvelocityknown){
            if (scanvelocity != velo)
                std::cout << "Inconsistency in scanvelocity discovered. Try to replace " << scanvelocity << " with " << velo << ". aborting..." <<std::endl;
            assert(scanvelocity==velo);
        } else {
            scanvelocityknown=true;
            scanvelocity = velo;
        }
    }
    void setfirstX(double first) {
        assert(!firstXknown);
        firstXknown=true;
        firstX=first;
    }
    void setlastX(double last) {
        assert(!lastXknown);
        lastXknown=true;
        lastX=last;
    }
    void setObservationSite(std::string ositename) {
        assert(!belongstoknown);
        belongstoknown=true;
        belongsto=ositename;
    }
    void setScanningSatellite(std::string satname) {
        if(scannedbyknown)
            assert(scannedby==satname);
        else {
            scannedbyknown=true;
            scannedby=satname;
        }
    }
    void print() {
        std::cout << "Patch name: >" << name << "<" << std::endl;
        std::cout << "Entry coordinates: " << entry << std::endl;
        std::cout << "Exit coordinates: " << exit << std::endl;
        std::cout << (belongstoknown?"[X] ":"[ ] ") << " belongsto: " << belongsto << std::endl;
        std::cout << (firstXknown?"[X] ":"[ ] ") << " firstX: " << firstX << std::endl;
        std::cout << (lastXknown?"[X] ":"[ ] ") << " lastX: " << lastX << std::endl;
        std::cout << (scandurationknown?"[X] ":"[ ] ") << " scanduration: " << scanduration << std::endl;
        std::cout << (scannedbyknown?"[X] ":"[ ] ") << " scannedby: " << scannedby << std::endl;
        std::cout << (scanvelocityknown?"[X] ":"[ ] ") << " scanvelocity: " << scanvelocity << std::endl;
    }
    
};

/**
 * Overload of "<<" to allow patchInfo to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, patchInfo const & pInfo)
{
    out << "{(" << pInfo.entry.x << ", " << pInfo.entry.y << ", " << pInfo.entry.z << "), (" << pInfo.exit.x << ", " << pInfo.exit.y << ", " << pInfo.exit.z << "), " << pInfo.scanduration << "s}";
    return out;
}

/**
 * Satellite Info
 *
 * Full Information accessible by the modules
 */
struct satelliteInfo {
    std::string name;
    double xPos;
    double xHorizon;
    double rollMaxN;
    double pitchMaxN;
    double angRateXmaxN;
    double angRateYmaxN;
    double angRateZmaxN;
    double angAccMaxN;
    double roll;
    double pitch;
    double yaw;
    double rollRate;
    double pitchRate;
    double yawRate;
    double vSubT;
    satelliteInfo(): name(""),
    xPos(std::numeric_limits<double>::max()),
			 xHorizon(std::numeric_limits<double>::max()),
			 rollMaxN(std::numeric_limits<double>::max()),
			 pitchMaxN(std::numeric_limits<double>::max()),
			 angRateXmaxN(std::numeric_limits<double>::max()),
			 angRateYmaxN(std::numeric_limits<double>::max()),
			 angRateZmaxN(std::numeric_limits<double>::max()),
			 angAccMaxN(std::numeric_limits<double>::max()),
			 roll(std::numeric_limits<double>::max()),
			 pitch(std::numeric_limits<double>::max()),
			 yaw(std::numeric_limits<double>::max()),
			 rollRate(std::numeric_limits<double>::max()),
			 pitchRate(std::numeric_limits<double>::max()),
			 yawRate(std::numeric_limits<double>::max()),
			 vSubT(std::numeric_limits<double>::max())
    {};
    satelliteInfo(
                  std::string _name,
                  double _xPos,
                  double _xHorizon,
                  double _rollMaxN,
                  double _pitchMaxN,
                  double _angRateXmaxN,
                  double _angRateYmaxN,
                  double _angRateZmaxN,
                  double _angAccMaxN,
                  double _roll,
                  double _pitch,
                  double _yaw,
                  double _rollRate,
                  double _pitchRate,
                  double _yawRate,
                  double _vSubT
                  ): name(_name),
    xPos(_xPos),
    xHorizon(_xHorizon),
    rollMaxN(_rollMaxN),
    pitchMaxN(_pitchMaxN),
    angRateXmaxN(_angRateXmaxN),
    angRateYmaxN(_angRateYmaxN),
    angRateZmaxN(_angRateZmaxN),
    angAccMaxN(_angAccMaxN),
    roll(_roll),
    pitch(_pitch),
    yaw(_yaw),
    rollRate(_rollRate),
    pitchRate(_pitchRate),
    yawRate(_yawRate),
    vSubT(_vSubT) {}
};

struct satellitePose {
    double x;
    double yaw;
    double roll;
    double pitch;
    double yawRate;
    double rollRate;
    double pitchRate;
    satellitePose(double _x, double _yaw, double _roll, double _pitch)
    : x(_x), yaw(_yaw), roll(_roll), pitch(_pitch) {}
    satellitePose(){}
};

/**
 * Overload of "<<" to allow satellite poses to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, satellitePose const & pose)
{
    out << "(" << pose.x << ", " /*<< pose.y */<< " ["<< pose.yaw*(180/PI) <<"° "<<pose.roll*(180/PI) <<"° "<<pose.pitch*(180/PI)<< "°])";
    return out;
}
/**
 * Satellite State
 */
struct satelliteState {
    double x;
    double roll;
    double pitch;
    double yaw;
    double rollRateN;
    double pitchRateN;
    double yawRateN;
    
    satelliteState(double _x, double _roll, double _pitch, double _yaw, double _rollRateN, double _pitchRateN, double _yawRateN)
    : x(_x), roll(_roll), pitch(_pitch), yaw(_yaw), rollRateN(_rollRateN), pitchRateN(_pitchRateN), yawRateN(_yawRateN) {}
    
    satelliteState() {satelliteState(0,0,0,0,0,0,0);}
    satelliteState(satelliteInfo satinfo) : x(satinfo.xPos), roll(satinfo.roll), pitch(satinfo.pitch), yaw(satinfo.yaw), rollRateN(satinfo.rollRate), pitchRateN(satinfo.pitchRate), yawRateN(satinfo.yawRate) {}
};

/**
 * Overload of "<<" to allow satellite states to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, satelliteState const & pose)
{
    out << "(" << pose.x << " ["<< pose.roll <<" "<<pose.pitch <<" "<<pose.yaw<< "]rad, ["<< pose.rollRateN <<" "<<pose.pitchRateN <<" "<<pose.yawRateN << "]rad/s)";
    return out;
}

/**
 * patchPose is storing a Satellite state when entering or exiting a patch
 */
struct patchPose {
    std::string patchname;
    satelliteState satPose;
    patchPose(string _patchname, double _x, double _roll, double _pitch, double _yaw, double _rollRateN, double _pitchRateN, double _yawRateN)
    : patchname(_patchname), satPose(satelliteState(_x, _roll, _pitch, _yaw, _rollRateN, _pitchRateN, _yawRateN)) {}
};

/**
 * Overload of "<<" to allow patchPoses to be printed by cout
 */
std::ostream& operator<< (std::ostream &out, patchPose const & paPose)
{
    out << "'" << paPose.patchname << "': " << paPose.satPose;
    return out;
}

struct satPosAndPatch {
    double x;
    // double v_sat;
    std::string patchName;
    bool entry; // true: entry false: exit
    satPosAndPatch(double _x,
                   //double _v_sat,
                   std::string _patchName, bool _entry) : x(_x),
    //v_sat(_v_sat),
    patchName(_patchName), entry(_entry) {}
};


struct satStatePair_comparator {
    bool operator()(std::pair<satelliteState,satelliteState> const & a, std::pair<satelliteState,satelliteState> const & b) {
        if (a.first.x != b.first.x) return a.first.x < b.first.x;
        if (a.first.roll != b.first.roll) return a.first.roll < b.first.roll;
        if (a.first.pitch != b.first.pitch) return a.first.pitch < b.first.pitch;
        if (a.first.yaw != b.first.yaw) return a.first.yaw < b.first.yaw;
        if (a.first.rollRateN != b.first.rollRateN) return a.first.rollRateN < b.first.rollRateN;
        if (a.first.pitchRateN != b.first.pitchRateN) return a.first.pitchRateN < b.first.pitchRateN;
        if (a.first.yawRateN != b. first.yawRateN) return a.first.yawRateN < b.first.yawRateN;
        if (a.second.x != b.second.x) return a.second.x < b.second.x;
        if (a.second.roll != b.second.roll) return a.second.roll < b.second.roll;
        if (a.second.pitch != b.second.pitch) return a.second.pitch < b.second.pitch;
        if (a.second.yaw != b.second.yaw) return a.second.yaw < b.second.yaw;
        if (a.second.rollRateN != b.second.rollRateN) return a.second.rollRateN < b.second.rollRateN;
        if (a.second.pitchRateN != b.second.pitchRateN) return a.second.pitchRateN < b.second.pitchRateN;
        return a.second.yawRateN < b.second.yawRateN;
	   }
};


struct satPosAndPatch_comparator {
    bool operator()(satPosAndPatch const & a, satPosAndPatch const & b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.patchName != b.patchName) return a.patchName < b.patchName;
        return a.entry < b.entry;
    }
};

struct stateAndPatchname {
    satelliteState pose;
    std::string patchName;
    stateAndPatchname(satelliteState _pose, std::string _patchName) : pose(_pose), patchName(_patchName) {}
};

struct stateAndPatchname_comparator {
    bool operator()(stateAndPatchname const & a, stateAndPatchname const & b) {
        if (a.pose.x != b.pose.x) return a.pose.x < b.pose.x;
        if (a.pose.roll != b.pose.roll) return a.pose.roll < b.pose.roll;
        if (a.pose.pitch != b.pose.pitch) return a.pose.pitch < b.pose.pitch;
        if (a.pose.yaw != b.pose.yaw) return a.pose.yaw < b.pose.yaw;
        if (a.pose.rollRateN != b.pose.rollRateN) return a.pose.rollRateN < b.pose.rollRateN;
        if (a.pose.pitchRateN != b.pose.pitchRateN) return a.pose.pitchRateN < b.pose.pitchRateN;
        if (a.pose.yawRateN != b. pose.yawRateN) return a.pose.yawRateN < b.pose.yawRateN;
        return a.patchName < b.patchName;
    }
};


static int modulecalls = 0;

// patchName -> all Informations found in the Planer State concerning the patch
static std::map<std::string, patchInfo> patchMap;

//pair(satelliteStateFrom,satelliteStateTo) -> bool // stores feasibility of maneuver from first to second satellite state
static std::map<std::pair<satelliteState,satelliteState>, bool, satStatePair_comparator> maneuverDatabase;

// (current satellite xPosition; patchName; entry/exit) -> satellitePose
// stores the state of the satellite from the current position to start or end of the patch
static std::map<satPosAndPatch, satelliteState, satPosAndPatch_comparator> satPoseDatabase;

//(current satellite State and target patch) -> distance (x-subtrack) to the approach pose for the patch
static std::map<stateAndPatchname, double, stateAndPatchname_comparator> approachPointDatabase;

static int scanTimeHeuristic = 0;
static int scanTimeCalls = 0;
static int scanTimeDatabase = 0;
static int scanTimeFresh = 0;

static int approachTimeHeuristic = 0;
static int approachTimeCalls = 0;
static int approachTimeDatabase = 0;
static int approachTimeFresh = 0;

static int approachPointInsert = 0;
static int approachPointLookup = 0;

static int maneuverDatabaseInsert = 0;
static int maneuverDatabaseLookup = 0;

static int satPoseDatabaseInsert = 0;
static int satPoseDatabaseLookup = 0; 

static int patchMapInsert = 0;
static int patchMapLookup = 0;


class DynamicSolver : public ExternalSolver
{
public:
    DynamicSolver();
    ~DynamicSolver();
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
    map<string,string> mapBelongs;
    double scanVelocity;
    map<string,double> mapFluents;
    void parseFluents();
    void scanEffects(map<string,double> &toReturn, string patch, string sat, string osite, map<string, satellitePose> mapPose);
    void targetEffects(map<string,double> &toReturn, string patch, string sat, string osite, map<string, satellitePose>& mapPose);
    double targetingTimeOfPatch(map<string,double> &toReturn, string patch, string sat, string osite, map<string, satellitePose> mapPose);
    double scanTimeOfPatch(map<string,double> &toReturn, string patch, string sat, string osite, map<string, satellitePose> mapPose);
    double endPoseAfterScanning(map<string,double> &toReturn, string patch, string sat, string osite, map<string, satellitePose> mapPose);
    bool fetchWorldState(string patch, string sat, string osite, map<string, satellitePose> mapPose, patchInfo & patinfo, satelliteInfo & satinfo);

};

#endif // DynamicSolver_H
