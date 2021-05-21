
#ifndef _HDMAPENGINE_H_
#define _HDMAPENGINE_H_
#include <iostream>
#include "tinyxml/tinyxml2.h"
#include"element/Road.h"
#include"element/Lane.h"
#include<vector>
using namespace std;
using namespace tinyxml2;


class HdmapEngine
{

private :
    bool paserLaneSection(XMLElement* sectionNode,Road& road);
	bool paserLane(XMLElement* laneNode,LaneSection& laneSection);
	bool paserJunction(XMLElement* junctionNode);
	bool paserRoad(XMLElement* roadNode);
	void printRoad();
public:
	vector<Road> roadList;
	vector<Lane> laneList;
	vector<LaneSection> lansectionList;
	HdmapEngine();
	~HdmapEngine();
	bool paserApolloxml(const char* file_name);
	
	
};

#endif
