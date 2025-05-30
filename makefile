default:
	@./encrypt

algorithm_functions.o: algorithm_functions.c
	@gcc -c algorithm_functions.c
print_functions.o: print_functions.c
	@gcc -c print_functions.c

md5.o: md5.c
	@gcc -c md5.c
	
compile_md5: md5.o algorithm_functions.o algorithm_functions.h print_functions.o print_functions.h
	@gcc -o encrypt md5.o algorithm_functions.o print_functions.o -Wall

hash: compile_md5
	@./encrypt $(ARGS)

hashcat.o: hashcat.c
	@gcc -c hashcat.c 

compile_hashcat: hashcat.o algorithm_functions.o algorithm_functions.h print_functions.o print_functions.h
	@gcc -o hashcat hashcat.o algorithm_functions.o print_functions.o -Wall

hashcat: compile_hashcat
	@./hashcat $(ARGS)

clean:
	rm -f *.o
	rm -f encrypt       
	rm -f hashcat         