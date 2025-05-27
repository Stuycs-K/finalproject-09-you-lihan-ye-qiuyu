default:
	@./encrypt
	
md5.o: md5.c
	@gcc -c md5.c
algorithm_functions.o: algorithm_functions.c
	@gcc -c algorithm_functions.c
print_functions.o: print_functions.c
	@gcc -c print_functions.c

compile_md5: md5.o algorithm_functions.o algorithm_functions.h print_functions.o print_functions.h
	@gcc -o encrypt md5.o algorithm_functions.o print_functions.o -Wall

run: compile_md5
	@./encrypt $(ARGS)
	@rm -f *.o
	@rm -f encrypt 

clean:
	rm -f *.o
	rm -f encrypt                