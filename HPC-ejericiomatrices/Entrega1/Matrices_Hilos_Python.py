import threading
from random import randrange
import numpy as np
import sys

from time import time
def MatricesProcesos(MatrizA, MatrizB, ColumnasResult,MatrizResultado, contador):  
	RangoFilas,RangoColumnas = MatrizA.shape
	x = 0
	
	for i in range(RangoFilas): #Para las filas
		for j in range (RangoColumnas): #Para las columnas
			if x <= RangoFilas:
				MatrizResultado[i][ColumnasResult+j]=MatrizA[i][x]* MatrizB[x][j]

	
	if len(sys.argv) == 2:
	    texto = sys.argv[1]
	    tamano = int(sys.argv[1])
	"""
	if contador == tamano:
		print ("")
		print ("Matriz Resultante:")
		print (MatrizResultado)
		print ()
	"""

if __name__ == '__main__':

	
	if len(sys.argv) == 2:
	    texto = sys.argv[1]
	    tamano = int(sys.argv[1])
	else:
	    print("Error - Introduce los argumentos correctamente")
	    print('Ejemplo: escribir_lineas.py "Texto" 5')


	TotalFilas = tamano	
	TotalColumnas = TotalFilas
	contador = 1

	#TotalFilas = 15
	#TotalColumnas = 15

	rango_inicio=0


	MatrizUno=np.empty((TotalFilas, TotalColumnas))
	MatrizDos=np.empty((TotalFilas, TotalColumnas))
	MatrizResultado=np.empty((TotalFilas, TotalColumnas))

	for i in range(TotalFilas):
		for j in range(TotalColumnas):
			MatrizUno[i][j]=randrange(10) 
			MatrizDos[i][j]=randrange(10) 
	"""
	print ("")
	print ("Matriz uno:")
	print (MatrizUno)
	
	print ("")
	print ("Matriz dos:")
	print (MatrizDos)
	
	"""
	tiempo_inicial = time()
	
	for z in range(tamano):
		hilo1 = threading.Thread(target=MatricesProcesos,args=(MatrizUno, MatrizDos, rango_inicio, MatrizResultado, contador))
		contador+=1
		hilo1.start()

	hilo1.join()
	tiempo_final = time()
	tiempo_ejecucion = tiempo_final - tiempo_inicial
	print ('El tiempo de ejecucion fue:',tiempo_ejecucion) #En segundos