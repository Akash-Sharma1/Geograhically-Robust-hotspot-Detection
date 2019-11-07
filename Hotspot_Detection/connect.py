import subprocess 
import os 

data, temp = os.pipe() 
os.write(temp, bytes("5 10\n", "utf-8")); 
os.close(temp) 
os.system('g++ main.cpp -o a')
s = subprocess.check_output("a.exe", stdin = data, shell = True)
s=s.decode("utf-8")
s=s.split()
print(type(s))
print(s) 

## stastical meathod for factor analysis
#factor reduciton
#factor selection
