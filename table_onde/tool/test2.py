from scipy.io import wavfile

samplerate, data = wavfile.read("C1A.wav")
a = open("C1A.csv", "w")
print(samplerate)

for i in data:
	a.writelines(str(i) + ' ')
a.close()

