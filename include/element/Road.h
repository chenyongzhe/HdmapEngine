
#ifndef _ROAD_H_
#define _ROAD_H_
#include <iostream>
#include "tinyxml/tinyxml2.h"
#include <string>
#include"element/LaneSection.h"
#include"element/StopLine.h"
#include"element/Crosswalk.h"
#include"element/TrafficLight.h"
using namespace std;
using namespace tinyxml2;
class Road
{
public:
	Road();
	Road(int road_id,string & predecessor_elementType,int predecessor_id, string successor_elementType,int successor_id);
	~Road();
	//道路id
	int road_id;
	//标记是否路口道路
	bool isJunctionRoad;
	string predecessor_elementType;
	int predecessor_id;
	int successor_id;
	string successor_elementType;

	double length=-1;
	//lanesection
	vector<LaneSection> laneSections;
	//停止线
	vector<StopLine> stopLines;
	//人行横道
    vector<Crosswalk> crosswalks;
    //交通灯
    vector<TrafficLight> trafficLights;


   double  getRoadLength(); 

	
};

#endif