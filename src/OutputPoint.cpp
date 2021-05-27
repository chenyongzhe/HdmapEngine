
#include"HdmapEngine.h"
#include"tools/TransformUtil.h"
#include"tools/KDTree.h"
//@author chenyonzghe
//Email 1276316543@qq.com

int main()
{
    HdmapEngine engine(43.856238, 125.3265161, 235.120);
    if(!engine.paserApolloxml("../mapdata/OriginTest.xml")) cout<<"解析失败"<<endl;
    engine.printBaseInfo();

    return 0;
}
