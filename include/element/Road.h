
#ifndef _ROAD_H_
#define _ROAD_H_
#include <iostream>
#include "tinyxml/tinyxml2.h"
#include <string>
#include"element/LaneSection.h"
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
	string predecessor_elementType;
	int predecessor_id;
	int successor_id;
	string successor_elementType;

	double length=-1;
	vector<LaneSection> laneSections;

   double  getRoadLength(); 

	
};

#endif