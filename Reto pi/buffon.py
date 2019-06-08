from random import random
from math import cos,pi

#while(1):
 #  print(random())

def corta(l=1,d=1):
    #válido únicamente si l <= d
    x = d*random()
    #Un poco anticlimático tener que usar pi
    y = l*cos(pi/2*random())
    if y>x:
        #print('x = ',x,' y = ',y)
        print(random())
        return True
    else:
        return False

intentos = 100000
N = 0
C = 0
L=0.25 
D=0.75
  

print ('Calculando el número pi\n') 
print ('La Aguja de Buffon\n')
print ('L = ',L,', D = ',D,'\n')


while N < intentos:
    #if N % 1000 == 0:
        #print('.')
    N+=1
    #print(corta(L,D))
    if corta(L,D):
        C+=1

print ('pi calculado = ',(2.0*L*N)/(D*C))
#print ('C = ',C,', N = ',N,'\n')
#print ('pi calculado = ',(2.0*L*N)/(D*C),' (pi = 3.14159...)\n') '''