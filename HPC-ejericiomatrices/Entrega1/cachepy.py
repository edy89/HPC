from random import randrange
import numpy as np
import sys
from time import time

def MatricesProcesos(MatrizA, MatrizB, RangoFilas,MatrizResultado, contador):  
	#RangoFilas = MatrizA.shape
	x = 0
	tem=0
	filaporfila=TotalFilas*TotalFilas
	print (MatrizA[0])
	

	for i in range(RangoFilas): #Para las filas
		for x in range (RangoFilas):
			#MatrizResultado[i]=
			tem+=MatrizA[x] * MatrizB[x*RangoFilas]
			print(tem)
			#print(MatrizB[x*RangoFilas])

			
				
		MatrizResultado[i]=tem
		tem=0

	"""
	if len(sys.argv) == 2:
	    texto = sys.argv[1]
	    tamano = int(sys.argv[1])
	"""
	
	if contador == tamano:
						print ("")
						print ("Matriz Resultante:")
						print (MatrizResultado)
						print ()
				


if __name__ == '__main__':

	
	if len(sys.argv) == 2:
	    texto = sys.argv[1]
	    tamano = int(sys.argv[1])
	else:
	    print("Error - Introduce los argumentos correctamente")
	    print('Ejemplo: escribir_lineas.py "Texto" 5')


	TotalFilas = tamano	
	contador = 1
	 

	#TotalFilas = 15
	#TotalColumnas = 15

	rango_inicio=0


	#MatrizUno=np.empty(TotalFilas)
	#MatrizDos=np.empty(TotalFilas)
	#MatrizResultado=np.empty(TotalFilas)

	MatrizUno=[]
	MatrizDos=[]
	MatrizResultado=[]

	filaporfila=TotalFilas*TotalFilas
	for i in range(filaporfila):
		MatrizUno.append(randrange(10) )
		MatrizDos.append(randrange(10)) 
			
	print ("")
	print ("Matriz uno:")
	print (MatrizUno)
	
	print ("")
	print ("Matriz dos:")
	print (MatrizDos)
	
	tiempo_inicial = time()
	for z in range(tamano):
		contador=1
		funcion = MatricesProcesos(MatrizUno, MatrizDos, TotalFilas, MatrizResultado, contador)
		

	tiempo_final = time()
	tiempo_ejecucion = tiempo_final - tiempo_inicial
	print ('El tiempo de ejecucion fue:',tiempo_ejecucion) #En segundos