
#ifndef _JUNCTION_H_
#define _JUNCTION_H_
#include<vector>
#include"element/Connection.h"
using namespace std;
class Junction
{
public:
	Junction();
	~Junction();
	int id;
	vector<Connection> connections;

	
};

#endif