
from subprocess import Popen, PIPE
import os

os.system(r'g++ C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\main.cpp -o a')
p = Popen([r'C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\a.exe'], shell=True, stdout=PIPE, stdin=PIPE)

value = "1 2.23 3.43 "
value = bytes(value, 'UTF-8')  # Needed in Python 3.
p.stdin.write(value)
p.stdin.flush()
result = p.stdout.readline().decode()
print(result)