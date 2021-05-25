
#ifndef _JUNCTION_H_
#define _JUNCTION_H_
#include<vector>
#include"element/Connection.h"
#include"element/Point.h"
using namespace std;
class Junction
{
public:
	Junction();
	~Junction();
	int id;
	//路口连接关系
	vector<Connection> connections;
	//路口边界轮廓
	vector<Point> outline;
	//路口中心坐标、东北天坐标系x,y,z
	Point center;

	
};

#endif