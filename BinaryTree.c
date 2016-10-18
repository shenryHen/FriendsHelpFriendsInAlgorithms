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
	//if the tree is empty create the tree inserting the new key as the root
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

		//this while loop finds where to input the key
		while(searchPtr != NULL){
			//if the key is already in the tree
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
		//inserts node onto the end of the tree
		Node *newNode = malloc(sizeof(Node));
		newNode->key = key;
		//if it should be a left leaf
		if (key < parentPtr->key){
			parentPtr->left = newNode;
			newNode->parent = parentPtr;
			newNode->numCollisions++;
			return key;
		}
		//if it should be a right leaf
		else if (key > parentPtr->key) {
			parentPtr->right = newNode;
			newNode->parent = parentPtr;
			newNode->numCollisions++;
			return key;
		}
		//if we fucked up
		else{
			printf("WtF happend.\n");
			free(newNode);
		}
	}
}

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

//will return the maximum key
//the maximum should be the rightmost leaf of the tree
int max(Node **rootPtr){
//we will initially set our pointer to the root of the tree
	Node *searchPtr = *rootPtr;
	//if the tree is empty we will return 0 instantly
	if(searchPtr){
		while (searchPtr->right != Null){
			//will go right until we reach the rightmost node
			searchPtr = searchPtr->right;
		}
		return searchPtr->key;
	}
	else{//in the event that this fucks up
		return -1;
	}
}

//will return the minimum key
//the minimum should be all the way on the leftmost leaf of the tree
int min(Node **rootPtr){
//we will initially set our pointer to the root of the tree
	Node *searchPtr = *rootPtr;
	//if the tree is empty we will return 0 instantly
	if(searchPtr){
		//will go left until we reach the leftmost node
		while (searchPtr->left != Null){
			searchPtr = searchPtr->left;
		}
		return searchPtr->key;
	}
	else{//in the event that this fucks up
		return -1;
	}
}

//search the tree for a key
//will return 1 if the key is found in the tree
//or 0 if it is not
int search(int key, Node **rootPtr){
	Node *searchPtr = *rootPtr;
	
	//will keep searching until it returns or we reach the end of the tree
	while(searchPtr != NULL){
		//search left of current spot in tree
		if(key < searchPtr->key){
			searchPtr = searchPtr->left;
		}
		//search right of current spot in tree
		else if (key > searchPtr->key){
			searchPtr = searchPtr->right;
		}
		//the key has been found
		else if (key == searchPtr->key){
			return 1;
		}
		else{ //the key was not found in the tree
			return 0;
		}
	}
	//if it were to break out of the while loop without choosing 0 or 1 some shits gone wrong
	printf("Something went wrong with search of value %d", key);
}

//for predecessor and successor do the same thing we do to replace nodes after deleting them
int succ(int key, Node **rootPtr){
	//if the key is not in the tree return -1;
	if(search(key) == 0){
		return -1;
	}
	//if the key is min return -1
	if(key == min(*rootPtr){
		return -1;
	}
	//if the key is the max return -1
	if(key == max(*rootPtr){
		return -1;
	}
	//if the tree is empty return -1
	if(rootPtr = NULL){
		return -1;
	}
	//set the searchPtr equal to the root
	Node *searchPtr = *rootPtr;
	
	//find where the key is in the tree
	//search left of current spot in tree
	if(key < searchPtr->key){
		searchPtr = searchPtr->left;
	}
	//search right of current spot in tree
	else if (key > searchPtr->key){
		searchPtr = searchPtr->right;
	}
	//the key has been found
	else if (key == searchPtr->key){
		//go one to the right
			searchPtr = searchPtr->right;
			
		//go all the way to the left until it is a leaf
		while(searchPtr->left != NULL){ //go to leftmost node in the right subtree
			searchPtr = searchPtr->left;	
		}
		//return the value of the succ
		return searchPtr->key;
	}
}

int main(int argc, char const *argv[])
{
	Node *root = NULL;
	printf("Hello World\n");
	insert(1, &root);
	return 0;
}


/*while(searchPtr != NULL){
	if (searchPtr->key == key){
		Node *newPtr = searchPtr->right; //right might be null, 
		while(newPtr->left != NULL){ //go to leftmost node in the right subtree
			
		}
		break;
	}
}*/

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
				}*/