
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
    //参数为地图原点维度 经度 高程
    HdmapEngine engine(43.856238, 125.3265161, 235.120);
    if(!engine.paserApolloxml("../mapdata/OriginTest.xml")) cout<<"解析失败"<<endl;
    engine.printBaseInfo();


    // //map 查到测试demo 
    // auto iter_junction=engine.junctionMap.find(462);
    // if(iter_junction!=engine.junctionMap.end()){
    //   cout <<"result junction id: "<< iter_junction->second.id<<endl;
    // }

 
    // //通过坐标搜索车道
    //  Lane * laneresult=engine.searchLaneByxy(-38.2,433.3);
    //  if(laneresult !=NULL){
    //     cout<<"x -38.2: y: 433.3 所在的车道uid为： "<<laneresult->uid<<endl;
    //  }

    // //测试getRoadBetweenJunctions
    // auto iter=engine.junctionMap.find(462);
    // if(iter==engine.junctionMap.end()){
    //   cout<<"can not find"<<endl;
    // }

    // Road* roadresult=engine.getRoadBetweenJunctions(engine.junctionMap[462],engine.junctionMap[309]);
    // if(roadresult!=NULL){
    // 	cout<<"查找到路口462 路口309的连接道路id为： "<<roadresult->road_id<<endl;
    // }
    

    
    //.....
    return 0;
}
