all:
	gcc pathmanager.c processmanager.c utils.c  -c
	gcc ls.c -o ls pathmanager.o utils.o
	gcc echo.c -o echo

	gcc prompt.c pwd.c input.c cd.c pinfo.c history.c newborn.c processmanager.c main.c -o shell pathmanager.o utils.o
