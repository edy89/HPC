#!/bin/bash


#gcc -o buffon_out serial_buffon.c -fPIC -lquadmath -lm
#gcc -o datboard_out serial_datboard.c -fPIC -lquadmath -lm
gcc -o buffon_parallel_out buffon_parallel.c -fPIC -lquadmath -lm -fopenmp
#gcc -o datboard_parallel_out datboard_parallel.c -fPIC -lquadmath -lm -fopenmp

echo "" &> tiempos.ods	

for VARIABLE in 1000 10000 100000 1000000 10000000 100000000 1000000000
do
	#echo $VARIABLE
	./buffon_parallel_out $VARIABLE &>> tiempos.ods
done
