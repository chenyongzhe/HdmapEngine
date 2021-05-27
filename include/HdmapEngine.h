
#ifndef _HDMAPENGINE_H_
#define _HDMAPENGINE_H_
#include <iostream>
#include "tinyxml/tinyxml2.h"
#include"element/Road.h"
#include"element/Lane.h"
#include"element/Connection.h"
#include"element/Junction.h"
#include"element/LaneSection.h"
#include"element/StopLine.h"
#include"element/Crosswalk.h"
#include"element/TrafficLight.h"
#include<vector>
#include<map>
using namespace std;
using namespace tinyxml2;
#include"tools/TransformUtil.h"
#include"tools/KDTree.h"



class HdmapEngine
{

private :
    //解析Lanesection
    bool paserLaneSection(XMLElement* sectionNode,Road* road);
    //解析Lane
	bool paserLane(XMLElement* laneNode,LaneSection* laneSection);
	//解析 Junction
	bool paserJunction(XMLElement* junctionNode);
	//解析 Road
	bool paserRoad(XMLElement* roadNode);
	
	//解析StopLineCrosswalk
	bool paserStopLineCrosswalk(XMLElement* roadNode,Road *road);
	//解析信号灯
	bool paserTrafficLight(XMLElement* roadNode,Road *road);

public:
	//lane哈希表,用于通过uid快速搜索车道
	map<string,Lane*> laneMap;
	//road 哈希表用于 通过id快速搜索道路
	map<int,Road*> roadMap;
	//lanesection哈希表,用于通过id快速搜索lanesection
	map<int,LaneSection*> laneSectionMap;
	//Junction哈希表，用于通过id快速搜索Junction
	map<int, Junction> junctionMap;
	//connection哈希表，用于通过vitruallane_id快速搜索路口连接关系
	map<string,Connection*> connectionMap;
	//stopLine哈希表，用于通过id快速搜索停车线
	map<string,StopLine> stopLineMap;
	//道路列表
	vector<Road *> roadList;
	//车道列表
	vector<Lane*> laneList;
	//lansection列表
	vector<LaneSection*> lansectionList;
	//junction列表
	vector<Junction> junctionList;
	//connection列表 
	vector<Connection*> connectionList;

	HdmapEngine(double lat,double lon,double alt);
	~HdmapEngine();
	//解析apollo xml函数
	bool paserApolloxml(const char* file_name);
	//打印基本信息
	void printBaseInfo();
	Road * getRoadBetweenJunctions(Junction& jun_first,Junction& jun_second);

	//通过坐标搜索出车道
    Lane * searchLaneByxy(double x,double y);

	//坐标转化工具
	TransformUtil* trans;
	//搜索树
	KDTree* tree;
	//搜索当前车道内distance 范围内的车道中心点 point
	vector<Point* > searchPoints(double x, double y, double distance);
	
	
};

#endif
