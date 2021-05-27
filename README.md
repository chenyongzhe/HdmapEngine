# HdmapEngine
##  apollo opendrive xml格式高精地图解析引擎<br>
作者：chenyongzhe<br>
联系邮箱：1276316543@qq.com<br>
## 依赖环境<br>
项目使用C++开发，目前支持 linux 下ubuntu 16.04、18.04 <br>
cmake 版本高于2.8<br>
使用xml解析库为tinyxml2<br>
依赖eigen 库做矩阵运算<br>
## 引擎功能 <br>
1. 解析 apollo opendrive xml 格式高精地图文件。(接口在HdMapEngine.h 头文件中)<br>
2. 通过给定坐标搜索得到车道。(HdMapEngine.h 中 searchLaneByxy函数返回车道指针)<br>
3. 显示高精路网地图<br>
4. 搜索指定范围内车道中心点<br>
5. 支持wgs84 经纬度坐标系到东北天（x,y,z）坐标系转换<br>

## 地图元素<br>
地图元素 包括：<br>
1. Road  道路 --->对应 xml 里的road 标签<br>
2. LaneSection --->对应 xml 里的 LaneSection标签<br>
3. Lane 车道  --->对应 xml 里的 Lane标签<br>
4. Junction 路口  --->对应 xml 里的 junction标签<br>
5. connection 路口内车道连接关系 --> 对应 xml 里的 connection标签<br>
6. StopLine 提车线 <br>
7. TrfficLight 信号灯 <br>
8. Crosswalk 人行横道<br>
每个元素具体属性参考 include/element/ 下的头文件内的注释<br>

## 编译运行<br>
cd build<br>
rm -rf ./*<br>
cmake ..<br>
make <br>
./HdmapEngine<br>

## 高精地图显示 <br>
需要 matplotlib 库<br>
安装matplotlib库<br>
pip install matplotlib<br>
1. 生成车道点：<br>
./OutputPoint > LanePoints.txt<br>
cp LanePoints.txt ../showMap/<br>

2. 使用python 显示车道点<br>
cd showMap<br>
python show.py<br>
效果<br>
<img src="https://raw.githubusercontent.com/chenyongzhe/HdmapEngine/master/showMap/map2.png" width=500 height=300/><br>

