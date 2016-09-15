/*
 * gen_path.h
 *
 *  Created on: Sep 14, 2016
 *      Author: Daewon Lee
 *
 *
 *
 */

#include "LatLong-UTMconversion.h"
#include <iostream>
#include <math.h>
#include <vector>
#include "LatLong-UTMconversion.h"
#include <stdio.h>
#define PI 3.14159265359
#define CW 0
#define CCW 1
#define R2D 180/PI
#define D2R PI/180

struct UTMVec{
	double x,y,h;
};

struct LLVec{
	double lon,lat,h;
};

class CPathGen {
public:
	CPathGen();
	~CPathGen(){}
	void setOrigin();
	double dist(UTMVec p1, UTMVec p2);
	
	// p1: target,   p2: UAV
	double heading(UTMVec p1, UTMVec p2);
	
	// r: radius in meter,   angle: in radian
	void circleTraj(UTMVec p1, UTMVec p2, double r, double angle, int ReferenceEllipsoid, const char* UTMZone, std::vector<double>* LLpathCircle_lon, std::vector<double>* LLpathCircle_lat, int direction);
	void missionFile(std::vector<double>* LLpathCircle_lon, std::vector<double>* LLpathCircle_lat, const char* filename, LLVec p1, int height);

protected:

};

