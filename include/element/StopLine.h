
#ifndef _STOPLINE_H_
#define _STOPLINE_H_

#include"element/Point.h"
#include<string>
#include<vector>

class StopLine
{
public:
	StopLine(){};
	~StopLine(){};
	//停止线id
	string id;

	//停止线点集
    vector<Point> points;

	
};

#endif