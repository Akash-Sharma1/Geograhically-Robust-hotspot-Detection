
from subprocess import Popen, PIPE
import os

os.system('g++ main.cpp -o a')

p = Popen(['a.exe'], shell=True, stdout=PIPE, stdin=PIPE)
value = "1 2 3 4 5 6 7 8 9 10 "
value = bytes(value, 'UTF-8')  # Needed in Python 3.
p.stdin.write(value)
p.stdin.flush()
result = p.stdout.readline().decode()
print(result)