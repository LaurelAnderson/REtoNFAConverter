//project1.h

#ifndef PROJECT1
#define PROJECT1

//structs

struct stack {
	struct nfa *top;
	int size; 
}; 

struct nfa {
	int start; 
	int accept; 
	struct trans *trans_list; 
	struct nfa *next; 
};

struct trans {
	int state1; 
	int state2; 
	int symbol; 
	struct trans *next_trans; 
	
};

//function declarations

//pushes a nfa onto the stack
void push(struct nfa*, struct stack*);

//pops a nfa off of the stack 
struct nfa* pop(struct stack*);

//creates a basic nfa with a input of a, b c, d, or e
struct nfa* basic(int, int, char); 

//takes 2 nfas and does the union operation on them
struct nfa* unionNfa(int, struct nfa*, struct nfa*); 

//takes 2 nfas and concats them. 
struct nfa* concatNfa(struct nfa*, struct nfa*); 

//takes an nfa and does the kleene star of it. 
struct nfa* kleeneNfa(int, struct nfa*); 

//prints the trans steps for the stack given. 
void printNfa(struct stack*); 

//frees single nfas
void freeAll(struct nfa*); 

#endif
