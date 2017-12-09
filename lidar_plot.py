import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
import random
import math
import time

style.use('dark_background')

fig = plt.figure()
ax1 = fig.add_subplot(1,1,1)

def get_data():
    dist = []
    for i in range(240):
        dist.append(random.uniform(0,1)*2)
    angle = []
    for i in range(240):
        angle.append(i)
    data = []
    for i in range (len(dist)):
        temp = []
        temp.append(dist[i]*math.cos(angle[i]*math.pi/180))
        temp.append(dist[i]*math.sin(angle[i]*math.pi/180))
        data.append(temp)
    return data

def animate(i):
    graph_data = get_data()
    xs = []
    ys = []
    for a in range(len(graph_data)):
        for b in range(a):
            xs.append(graph_data[b][0])
            ys.append(graph_data[b][1])
    ax1.clear()
    ax1.plot(xs,ys,'ro')

ani = animation.FuncAnimation(fig, animate, interval= 4)
plt.show()