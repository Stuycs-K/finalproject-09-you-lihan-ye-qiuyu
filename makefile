default:
	@./encrypt
	
md5.o: md5.c
	@gcc -c md5.c
	
compile_md5: md5.o
	@gcc -o encrypt md5 -Wall -lm

encrypt: compile_md5
	@./encrypt

clean:
	rm -f *.o
	rm -f encrypt                