/*
 * main.cpp
 *
 *  Created on: Sep 14, 2016
 *      Author: Daewon Lee
 *
 *
 *
 */

#include "gen_path.h"
#include "ros/ros.h"
#include "std_msgs/Float64MultiArray.h"


UTMVec UTMtarget, UTMUAV;
LLVec LLtarget, LLUAV, LLtargetTest;
bool get_target = false;
bool get_UAV = false;
char UTMZone[4];
int RefEllipsoid = 23;

void targetGPSCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{	
	LLtarget.lon = msg->data[0];
	LLtarget.lat = msg->data[1];
	LLtarget.h = msg->data[2];
	
	LLtoUTM(RefEllipsoid, LLtarget.lon, LLtarget.lat, UTMtarget.x, UTMtarget.y, UTMZone); 
	get_target = true;
	return;
}

void UAVGPSCallback(const std_msgs::Float64MultiArray::ConstPtr& msg)
{
	LLUAV.lon = msg->data[0];
	LLUAV.lat = msg->data[1];
	LLUAV.h = msg->data[2];
	
	LLtoUTM(RefEllipsoid, LLUAV.lon, LLUAV.lat, UTMUAV.x, UTMUAV.y, UTMZone); 
	get_UAV = true;
	return;
}



int main(int argc, char **argv)
{
ros::init(argc, argv, "Path_Generator");
ros::NodeHandle nh;
ros::Subscriber target_gps_subscriber = nh.subscribe("/target_GPS", 10, targetGPSCallback);
ros::Subscriber UAV_gps_subscriber = nh.subscribe("/UAV_GPS", 10, UAVGPSCallback);
std::vector<double> LLpathCircle_lon, LLpathCircle_lat;
CPathGen target_path;
double d, heading;
int height = 10; //in meter
int direction = CCW;// = CCW;
double radius = 10.;
double angle = 250. * D2R;
target_path.setOrigin();


while(ros::ok())
	{
	
	ros::spinOnce();
	char const *missionFileName = "mission.txt";
	if(get_UAV == true && get_target == true) {
	
		d = target_path.dist(UTMtarget, UTMUAV);
		heading = target_path.heading(UTMtarget, UTMUAV);
		target_path.circleTraj(UTMtarget, UTMUAV, radius, angle, RefEllipsoid, UTMZone, &LLpathCircle_lon, &LLpathCircle_lat, direction);
		target_path.missionFile(&LLpathCircle_lon, &LLpathCircle_lat, missionFileName, LLUAV, height);
		
		ros::shutdown();
		}
	
	}

return 0;

}


