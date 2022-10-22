import matplotlib.pyplot as plt
import sys

a = open(sys.argv[1], "r")
l = a.readlines()
a.close()
x=[]
y=[]

for i in range(len(l)):
	x.append(i)
	y.append(int(l[i]))
plt.plot(x,y)
plt.show()

