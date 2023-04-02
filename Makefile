build: spkmeans.h spkmeans.o spk.o wam.o ddg.o gl.o jacobi.o kmeans.o
	gcc -o spkmeans spkmeans.o wam.o ddg.o gl.o jacobi.o spk.o kmeans.o -lm

main.o: spkmeans.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors spkmeans.c

spk.o: spk.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors spk.c

wam.o: wam.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors wam.c

ddg.o: ddg.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors ddg.c

gl.o: gl.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors gl.c

jacobi.o: jacobi.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors jacobi.c

kmeans.o: kmeans.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c