
#include"HdmapEngine.h"
#include"tools/TransformUtil.h"
#include"tools/KDTree.h"
//@author chenyonzghe
//Email 1276316543@qq.com

int main()
{
    //const char* file_name = "../mapdata/FourWaySignal.xml";
    //test tools uws84 到东北天坐标转换
    TransformUtil trans(43.8537909, 125.3279195, 235.120);
    Eigen::Vector3d xyz(0,0,0);
    trans.gps2xyz(125.3279168, 43.8537930, 235.120,xyz);
    //std::cout<<xyz;
    
    HdmapEngine engine(43.8537909, 125.3279195, 235.120);
    if(!engine.paserApolloxml("../mapdata/OriginTest.xml")) cout<<"解析失败"<<endl;
    engine.printBaseInfo();
    //float xlist[6]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
    //float ylist[6]={1.0f,2.0f,3.0f,4.0f,5.0f,6.0f};
    // vector<Point> points;
    // Point p1(1,1);
    // Point p2(2,2);
    // Point p3(3,3);
    // Point p4(4,4);
    // points.push_back(p1);
    // points.push_back(p2);
    // points.push_back(p3);
    // points.push_back(p4);

    
    // tree->read_in(points);
    double dis=1000000000;
    Point result;
    engine.tree->find_nearest_point(-38.4624,433.8,result,dis);
    //cout<<"data_ szie "<<tree->_data.size()<<endl;
    cout<<"res "<<result.x<<" "<<result.y<<endl;
    cout<<"dis  "<<dis<<endl;
    cout<<"搜索车道结果为"<<result.lane_id<<endl;
    

    
    //.....
    return 0;
}
