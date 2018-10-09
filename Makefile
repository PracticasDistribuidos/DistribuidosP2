distparalel: distparalel.c 
	mpicc -o distparalel distparalel.c -lm
	mpirun -n 5 ./distparalel

clean: 
	rm distparalel
