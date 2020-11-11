#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project1.h"

void push(struct nfa *new_nfa, struct stack *stack){

	//attach the nfa to stack top
	new_nfa->next = stack->top;
	stack->top = new_nfa; 
	stack->size++; 

	return; 
}


struct nfa* pop(struct stack *stack){
	
	//take the nfa off the top of the stack 
	struct nfa *ret_nfa = stack->top; 
	
	stack->top = ret_nfa->next; 
	stack->size--; 
	
	return(ret_nfa); 

}

struct nfa* basic(int s, int a, char sym){

	//create new structs	
	struct trans *new_trans = malloc(sizeof *new_trans); 
	struct nfa *new_nfa = malloc(sizeof *new_nfa); 
	
	//check malloc 
	if (new_nfa == NULL || new_trans == NULL){
		printf("Malloc failed"); 
		return NULL; 	
	}

	//assign the elements of the new nfa
	new_nfa->start = s; 
	new_nfa->accept = a; 
	new_nfa->next = NULL; 
	
	//assign the elements of the new trans	
	new_trans->state1 = s; 
	new_trans->state2 = a; 
	new_trans->symbol = sym; 
	new_trans->next_trans = NULL; 
	
	//tack the new trans to the new nfa
	new_nfa->trans_list = new_trans; 

	return new_nfa; 
}

struct nfa* unionNfa(int count, struct nfa* nfa1, struct nfa* nfa2){

	struct nfa *nfa3 = malloc(sizeof *nfa3);
	struct trans *trans1 = malloc(sizeof *trans1); 
	struct trans *trans2 = malloc(sizeof *trans2);
	struct trans *trans3 = malloc(sizeof *trans3);
	struct trans *trans4 = malloc(sizeof *trans4);
	
	//check malloc
	if (nfa3 == NULL || trans1 == NULL || trans2 == NULL || trans3 == NULL || trans4 == NULL){
		printf("Malloc failed"); 
		return NULL; 	
	}
	
	//assing state numbers for the new nfa
	nfa3->start = count; 
	nfa3->accept = count + 1; 
	
	//create trans state 1 	
	trans1->state1 = nfa3->start; 
	trans1->state2 = nfa1->start; 
	trans1->symbol = 'E'; 
	
	//assign to end of new nfa
	nfa3->trans_list = trans1; 
	
	//create trans state 2 	
	trans2->state1 = nfa3->start; 
	trans2->state2 = nfa2->start; 
	trans2->symbol = 'E'; 

	//assign to end of trans1
	trans1->next_trans = trans2; 
	
	//attach to the front of nfa1
	trans2->next_trans = nfa1->trans_list; 
	
	//set nfa1 to the end trans of nfa1
	while(nfa1->trans_list->next_trans != NULL){
		nfa1->trans_list = nfa1->trans_list->next_trans; 
	}
	
	//set the end of the trans's to the beguinning of nfa2 trans
	nfa1->trans_list->next_trans = nfa2->trans_list; 
	
	//do the same for the end of nfa2 trans
	while(nfa2->trans_list->next_trans != NULL){
		nfa2->trans_list = nfa2->trans_list->next_trans; 
	}	
	
	//create trans state 3	
	trans3->state1 = nfa1->trans_list->state2; 
	trans3->state2 = nfa3->accept; 
	trans3->symbol = 'E'; 	
	
	//connect end of trans to trans3
	nfa2->trans_list->next_trans = trans3; 
	
	//create trans state 4	
	trans4->state1 = nfa2->trans_list->state2; 
	trans4->state2 = nfa3->accept; 
	trans4->symbol = 'E';

	//connect the rest of the trans
	trans3->next_trans = trans4; 	
	trans4->next_trans = NULL; 
	
	//clean old nfas
	free(nfa1); 
	free(nfa2);
	 	
	return nfa3; 

}

struct nfa* concatNfa(struct nfa* nfa1, struct nfa* nfa2){
	
	struct trans *new_trans = malloc(sizeof *new_trans); 
	struct nfa *new_nfa = malloc(sizeof *new_nfa); 
	
	//check if malloc failed
	if (new_nfa == NULL || new_trans == NULL){
		printf("Malloc failed"); 
		return NULL; 	
	}
	
	//assign part of new nfa
	new_nfa->start = nfa1->start; 
	new_nfa->accept = nfa2->accept; 
	new_nfa->trans_list = nfa1->trans_list; 
	
	//get to the end of nfa 1
	while(nfa1->trans_list->next_trans != NULL){
		nfa1->trans_list = nfa1->trans_list->next_trans;
	}
	
	//connect the end of nfa1 to new trans
	nfa1->trans_list->next_trans = new_trans;
	
	//assign state1 for new trans
	new_trans->state1 = nfa1->trans_list->state2;  
	
	//connect new trans to the front of nfa2
	new_trans->next_trans = nfa2->trans_list;
	
	//assign parts to the new trans
	new_trans->state2 = nfa2->start;
	new_trans->symbol = 'E';  
	
	//clean old nfas
	free(nfa1); 
	free(nfa2); 
	
	return new_nfa; 
			
}

struct nfa* kleeneNfa(int count, struct nfa* nfa){

	struct nfa *new_nfa = malloc(sizeof *new_nfa); 
	struct trans *trans1 = malloc(sizeof *trans1); 
	struct trans *trans2 = malloc(sizeof *trans2); 
	
	//check malloc
	if (nfa == NULL || trans1 == NULL || trans2 == NULL){
		printf("Malloc failed"); 
		return NULL; 
	}
	new_nfa->start = new_nfa->accept = count; 
	
	//assign trans1 values
	trans1->state1 = new_nfa->start; 
	trans1->state2 = nfa->start; 
	trans1->symbol = 'E'; 
	
	//connect new nfa to trans1
	new_nfa->trans_list = trans1; 
	//connect trans1 to the start of nfa
	trans1->next_trans = nfa->trans_list; 
	
	//find the last trans of nfa
	while(nfa->trans_list->next_trans != NULL){
		nfa->trans_list = nfa->trans_list->next_trans; 
	}
	
	//assign values to trans2
	trans2->state1 = nfa->trans_list->state2; 
	trans2->state2 = new_nfa->accept; 
	trans2->symbol = 'E'; 
	trans2->next_trans = NULL;
	
	//put trans 2 on the end of nfa's trans list
	nfa->trans_list->next_trans = trans2; 
	 
	free(nfa); 
	
	return new_nfa; 
	
}

void printNfa(struct stack* stack){
	
	struct nfa *test_nfa; 
	struct trans *test_trans; 
		
	//iter through all nfa's in stack 	
	while(stack->size > 0){
	
		test_nfa = pop(stack); 
		printf("Start: %d Accept: %d\n",test_nfa->start, test_nfa->accept);
		
		//for each nfa, iter through all the trans
		while(test_nfa->trans_list != NULL){
			printf("(q%d, %c) -> q%d\n", test_nfa->trans_list->state1, test_nfa->trans_list->symbol, test_nfa->trans_list->state2); 
			test_trans = test_nfa->trans_list; 
			test_nfa->trans_list = test_nfa->trans_list->next_trans; 
			free(test_trans); 	
		}
		
		free(test_nfa);
		
	} 	
	 
}

void freeAll(struct nfa* nfa){

		//frees the trans on the given nfa
		struct trans *test_trans;

		while(nfa->trans_list != NULL){
			test_trans = nfa->trans_list; 
			nfa->trans_list = nfa->trans_list->next_trans; 
			free(test_trans); 	
		}
		free(nfa); 
}


















