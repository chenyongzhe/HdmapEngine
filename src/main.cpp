
#include"HdmapEngine.h"
#include"tools/TransformUtil.h"
//@author chenyonzghe
//Email 1276316543@qq.com

int main()
{
    //const char* file_name = "../mapdata/FourWaySignal.xml";
    //test tools uws84 到东北天坐标转换
    TransformUtil trans(43.8537909, 125.3279195, 235.120);
    Eigen::Vector3d xyz(0,0,0);
    trans.gps2xyz(125.3279168, 43.8537930, 235.120,xyz);
    std::cout<<xyz;
    
    HdmapEngine engine;
    if(!engine.paserApolloxml("../mapdata/OriginTest.xml")) cout<<"解析失败"<<endl;
    engine.printBaseInfo();
    //.....
    return 0;
}
