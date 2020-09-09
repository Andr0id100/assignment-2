all:
	gcc prompt.c pathmanager.c input.c processmanager.c cd.c pwd.c ls.c echo.c pinfo.c main.c -o main
	./main
	# ls
	# ls .
	# ls ..
	# ls ../assignment-1
	# ls /home/snehal/Documents

# all:
# 	gcc test.c -o test
# 	./test