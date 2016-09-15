//constants.h

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "LatLong-UTMconversion.h"

const double PI = 3.14159265;
const double FOURTHPI = PI / 4;
const double deg2rad = PI / 180;
const double rad2deg = 180.0 / PI;
char msg0[] = "Placeholder";


static Ellipsoid ellipsoid[] = 
{//  id, Ellipsoid name, Equatorial Radius, square of eccentricity	
	Ellipsoid( -1, msg0, 0, 0),//placeholder only, To allow array indices to match id numbers
	Ellipsoid( 1, msg0, 6377563, 0.00667054),
	Ellipsoid( 2, msg0, 6378160, 0.006694542),
	Ellipsoid( 3, msg0, 6377397, 0.006674372),
	Ellipsoid( 4, msg0, 6377484, 0.006674372),
	Ellipsoid( 5, msg0, 6378206, 0.006768658),
	Ellipsoid( 6, msg0, 6378249, 0.006803511),
	Ellipsoid( 7, msg0, 6377276, 0.006637847),
	Ellipsoid( 8, msg0, 6378166, 0.006693422),
	Ellipsoid( 9, msg0, 6378150, 0.006693422),
	Ellipsoid( 10, msg0, 6378160, 0.006694605),
	Ellipsoid( 11, msg0, 6378137, 0.00669438),
	Ellipsoid( 12, msg0, 6378200, 0.006693422),
	Ellipsoid( 13, msg0, 6378270, 0.00672267),
	Ellipsoid( 14, msg0, 6378388, 0.00672267),
	Ellipsoid( 15, msg0, 6378245, 0.006693422),
	Ellipsoid( 16, msg0, 6377340, 0.00667054),
	Ellipsoid( 17, msg0, 6377304, 0.006637847),
	Ellipsoid( 18, msg0, 6378155, 0.006693422),
	Ellipsoid( 19, msg0, 6378160, 0.006694542),
	Ellipsoid( 20, msg0, 6378165, 0.006693422),
	Ellipsoid( 21, msg0, 6378145, 0.006694542),
	Ellipsoid( 22, msg0, 6378135, 0.006694318),
	Ellipsoid( 23, msg0, 6378137, 0.00669438)
};

#endif
