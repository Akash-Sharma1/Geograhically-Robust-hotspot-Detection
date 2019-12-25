from django.http import HttpResponse
from django.shortcuts import render
from .models import Coordinates
from django.http import HttpResponseRedirect
import random 
import os
import subprocess
import math

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
            f = open(r"C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\cpp files\demofile.txt", "w")
            f.write(str(len(dataset))+"\n")
            for i in dataset:
                f.write(str(i[0])+" "+str(i[1])+"\n")
            f.close()
            ###
        subprocess.call(["g++","C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\Hotspot_Detection\\projects\\hotspot\\myapp\\cpp files\\main.cpp"])
        tmp=subprocess.call("C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\Hotspot_Detection\\projects\\hotspot\\a.exe")
        res=[]
        with open(r'C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\cpp files\outputgen.txt', 'r') as reader:
            for line in reader:
                line=line.split()
                temp=[]
                for i in line:
                    temp.append(math.floor(float(i)))  
                res.append(temp)
        for data in res:
            cx=data[0]
            cy=data[1]
            cr=data[2]
            for i in range(0,len(string)):
                x=int(i/133)
                y=i%133
                if (x-cx)*(x-cx)+(y-cy)*(y-cy)<=cr*cr:
                    string=string[:i]+'1'+string[i+1:]
        return render(request,'myapp/grid.html',{'stock': string})
    return render(request,'myapp/grid.html',{'stock': string})