from django.http import HttpResponse
from django.shortcuts import render
from .models import Coordinates
from django.http import HttpResponseRedirect
import random 
import subprocess
import math
from queue import Queue 
  

def draw(request):
    string="0"
    if request.method == 'POST':
        ###
        string=request.POST['text']
        count=0
        dataset=[]
        for i in range(0,len(string)):
            if string[i]=='1':
                x=int(i/133)
                y=i%133
                temp=[x,y]
                dataset.append(temp)
            f = open(r"C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\hotspot\myapp\cpp files\demofile.txt", "w")
            f.write(str(len(dataset))+"\n")
            for i in dataset:
                f.write(str(i[0])+" "+str(i[1])+"\n")
            f.close()
        subprocess.call(["g++","C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\hotspot\\myapp\\cpp files\\main.cpp"])
        tmp=subprocess.call("C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\hotspot\\a.exe")
        
        res=[]
        with open(r'C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\hotspot\myapp\cpp files\outputgen.txt', 'r') as reader:
            for line in reader:
                line=line.split()
                temp=[]
                for i in line:
                    temp.append(math.floor(float(i)))  
                res.append(temp)
        dx=[-1,0,1]
        last=[]
        for data in res:
            vis=[ [0 for i in range(0,200)] for i in range(0,200) ]
            c=[data[0],data[1]]
            vis[data[0]][data[1]]=1
            cr=data[2]
            q = Queue(maxsize = 133*63+5)
            q.put(c)
            while q.qsize()>0:
                node=q.get()
                x=node[0]
                y=node[1]
                flag=0
                for i in dx:
                    for j in dx:
                        newx=x+i
                        newy=y+j
                        if newx>=0 and newx<63 and newy>=0 and newy<133 and vis[newx][newy]==0:
                            if (newx-c[0])*(newx-c[0])+(newy-c[1])*(newy-c[1])<=cr*cr:
                                vis[newx][newy]=1
                                flag=1
                                q.put([newx,newy])
                if flag==0:
                    last.append(node)
        final=""
        for i in range(0,133*63):
            final+='0'
        count=0
        for i in last:
            x=i[0]
            y=i[1]
            j=x*133+y
            final=final[:j]+'1'+final[j+1:]
            count+=1
        return render(request,'myapp/result.html',{'stock': string,'final':final})
    return render(request,'myapp/grid.html',{'stock': string})