build: spkmeans.h spkmeans.o spk.o wam.o ddg.o gl.o jacobi.o
	gcc -o spkmeans spkmeans.o wam.o ddg.o gl.o jacobi.o 

main.o: spkmeans.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm spkmeans.c

spk.o: spk.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm spk.c

wam.o: wam.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm wam.c

ddg.o: ddg.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm ddg.c

gl.o: gl.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm gl.c

jacobi.o: jacobi.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm jacobi.c
