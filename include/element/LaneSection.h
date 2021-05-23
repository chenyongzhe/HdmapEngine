#ifndef _LANESECTION_H_
#define _LANESECTION_H_
#include"element/Lane.h"

#include<vector>
using namespace std;
class LaneSection
{
public:
	LaneSection();
	~LaneSection();
	//长度
	double length;
	//车道列表
    vector<Lane> lanes;
    //laneSection id
    int laneSection_id;
	
};

#endif