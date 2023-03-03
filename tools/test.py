import matplotlib.pyplot as plt

a = open("C1A.csv", "r")
lines = a.readlines()
if len(lines) == 1:
	lines = lines[0].split(" ")
a.close()

for i in range(len(lines)):
	plt.scatter(i/44100, float(lines[i]))
plt.show()

