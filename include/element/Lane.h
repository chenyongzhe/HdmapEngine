
#ifndef _LANE_H_
#define _LANE_H_

#include<string>
#include <iostream>
#include "tinyxml2.h"
#include<vector>
using namespace std;
using namespace tinyxml2;

using namespace std;
class Lane
{
public:
	Lane();
	~Lane();
	//车道uid
	string lane_uid;
	//车道前驱id
	string predecessor_id;
	//车道后继id
	string successor_id;
	//左邻近近同向车道
	string leftNeighbor_sameDirect_id;
	//左邻近近不同向车道
	string leftNeighbor_reverseDirect_id;
	//右邻近近同向车道
	string rightNeighbor_sameDirect_id;
	//右近近不同向车道
	string rightNeighbor_reverseDirect_id;
	//所在道路id
	int road_id;
	//车道长度
	double lane_length=-1;
	//车道转向类型
	string turn_type;
	//车道限速
	double speed_limit;



	
};
#endif