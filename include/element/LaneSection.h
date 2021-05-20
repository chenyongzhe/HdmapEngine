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
	double length;
    vector<Lane> Lanes;
    int LaneSection_id;
	
};

#endif