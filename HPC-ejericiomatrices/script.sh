#!/bin/bash
# A sample Bash script, by Ryan
cd /home/utp/Escritorio/HPC/HPC-ejericiomatrices
gcc multiplicacion_matrices.c -o mulma
gcc matrices_parallel.c -o mulmapa -lpthread
#(time -o datos.txt ./mulma 2) 
 
echo "" &> datosexcel.ods	

for VARIABLE in 1000 200
do
	#echo $VARIABLE
	./mulma $VARIABLE &>> datosexcel.ods
done



for VARIABLE in 10 100 1000	
do
	#echo $VARIABLE
	./mulmapa $VARIABLE &>> datosexcel.ods
done

#(time ./mulma 1) &>> datosexcel.ods
#(time ./mulma 10) &>> datosexcel.ods
#(time ./mulma 200) &>> datosexcel.ods
#(time ./mulma 2000) &>> datosexcel.ods
#./mulma 810
#(time ./mulma 100000) &>> datosexcel.ods
#(time ./mulma 1000000) &>> datosexcel.ods
#(time ./mulma 10000000) &>> datosexcel.ods
#start_time=$(date +%s)
#Ejecución
#(time ./mulma 1000) &>> datosexcel.ods
#finish_time=$(date +%s)
#let a=$((finish_time - start_time)) 
#echo "$a"
#echo "Time duration: $((finish_time - start_time)) secs."