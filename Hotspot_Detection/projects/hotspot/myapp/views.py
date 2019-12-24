
from django.http import HttpResponse
from django.shortcuts import render
from .models import Coordinates
    
def show(request):
    w= open(r"C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\static\myapp\foo.txt","w+")
    st='['
    w.write(st)
    c=0
    for i in Coordinates.objects.all():
        if c>0:
            st=', \n {'
        else:
            st = '\n { \n'
        st += "\"lat\" : "+str(i.lat)+",\n \"lng\" : "+str(i.longt)+"\n"
        st += '}'
        w.write(st)
        c += 1
    st=']'
    w.write(st)
    w.close()
    return render(request,'myapp/plotmarkers.html',{})

def draw(request):
    import subprocess 
    import os 
    import csv

    w= open(r"C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\myapp\static\myapp\inputgen.txt","w+")
    ss=str(Coordinates.objects.all().count())+"\n"
    for i in Coordinates.objects.all():
        st=str(i.lat)+"\n"+str(i.longt)+"\n"
        w.write(st)
    w.close()
    data, temp = os.pipe() 
    os.write(temp, bytes("5 10\n", "utf-8")); 
    os.close(temp) 
    
    os.system(r'g++ C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\cpp files\pointsjsonconv.cpp -o pcon')
    os.system("C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\Hotspot_Detection\\projects\\hotspot\\cpp files\\pcon.exe")
      
    os.system(r'g++ C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\cpp files\main.cpp -o a')
    os.system("C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\Hotspot_Detection\\projects\\hotspot\\cpp files\\a.exe")
    
    os.system(r'g++ C:\Users\aakas\Documents\Geograhically-Robust-hotspot-Detection\Hotspot_Detection\projects\hotspot\cpp files\pointsjsonconv.cpp -o pout')
    os.system("C:\\Users\\aakas\\Documents\\Geograhically-Robust-hotspot-Detection\\Hotspot_Detection\\projects\\hotspot\\cpp files\\pout.exe")

    return render(reque st,'myapp/plotcircles.html',{})

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
            if c>500:
                break
            if c>0:
                q = Coordinates(lat=data[0],longt=data[1])
                q.save()
            c += 1
    return HttpResponse("Data set Updated")