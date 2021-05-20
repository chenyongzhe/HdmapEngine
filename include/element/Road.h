
#ifndef _ROAD_H_
#define _ROAD_H_
#include <iostream>
#include "tinyxml2.h"
#include <string>
#include"element/LaneSection.h"
using namespace std;
using namespace tinyxml2;
class Road
{
public:
	Road();
	Road(int road_id,string & predecessor_elementType,int predecessor_id, string successor_elementType,int successor_id,double road_length);
	~Road();
	//道路id
	int road_id;
	string predecessor_elementType;
	int predecessor_id;
	int successor_id;
	string successor_elementType;

	double road_length=-1;
	vector<LaneSection> LaneSections;

 static  double  parser_length_fromxML(XMLElement* lanes); 

	
};

#endif