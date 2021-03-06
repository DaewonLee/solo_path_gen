/*
 * gen_path.cpp
 *
 *  Created on: Sep 14, 2016
 *      Author: Daewon Lee
 *
 *
 *
 */
#include "gen_path.h"
#include <stdio.h>
CPathGen::CPathGen()
{
}

void CPathGen::setOrigin()
{
	return;
}

double CPathGen::dist(UTMVec p1, UTMVec p2)
{
	double d = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
	return d;
}

double CPathGen::heading(UTMVec p1, UTMVec p2)
{
	return atan2(p1.y - p2.y, p1.x - p2.x);
}

void CPathGen::circleTraj(UTMVec p1, UTMVec p2, double r, double angle, int ReferenceEllipsoid, const char* UTMZone, std::vector<double>* LLpathCircle_lon, std::vector<double>* LLpathCircle_lat, int direction)
{
	int i;
	int angle_prec = 10;
	double T_heading = PI + heading(p1, p2);
	UTMVec tmp_utm;
	LLVec tmp_path;
	std::vector<double> UTMpathCircle_x, UTMpathCircle_y;
	UTMpathCircle_x.clear();
	UTMpathCircle_y.clear();
	for(i=0; i < angle_prec+1; i++){
		tmp_utm.x = r*cos(T_heading) + p1.x;
		tmp_utm.y = r*sin(T_heading) + p1.y;
		UTMpathCircle_x.push_back(tmp_utm.x);
		UTMpathCircle_y.push_back(tmp_utm.y);
		
		UTMtoLL(ReferenceEllipsoid, tmp_utm.x, tmp_utm.y, UTMZone, tmp_path.lon, tmp_path.lat); 
		LLpathCircle_lon->push_back(tmp_path.lon);
		LLpathCircle_lat->push_back(tmp_path.lat);
		if(direction == CCW) T_heading += angle/angle_prec;
		else T_heading -= angle/angle_prec;
		
	}

	for(i=0; i < angle_prec+1; i++){
		if(direction == CCW) T_heading -= angle/angle_prec;
		else T_heading += angle/angle_prec;
		
		tmp_utm.x = r*cos(T_heading) + p1.x;
		tmp_utm.y = r*sin(T_heading) + p1.y;
		UTMpathCircle_x.push_back(tmp_utm.x);
		UTMpathCircle_y.push_back(tmp_utm.y);
		
		UTMtoLL(ReferenceEllipsoid, tmp_utm.x, tmp_utm.y, UTMZone, tmp_path.lon, tmp_path.lat); 
		LLpathCircle_lon->push_back(tmp_path.lon);
		LLpathCircle_lat->push_back(tmp_path.lat);

	}

}

void CPathGen::missionFile(std::vector<double>* LLpathCircle_lon, std::vector<double>* LLpathCircle_lat, const char* filename, LLVec p1, int height)
{
	FILE *file;
    	file = fopen(filename,"w");
    	char sprintf_buffer[10000];
	int sprintf_buffer_loc = 0;
    	int sprintf_size = sprintf(sprintf_buffer+sprintf_buffer_loc,"QGC WPL 110\n");
    	sprintf_buffer_loc+=sprintf_size;
    	
    	sprintf_size = sprintf(sprintf_buffer+sprintf_buffer_loc,"%d\t%d\t%d\t%d\t%e\t%d\t%d\t%d\t%e\t%e\t%d\t%d\n",1,0,0,16,0.15,0,0,0,p1.lat,p1.lon,height,1);
		    sprintf_buffer_loc+=sprintf_size;
		    
    	for(int i=0;i<LLpathCircle_lon->size();i++){
    	
	    	    sprintf_size = sprintf(sprintf_buffer+sprintf_buffer_loc,"%d\t%d\t%d\t%d\t%e\t%d\t%d\t%d\t%e\t%e\t%d\t%d\n",i+2,0,0,16,0.15,0,0,0,LLpathCircle_lat->at(i),LLpathCircle_lon->at(i),height,1);
		   
		    sprintf_buffer_loc+=sprintf_size;
	}		   
	
	sprintf_size = sprintf(sprintf_buffer+sprintf_buffer_loc,"%d\t%d\t%d\t%d\t%e\t%d\t%d\t%d\t%e\t%e\t%d\t%d\n",LLpathCircle_lon->size()+2,0,0,16,0.15,0,0,0,p1.lat,p1.lon,height,1);
		    sprintf_buffer_loc+=sprintf_size;
	
	printf("Saving buffer to a file.....  \n");
        fwrite(sprintf_buffer, 1, sprintf_buffer_loc,file);
        printf("free buffer file.....  \n");
        fclose(file); 
}

