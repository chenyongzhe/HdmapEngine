# HdmapEngine
##  apollo opendrive xml格式高精地图解析引擎<br>
作者：chenyongzhe<br>
联系邮箱：1276316543@qq.com<br>
## 依赖环境<br>
项目使用C++开发，目前支持 linux 下ubuntu 16.04、18.04 <br>
cmake 版本高于2.8<br>
使用xml解析库为tinyxml2<br>
依赖eigen 库做矩阵运算<br>
## 编译运行<br>
cd build<br>
rm -rf ./*<br>
cmake ..<br>
make <br>
./HdmapEngine<br>
## 高精地图显示<br>
使用python 将车道边界点连接起来<br>
需要 matplotlib 库<br>
安装matplotlib库<br>
pip install matplotlib<br>

cd showMap<br>
python show.py<br>

<img src="https://raw.githubusercontent.com/chenyongzhe/HdmapEngine/master/showMap/map2.png" width=500 height=300/><br>
