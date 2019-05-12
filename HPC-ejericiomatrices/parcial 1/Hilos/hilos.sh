#cd /media/edison/5CAC40DEAC40B3F4/Users/Edyson/Desktop/HPC/Parcial1/parcial\ 1
gcc -DUSE_CLOCK -O3 jacobi1d_hilos.c timing.c -o jacobi1dhilos -lpthread
N=100000
NSTEPS=1000
echo "" &> datosexcel.ods
#./jacobi1dhilos $N $NSTEPS u_serial.out > timing_serial.out

for VARIABLE in 10 100 1000 10000 100000 1000000 10000000
do
	#echo $VARIABLE
	./jacobi1dhilos $VARIABLE  NSTEPS &>> datosexcel.ods
done

