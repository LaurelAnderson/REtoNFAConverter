project1: project1.c
	gcc -g -o output project1.c project1user.c
run: 
	./output inputFile.txt
	
clean: 
	rm output
	
test: 
	valgrind --leak-check=full ./output inputFile.txt 
