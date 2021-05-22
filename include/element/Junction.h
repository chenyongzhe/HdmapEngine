#ifndef _JUNCTION_H_
#define _JUNCTION_H_

#include"element/Point.h"
#include<string>
#include<vector>
using namespace std;


class Junction
{
public:
	Junction();
	~Junction();
	//路口id
	int id;
	//进入入口的道路id
	int in_road_id;
	//出路口的道路id
	int out_road_id;
	//进入路口的通行方式
	string in_road_turntype;
	//离开口的通行方式
	string out_road_turntype;
	//进入路口的车道id
	string in_lane_id;
	//离开路口的车道id
	string out_lane_id;
	//进入道路的通行方式
	string in_lane_turntype;
	//离开道路的通行方式
	string outLaneTurntype;
	//虚拟车道id
	string virtualLaneId;
	//虚拟车道参考线（离散点）
	 vector<Point> referLinePoints;

	
};
#endif