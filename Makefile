build: spkmeans.o spk.o wam.c ddg.c gl.o jacobi.o spkmeans.h
	gcc -o spkmeans spkmeans.o spk.o wam.c ddg.c gl.o jacobi.o

main.o: spkmeans.c
	gcc -c spkmeans.c

spk.o: spk.c
	gcc -c spk.c

wam.o: wam.c
	gcc -c wam.c

ddg.o: ddg.c
	gcc -c ddg.c

gl.o: gl.c
	gcc -c gl.c

jacobi.o: jacobi.c
	gcc -c jacobi.c