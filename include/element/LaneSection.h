#ifndef _LANESECTION_H_
#define _LANESECTION_H_
#include"element/Lane.h"
#include"Point.h"

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
    vector<Lane *> lanes;
    //laneSection id
    int laneSection_id;

    //中心车道线
    vector<Point*> centerborder;
    //中心车道线border
    vector<BorderType>  centerborderTypes;

	
};

#endif