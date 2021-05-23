#ifndef _CROSSWALK_H_
#define _CROSSWALK_H_
#include"element/Point.h"
#include<string>
#include<vector>

class Crosswalk
{
public:
	Crosswalk(){};
	~Crosswalk(){};
	//crosswalk id 
	string id;
	//人行横道轮廓
    vector<Point> outline;
	
};

#endif