//proj3.c created by Laurel Anderson
#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include "proj3.h"

int main(){
	
	char c, h; 
	int n; 

	//Create a new node for the root at the beguinning of the program 
	struct node *root = NULL;  

	printf("This is a BST maker: enter a command followed by either a number or a char. \n"); 

	// Eternal loop that checks the inputs. 
	while(1){
		
		//Take in one char	
		scanf("%c", &c); 
		
		//begin switch statment. Will send to function depending on what c is. 
		if(isspace(c)==0){
			
			switch(c){
				//Insert
				case 'i':
					scanf("%d", &n); 
					printf("inserted %d! \n", n);
					root = insert(n, root);  
					break;
				//Delete 
				case 'd':
					scanf("%d", &n);
					printf("deleted %d! \n", n);
					root = delete(n, root);  
					break;
				//Search 
				case 's': 
					scanf("%d", &n);
					printf("searched %d! \n", n); 
					struct node *temp = search(n, root);
					break; 
				//Empty
				case 'e': 
					printf("empty! \n");
					empty(root);
					root = NULL;   
					break; 
				//Traversal
				case 't':
					scanf(" %c", &h); 
					if(h == 'l') preorder(root);  
					if(h == 'i') inorder(root);  
					if(h == 'r') postorder(root);
					printf("\n"); 
					break; 
				//Quit
				case 'q':
					empty(root); 
					return 0; 
				//Default
				default: 
					printf("Not a valid command! \n");    
		
			}
		}	
	}
  
	return 0; 
}


