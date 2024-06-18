import random
f=open("test.txt",'r')
words=[]
f1=open("data.txt","w")
for i in f:
    f1.write('2 ')
    f1.write(i)
f1.write('0')
