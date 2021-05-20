
#ifndef _HDMAPENGINE_H_
#define _HDMAPENGINE_H_
#include <iostream>
#include "tinyxml2.h"
#include"element/Road.h"
#include"element/Lane.h"
#include<vector>
using namespace std;
using namespace tinyxml2;


class HdmapEngine
{
public:
	vector<Road> roadList;
	vector<Lane> LaneList;
	HdmapEngine();
	~HdmapEngine();
	void printRoad();
	bool paserApolloxml(const char* file_name);
	
};

#endif
