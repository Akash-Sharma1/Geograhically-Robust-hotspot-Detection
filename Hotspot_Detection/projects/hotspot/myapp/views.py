
from django.http import HttpResponse
from django.shortcuts import render
from .models import Coordinates
    
def show(request):
    context = {
        'data_list' : Coordinates.objects.all()
    }
    return render(request,'myapp/add.html',context)

def draw(request):
    import subprocess 
    import os 
    import csv

    w= open("inputgen.txt","w+")
    ss=str(Coordinates.objects.all().count())+"\n"
    w.write(ss)
    for i in Coordinates.objects.all():
        st=str(i.lat)+"\n"+str(i.longt)+"\n"
        w.write(st)
    w.close()

    data, temp = os.pipe() 
    os.write(temp, bytes("5 10\n", "utf-8")); 
    os.close(temp) 
    os.system(r'g++ C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\main.cpp -o a')
    s = subprocess.check_output(r"C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\a.exe", stdin = data, shell = True)
    
    #main.cpp uses inputgen.txt to get input and saves ouput in
    #outputgen.txt file, now python takes result from that file
    
    
    list =""
    f= open(r"C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\static\myapp\outputgen.txt","r")
    f1=f.readlines()
    for row in f1:
        list+=str(row)
        list+=" "

    list=list.split()
#    print(list) 
    
    value=[]
    c=0
    temp= []
    for data in list:
        if c%3==0:
            temp.append(data)
        elif c%3==1:
            temp.append(data)
        elif c%3==2:
            temp.append(data)
            value.append(temp)
            temp = []
        c += 1
        
    context = {
        'coord_list' : value,
    }
    #value[i][0] gives data
    
    return render(request,'myapp/draw.html',context)

def add(request):
    import csv
    #for adding datasets

    list = []
    Coordinates.objects.all().delete()
    with open(r'C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\static\myapp\test.csv') as csvfile:
        readCSV =csv.reader(csvfile, delimiter=',')
        for row in readCSV:
            list.append([row[5],row[6]])
        c=0
        for data in list:
            if c>0:
                q = Coordinates(lat=data[0],longt=data[1])
                q.save()
            c += 1
    return HttpResponse("Data set Updated")

