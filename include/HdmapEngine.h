
#ifndef _HDMAPENGINE_H_
#define _HDMAPENGINE_H_
#include <iostream>
#include "tinyxml/tinyxml2.h"
#include"element/Road.h"
#include"element/Lane.h"
#include"element/Connection.h"
#include"element/Junction.h"
#include"element/LaneSection.h"
#include<vector>
#include<map>
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
	map<string,Lane> laneMap;
	map<int,Road> roadMap;
	map<int,LaneSection> laneSectionMap;
	map<int, Junction> junctionMap;
	map<string,Connection> connectionMap;
	vector<Road> roadList;
	vector<Lane> laneList;
	vector<LaneSection> lansectionList;
	vector<Junction> junctionList;
	vector<Connection> connectionList;
	HdmapEngine();
	~HdmapEngine();
	bool paserApolloxml(const char* file_name);
	
	
};

#endif
