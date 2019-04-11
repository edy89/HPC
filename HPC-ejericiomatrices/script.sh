#!/bin/bash
# A sample Bash script, by Ryan
cd /home/kalugy/Escritorio/HPC/HPC-ejericiomatrices
gcc multiplicacion_matrices.c -o mulma

#(time -o datos.txt ./mulma 2) 
 
echo "" &> datosexcel.ods	

#for VARIABLE in 10 100 1000 10000 100000 1000000 10000000
#do
	#echo $VARIABLE
	#(time ./mulma $VARIABLE) &>> datosexcel.ods
#done
(time ./mulma 10) &>> datosexcel.ods
(time ./mulma 100) &>> datosexcel.ods
(time ./mulma 1000) &>> datosexcel.ods
#(time ./mulma 10000) &>> datosexcel.ods
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