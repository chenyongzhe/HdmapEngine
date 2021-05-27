
#ifndef _LANE_H_
#define _LANE_H_

#include<string>
#include <iostream>
#include "tinyxml/tinyxml2.h"
#include<vector>
#include"element/Point.h"
using namespace std;
using namespace tinyxml2;

using namespace std;
//车道宽度

struct WidthsampleAssociate
{
	double sOffset;
	double leftWidth;
	double rightWidth;
	double width;
} ;
//车道类型
struct BorderType
{
	string type;
	string color;
	double sOffset;
	double eOffset;
	
};


class Lane
{
public:
	Lane();
	~Lane();
	//车道id
	int id;
	//车道uid
	string uid;
	//车道前驱id 可能多个前驱
	vector<string> predecessors;
	//车道后继id 可能多个后继
	vector<string> successors;
	//左邻近同向车道
	string leftNeighbor_sameDirect_id;
	//左邻近不同向车道
	string leftNeighbor_reverseDirect_id;
	//右邻近同向车道
	string rightNeighbor_sameDirect_id;
	//右邻近不同向车道
	string rightNeighbor_reverseDirect_id;
	//所在道路id
	int road_id;
	//车道长度
	double lane_length=-1;
	//车道转向类型
	string turn_type;
	//车道限速 km/h
	double speed_limit;
	//车道类型
	string type;
	//车道方向:forward、backward、bidirection unknow ....
	string direction;
	//车道中心点参考线（离散点）
	 vector<Point*> centerLinePoints;

	 //车道宽度采样
    vector<WidthsampleAssociate> widthsampleAssociates;

    //车道边界类型(xml里的)
    vector<BorderType>  borderTypes;
    //车道边界点（xml里的）
    vector<Point*> borderPoints;


     //车道左右边界
     //左边界点
     vector<Point*> leftPoints;
     //车道左边界类型
     vector<BorderType>  leftborderTypes;
    //右边界点
     vector<Point*> rightPoints;
     //车道右边界类型
    vector<BorderType>  rightborderTypes;


	
};
#endif