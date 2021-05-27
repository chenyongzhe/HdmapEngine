import matplotlib.pyplot as plt
xlist=[]
ylist=[]
zlist=[]
x=None
y=None
z=None

def string_to_float(str):
  return float(str)
with open("test9.txt", "r") as f:
  lines = f.readlines()
  for data in lines:
     if(len(data)<5):
        #print(1)
        plt.plot(xlist,ylist,linewidth =0.5, color='blue', marker='None', linestyle='-', label='A')
        #plt.plot(xlist,ylist,linewidth =0.5, color='blue',markersize=0.1, marker='*', linestyle='-', label='A')
        xlist=[]
        ylist=[]
        zlist=[]
        continue
     items=data.split(' ')
     xlist.append(string_to_float(items[0]))
     ylist.append(string_to_float(items[1]))
     zlist.append(string_to_float(items[2]))
     #print(xlist,ylist,zlist)
     
     

#print(x.shape)
#plt.xlim(-200,200)
#plt.ylim(-200,200)

plt.show()
