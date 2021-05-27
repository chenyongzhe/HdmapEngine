#ifndef _KDTREE_H_
#define _KDTREE_H_


#define lson (rt << 1)//左节点
#define rson (rt << 1 | 1)//右节点

#include <vector>
#include <algorithm>
#include <cmath>
#include<iostream>
#include"element/Point.h"
using namespace std;

    const long N = 5000005;
    const int k = 2; //2D-tree

    class KDTree {
    public:
        KDTree();
        ~KDTree();
        void clean();
        int read_in(vector<Point> inputPoints);
        void build(int l, int r, int rt, int dept);
        int find_nearest_point(double x, double y, Point& result, double& dist);
        double distance(const Point& x, const Point& y);
    public:
        void query(const Point& p, Point& res, double& dist, int rt, int dept);
        std::vector<Point> _data;//用vector模拟数组
        std::vector<int> _flag;//判断是否存在
        int _idx;
        std::vector<Point> _find_nth;
    };
#endif