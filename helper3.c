//helper3.h created by Laurel Anderson
//Helper to proj3.c
#include <stdio.h> 
#include <stdlib.h>
#include "proj3.h"

//Helper function that makes a new node when called. 
struct node *makeNode(int key){

	struct node *t = (struct node*)malloc(sizeof(struct node)); 
	t->value = key; 
	t->left = t->right = NULL; 
	return t; 

}

//inserts a node with the given key -> value. 
struct node *insert(int key, struct node* node){
	
	if(node == NULL) return makeNode(key); 
	
	if(key <= node->value){ 
		node->left = insert(key, node->left);
	}else{ 
		node->right = insert(key, node->right);
	}
}

//Preorder walk. 
void preorder(struct node *root){

	if(root == NULL) return; 
	printf("%d ", root->value);
	preorder(root->left); 
	preorder(root->right); 

}

//Inorder walk. 
void inorder(struct node *root){

	if(root == NULL) return; 
	inorder(root->left);
	printf("%d ", root->value); 
	inorder(root->right); 

}

//Postorder walk. 
void postorder(struct node *root){

	if(root == NULL) return; 
	postorder(root->left); 
	postorder(root->right);
	printf("%d ", root->value); 

}

//A helper function that searches the tree and prints whether it is in the tree. 
struct node *search(int key, struct node *root){

	if(root == NULL){
		printf("%d is not here :( \n", key);
		return root; 
	}else if(root->value == key){
		printf("%d is here! :D \n", key);
		return root; 
	}

	if(key < root->value){
		root->left = search(key, root->left); 
	}else{
		root->right = search(key, root->right);
	}
	return root;
 
}

//Function that does a postorder traversal of the tree and frees all of the nodes. 
void empty(struct node *root){

	if(root == NULL) return; 
	empty(root->left); 
	empty(root->right); 
	free(root); 

}

//Finds the smallest in order successor of a node that we pass in and returns it. Helper to delete. 
struct node *min(struct node *node){

	struct node* t = node; 

	while(t->left && t != NULL){
		t=t->left; 
	}
	return t; 
}

//Find a node with the key given and delete it. 
struct node *delete(int key, struct node *node){

	if(node==NULL) return node; 

	if(search(key, node)==NULL){ 
		return node; 
	}	
	
	//traverse the tree. 
	if(key < node->value){
		node->left = delete(key, node->left); 	
	}else if(key > node->value){
		node->right = delete(key, node->right);
	//You have found the node that you want to get rid of.  
	}else{ 

		//case with either 1 or no child nodes. 
		if(node->right==NULL){

			struct node *t = node->left; 
			free(node);  
			return t;  

		}else if(node->left==NULL){
			
			struct node *t = node->right; 
			free(node);  
			return t; 			  
		}
		//case with two nodes that are occupied. 
		struct node *t = min(node->right); 
		
		node->value = t->value; 
		
		node->right = delete(t->value, node->right); 
		
	}
	return node; 
}

