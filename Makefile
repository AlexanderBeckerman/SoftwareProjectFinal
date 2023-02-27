build: spkmeans.o wam.c ddg.c gl.o jacobi.o spkmeans.h
	gcc -o spkmeans spkmeans.o wam.c ddg.c gl.o jacobi.o

main.o: spkmeans.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm spkmeans.c

wam.o: wam.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm wam.c

ddg.o: ddg.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm ddg.c

gl.o: gl.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm gl.c

jacobi.o: jacobi.c
	gcc -c -ansi -Wall -Wextra -Werror -pedantic-errors -lm jacobi.c