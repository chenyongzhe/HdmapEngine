#ifndef _POINT_H_
#define _POINT_H_

#include<string>
using namespace std;
class Point
{
public:
	//Point();
	~Point();
	//经度
	double lon;

	//维度
	double lat;
	//东北天   x y z
	//x坐标
	double x;
	//y坐标
	double y;
	//高度 m
	double z;

	//如果车道上的点
	string lane_id;

	static int idx;

    Point(double x0, double y0) {
            x = x0;
            y = y0;
        }
    bool operator < (const Point &u) const {
    	    if(idx==0)return x<u.x;
    	    if(idx==1) return y<u.y;
        }
        //TOOD =hao
     Point() {
            x=0;
            y=0;
        }
	
};

#endif