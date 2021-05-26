# -*-coding: utf-8- -*-
'''

@author: chenyongzhe
'''

import numpy as np
import matplotlib.pyplot as plt
import mpl_toolkits.mplot3d
xlist=[]
ylist=[]
zlist=[]
def string_to_float(str):
  return float(str)
with open("mytest.txt", "r") as f:
  lines = f.readlines()
  for data in lines:
     items=data.split(' ')
     xlist.append(string_to_float(items[0]))
     ylist.append(string_to_float(items[1]))
     zlist.append(string_to_float(items[2]))
     #print(xlist,ylist,zlist)
x = np.array(xlist)
y = np.array(ylist)
z = np.array(zlist)
print(x.shape)

ax = plt.subplot(projection = '3d')  # 创建一个三维的绘图工程
ax.set_title('3d_image_show')  # 设置本图名称
#ax.set_aspect("equal") 

ax.scatter(x, y, z, c = 'r')   # 绘制数据点 c: 'r'红色，'y'黄色，等颜色

ax.set_xlabel('X')  # 设置x坐标轴
ax.set_ylabel('Y')  # 设置y坐标轴
ax.set_zlabel('Z')  # 设置z坐标轴
#ax.set_xlim3d(-200, 200)
#ax.set_ylim3d(-200, 200)
ax.set_zlim3d(-30, 300)
plt.axis("equal")
plt.show()
