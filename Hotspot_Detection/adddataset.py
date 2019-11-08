import csv
list = []
with open('train.csv') as csvfile:
    readCSV =csv.reader(csvfile, delimiter=',')
    for row in readCSV:
        list.append([row[5],row[6]])
    print(list)    
