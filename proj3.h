//proj3.h

#ifndef PROJ3_H
#define PROJ3_H

//a struct for the road
struct node{
	int value; 
	struct node *left, *right; 
};

//Helper to create a new node. 
struct node *makeNode(int key);

//Takes in a value and makes a node for it.
struct node *insert(int key, struct node* node);

//preorder traversal 
void preorder(struct node *root);

//inorder traversal 
void inorder(struct node *root);

//postorder traversal 
void postorder(struct node *root);

//search for the given node in the tree. 
struct node *search(int key, struct node *root); 

//Traverse through the tree and free all of the nodes. 
void empty(struct node *root);   

//Helper for delete. Returns the min. 
struct node *min(struct node *n); 

//Deletes the node with the given key. 
struct node *delete(int key, struct node *node); 

#endif
