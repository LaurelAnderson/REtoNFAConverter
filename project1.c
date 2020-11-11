#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project1.h"

int main(int argc, char **argv){
	
	//check the file
	FILE *file = fopen(argv[1], "r"); 
	if (file==NULL) { printf("File failed to open file\n"); }
	
	//allocate room for stack
	struct stack *stack = malloc(sizeof *stack); 
	if (stack == NULL) { 
		printf("Malloc failed");
		return -1; 
	}
	
	//initialize stack
	stack->top = NULL; 
	stack->size = 0;  
	
	//Iterate through the file
	int s1 = 1; 
	int s2 = 2; 
	
	//keep track of where the current nfa is
	int count = 0; 
	char ch; 
	 
	while((ch=fgetc(file))!=EOF){	 	 
		
		if(ch == '&'){
		
			//handle the error 
			if (count < 2){
			
				printf("not enough arguments for (&)\n");
				
				//iterate to the end of the line
				while(ch=fgetc(file) != 10)  {}
								
				//pop how many nfas this line pushed
				while(count>0){
					free(pop(stack));
					count--; 
				} 
				  
			}else{
			 
				//push a new nfa that accepts the concat of nfa1 and nfa2
				push(concatNfa(pop(stack), pop(stack)), stack);  		
		 		
		 	}
		 
		}else if(ch == '|'){
		
			//handle the error 
			if (count < 2){
			
				printf("not enough arguments for (|)\n");
				
				//iterate to the end of the line
				while(ch=fgetc(file) != 10)  {}	
				
				//pop how many nfas this line pushed
				while(count>0){
					free(pop(stack));
					count--; 
				}				
	
			}else{
			
				//push a new nfa that accepts the union of nfa1 and nfa2
				push(unionNfa(s1, pop(stack), pop(stack)), stack); 
 				s1+=2; 
 				s2+=2;
 				count--;
 			}  			
			 
		}else if(ch == '*'){
			
			if(count == 0){
			
				printf("not enough arguments for (*)\n"); 
				
				//iterate to the end of the line
				while(ch=fgetc(file) != 10)  {}	 
 				
			}else{
			 
			//push a new nfa that accepts the star of the nfa
				push(kleeneNfa(s1, pop(stack)), stack);  
				s1+=1; 
				s2+=1; 
			}
				
		}else if((ch >= 'a' && ch <= 'e') || ch == 'E'){
		
			//push a basic new nfa
			push(basic(s1,s2,ch), stack);  
 			s1+=2; 
 			s2+=2; 
 			count++; 
 				
 			
		}else if(ch == 10){
				
			//we are at a new nfa
			count = 0; 
			
		}else if(ch != 32){//if you have a char that is not valid; 

			//print invalid input
			printf("invalid input (%c) \n", ch);
				
			//iterate to the end of the line
			while(ch=fgetc(file) != 10)  {}
				
			//pop how many nfas this line pushed
			while(count>0){
				free(pop(stack));
				count--; 
			} 
		}
		 
	} 
	
	//print and free all the structs 
	
	printNfa(stack);
 	
 	free(stack); 
 
	fclose(file); 
	
	return 0; 
	
}









