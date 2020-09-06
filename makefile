all:
	gcc prompt.c pathmanager.c input.c processmanager.c cd.c pwd.c ls.c echo.c main.c -o main
	./main

# all:
# 	gcc test.c -o test
# 	./test