output:
	gcc -g -o output proj3.c helper3.c

clean: 
	rm output

run: output
	./output

detectleaks: 
	valgrind ./output

