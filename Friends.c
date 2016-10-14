#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{	 
	int key;
	int numCollisions;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
} Node; 
//the root pointer of the tree 

/*
	rules: 
	only for duplicates
		if node->left is null, add to left
		if node->left is full, add to right
		if node->right is full, add to left->left
*/

//inserts the node into the tree,
//can accept duplicate keys
//@param key, the key to be inserted
//@param rootPtr, should be the root of the tree 
int insert(int key, Node **rootPtr){
	Node *ptr;
<<<<<<< HEAD
	//if the tree is empty create the tree inserting the new key as the root
=======
>>>>>>> refs/remotes/origin/master
	if (!*rootPtr){
		ptr = malloc( sizeof(Node));
		ptr->key = key;
		*rootPtr = ptr;
	}
	else{
		//only for inserting at root
		//move this this block somewhere else 
		Node *searchPtr = *rootPtr;
		Node *parentPtr;

		while(searchPtr != NULL){
			if(key == searchPtr->key){
				searchPtr->numCollisions++;
			}
			else if (key < searchPtr->key){
				//something happens...magic
				parentPtr = searchPtr;
				searchPtr = searchPtr->left;
			}
			else { //when (key is > searchPtr->key)
				parentPtr = searchPtr;
				searchPtr = searchPtr->right;
			}	
		}
<<<<<<< HEAD
		//inserts node onto the end of the tree
=======
>>>>>>> refs/remotes/origin/master
		Node *newNode = malloc(sizeof(Node));
		newNode->key = key;
		if (key < parentPtr->key){
			parentPtr->left = newNode;
<<<<<<< HEAD
			newNode->parent = parentPtr;
			newNode->numCollisions++;
			return key;
		}
		else if (key > parentPtr->key) {
			parentPtr->right = newNode;
			newNode->parent = parentPtr;
			newNode->numCollisions++;
			return key;
=======
		}
		else if (key > parentPtr->key) {
			parentPtr->right = newNode;
>>>>>>> refs/remotes/origin/master
		}
		else{
			printf("WtF happend.\n");
			free(newNode);
		}
	}
}
<<<<<<< HEAD

int delete(int key, Node **rootPtr){
	//if the tree is empty return
	if(!*rootPtr){
		return 0;
	}
	//if the tree is not empty
	else{
		Node *searchPtr = *rootPtr;
		Node *parentPtr;
		
		//finding where the fuck dat key node is bruh
		while(!((searchPtr->key == key) || (searchPtr == NULL))){
			if(key < searchPtr->key){
				searchPtr = searchPtr->left;
			}
			else{ //searchPtr->key > key
				searchPtr = searchPtr->right;
			}
		}
		//if we were to go through the whole tree 
		if(searchPtr == NULL){
			printf("key was not found in the binary tree...fuck off.");
			return 0;
		}
		else{
			if (searchPtr->right == NULL){ //if deleted node is a leaf
				Node *tempParent = searchPtr->parent;
				tempParent->right = NULL;
				free(searchPtr);
				//how can we return the amount of collisions after freeing the value?
				//should we create a new variable and set it equal to searchPtr->numCollisions? 
				return searchPtr->numCollisions;
			}
			else if (searchPtr->left == NULL){
				Node *tempParent = searchPtr->parent;
				tempParent->left = NULL;
				free(searchPtr);
				//how can we return the amount of collisions after freeing the value?
				//should we create a new variable and set it equal to searchPtr->numCollisions? 
				return searchPtr->numCollisions;
			}
			else{ //not a leaf
				Node *newPtr = searchPtr->right; //right might be null, 
				while(newPtr->left != NULL){ //go to leftmost node in the right subtree
					newPtr = newPtr->left;	
				}
				searchPtr->key = newPtr->key;
				if (newPtr->right != NULL){ // if newPtr has right children
					newPtr->parent->left = newPtr->right;
					//need to return
				}
			}
		}
	}
}
=======
>>>>>>> refs/remotes/origin/master
int main(int argc, char const *argv[])
{
	Node *root = NULL;
	printf("Hello World\n");
	insert(1, &root);
	return 0;
}


<<<<<<< HEAD
/*while(searchPtr != NULL){
	if (searchPtr->key == key){
		Node *newPtr = searchPtr->right; //right might be null, 
		while(newPtr->left != NULL){ //go to leftmost node in the right subtree
			
		}
		break;
	}
}*/

=======
>>>>>>> refs/remotes/origin/master
/*if (searchPtr->left == NULL){
					//insert key in to left 
					searchPtr->left = malloc(sizeof(Node));
					searchPtr = searchPtr->left; //this step for referencing only
					searchPtr->key = key;
					searchPtr->parent = parentPtrnew;
				}
				else if (searchPtr->right == NULL){
					searchPtr->right = new Node;
					searchPtr = searchPtr->right; //this step for referencing only
					searchPtr->key = key;
					searchPtr->parent = parentPtr;
				}
				else{
					parentPtr = searchPtr;
					searchPtr = searchPtr->left;
<<<<<<< HEAD
				}*/
=======
				}*/
>>>>>>> refs/remotes/origin/master
