
#ifndef _TRAFFICLIGHT_H_
#define _TRAFFICLIGHT_H_

#include"element/Point.h"
#include<string>
#include<vector>
//子信号
struct SubSignal
{
	int id;
	//子信号类型 circle ...
	string type;
	//center point 
	//经度
	double lon;
	//纬度
	double lat;
    //东北天 x y z
	double x;
	double y;
	double z;
};

//信号灯
class TrafficLight
{
public:
	TrafficLight(){};
	~TrafficLight(){};
	//信号灯id
	int  id;
	// 信号布局： 垂直（mix3Vertical）、水平 。。。。
	string layoutType;
	//信号灯轮廓
	vector<Point> outline;
	//信号灯对应的停止线
	vector<StopLine> stopLines;
	//信号灯子信号
    vector<SubSignal> subSignals;

	
};

#endif