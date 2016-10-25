/*
Authors: Daniel Brennan, Henry Shen, Conor Culleton
Project: Binary Tree for Algorithms
Due Date: 10/15/16
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BinaryTree.h"

/*typedef struct Node
{	 
	int key;
	int numCollisions;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
	struct Node *repeat;
} Node;*/ 
//the root pointer of the tree 

/*
	rules: 
	only for duplicates
		if node->left is null, add to left
		if node->left is full, add to right
		if node->right is full, add to left->left
*/
int numNodes = 0;

//inserts the node into the tree,
//can accept duplicate keys
//@param key, the key to be inserted
//@param rootPtr, should be the root of the tree 
int insert(int key, Node **rootPtr){
	printf("\tin insert ");
	printf("%d\n", key);
	Node *searchPtr = *rootPtr;
	Node *parentPtr = NULL;
	Node *newNode = malloc(sizeof(Node));
	newNode->key = key;
	newNode->right = NULL; 
	newNode->left = NULL;
	newNode->parent = NULL;
	newNode->repeat = NULL;
	//if the tree is empty create the tree inserting the new key as the root
	if (!*rootPtr){
		printf("\ttree empty \n");
		*rootPtr = newNode;
		//ERROR HERE?? *rootPtr = searchPtr;
		return newNode->key;
	}
	else{
		printf("\tadding to tree\n");
		if (key == searchPtr->key){ // if key is == root's key
			printf("addind to root, chaining\n");
				searchPtr->numCollisions++;
				Node *collisionPtr = searchPtr->repeat;
				if (collisionPtr == NULL){
					collisionPtr = newNode;
				}
				else{
					printf("\tgo to chain here\n");
				}
				return newNode->key;
		}
		//printf("search ptrs = %d %d \n ", searchPtr->left, searchPtr->right);
		//printf("searchPtr key = \n %d ", searchPtr->key);
		//printf("decl some vars \n");
		//only for inserting at root
		//move this this block somewhere else 
		/*if ((searchPtr->left == NULL) || (searchPtr->right == NULL)){ // if adding to root node
			
			printf("both sides null \n");
			if (key < searchPtr->key){
				searchPtr->left = newNode;
				printf("err\n");
				numNodes++;
			}
			else if(key > searchPtr->key){
				searchPtr->right = newNode;
				printf("err\n");
				numNodes++;
			}
			else{
				printf("do somee chanining here....\n");
			}
			return newNode->key;
		}*/
		//creates new node for when we need to insert it		
		//this while loop finds where to input the key
		// while right or left  point to nodes, wont run if both are null
		while(searchPtr != NULL){
			//print("\tin while\n");
			////print("%d\n ", searchPtr->key);
			//if the key is already in the tree
			if(key == searchPtr->key){
				//print("Chaining...\n");
				//make sure to keep track of the number of collisions
				searchPtr->numCollisions++;
				//collisionPtr is created to bring us to the end of the chain
				Node *collisionPtr = searchPtr;
				//while loop to bring us to the end of the repeat chain
				while(collisionPtr->repeat != NULL){
					collisionPtr = collisionPtr->repeat;
				}
				//add newNode to the end of the chain
				collisionPtr->repeat = newNode;
				newNode->key = key;
				return newNode->key;
			}
			else if (key < searchPtr->key){
				//print("\tleft\n");
				//something happens...magic
				parentPtr = searchPtr;
				searchPtr = searchPtr->left;
				//print("\t parentPtr key %d\n", parentPtr->key);
			}
			else { //when (key is > searchPtr->key)
				//print("\tright\n");
				parentPtr = searchPtr;
				searchPtr = searchPtr->right;
				//print("\treassigned ptrs\n");
			}	
		}
		//print("\tadding new node to tree %d \n", parentPtr->key);
		//inserts node onto a leaf of the tree
		numNodes++;
		//if it should be a left leaf
		if (key < parentPtr->key){
			//print("\tadding left\n");
			newNode->parent = parentPtr;
			parentPtr->left = newNode;
/*				printf("\t right, left = %d ", searchPtr->left->key);
			printf("\t parent = %d \n",  newNode->parent->key);*/
			return newNode->key;
		}
		//if it should be a right leaf
		else if (key >  parentPtr->key) {
			//print("\t adding rightr \n");
			newNode->parent = parentPtr;
			parentPtr->right = newNode;
			//	printf("\tadded left %d\n", parentPtr->right->key);
			return newNode->key;
		}
		//if we fucked up
		else{
			//should not reach here
			//print("\t key collision is %d\n", key);
			//print("\tcollision in node.\n");
			free(newNode);
		}
	}
}

int delete(int key, Node **rootPtr){
	//temporary variable so we can print the number of collisions
	int collprint = 0;
	//if the tree is empty return
	if(!*rootPtr){
		return 0;
	}
	//if the tree is not empty
	else{
		Node *searchPtr = *rootPtr;
		Node *parentPtr;
		printf("\tdeleting a node, root exists\n");
		//finding where the fuck dat key node is bruh
		while(!((searchPtr == NULL) || (searchPtr->key == key) )){
			printf("\tsearchPtr = ");
			printf("%d\n", searchPtr->key);
			if(key < searchPtr->key){
				
				searchPtr = searchPtr->left;
				printf("\twent left\n");
			}
			else{ //searchPtr->key > key
				printf("\twent right\n");
				searchPtr = searchPtr->right;
			}
		}
		//if we were to go through the whole tree without finding the key
		if(searchPtr == NULL){
			printf("%s\n", "key was not found in the binary tree...fuck off.");
			return 0;
		}
		else{
			printf("\tnow deleting %d \n", searchPtr->key);
			//if the node we want to delete is a leaf
			if ((searchPtr->right == NULL) && (searchPtr->left == NULL)){ 
				printf("\t is a leaf\n");
				Node *tempParent = searchPtr->parent;
				//printf("%d\n", );
				//if the leaf we are trying to delete is a right node
				if(tempParent->right == searchPtr){
					tempParent->right = NULL;
					//so that you can print the number of collisions
					collprint = searchPtr->numCollisions;
					printf("num on stack = %d\n", collprint);
					//delete the entire chain starts here
					Node *collisionPtr = searchPtr;
					//get us to the end of the chain deleting as we go.
					while(searchPtr->repeat != NULL){
						collisionPtr = searchPtr;
						searchPtr = searchPtr->repeat;
						free(collisionPtr);

					}
					numNodes--;
					return collprint;
				}
				//if the leaf we are trying to delete is a left node
				else if(tempParent->left == searchPtr){
					printf("\t chain to searchPtr here...\n");
					tempParent->left = NULL;
					collprint = searchPtr->numCollisions;
					//delete the entire chain starts here
					Node *collisionPtr = searchPtr;
					//get us to the end of the chain deleting as we go.
					while(searchPtr->repeat != NULL){
						collisionPtr = searchPtr;
						searchPtr = searchPtr->repeat;
						free(collisionPtr);
					}
					numNodes--;
					return collprint;
				}	
				//how can we return the amount of collisions after freeing the value?
				//should we create a new variable and set it equal to searchPtr->numCollisions? 
				return searchPtr->numCollisions;
			}
			else{ //not a leafs
				printf("\t\n", "not a leaf, deleting ");
				printf("%d", searchPtr->key);
				Node *tempParent = searchPtr->parent;
				//if is a root node
				if (tempParent == NULL){
					printf("%s\n", "\tdeleting root");
					if (searchPtr->left ==  NULL && searchPtr->right == NULL){
						printf("Root has no children\n");
						int numColl = searchPtr->numCollisions;
						free(searchPtr);
						return numColl;
					}
					//if root has no left children
					else if (searchPtr->left == NULL && searchPtr->right != NULL){
						printf("\troot has no only right children\n");
						Node *newPtr = searchPtr->right;
						int tempKey = searchPtr->key;
						while(newPtr->left != NULL){
							newPtr = newPtr->left;
						}
						searchPtr->key = newPtr->key;
						int numColl = searchPtr->numCollisions; 
						free(newPtr);
						numNodes--;
						return numColl;
					}
					//if root has no right chidlren
					else if (searchPtr->right == NULL && searchPtr->left != NULL){
						printf("\troot has only left children\n");
						Node *newPtr = searchPtr->left;
						printf("\t%d %d\n", searchPtr->key, newPtr->key);
						while(newPtr->right != NULL){
							newPtr = newPtr->right;
						}
						searchPtr->key = newPtr->key;
						int numColl = searchPtr->numCollisions; 
						free(newPtr);
						numNodes--;
						return numColl;
					}
					else{
						printf("\t root has children\n");
						Node *newPtr = searchPtr->left;
						while(newPtr->right != NULL){
							newPtr = newPtr->right;
						}
						searchPtr->key = newPtr->key;
						int numColl = searchPtr->numCollisions;
						printf(" num coll %d\n", numColl);
						free(newPtr);
						numNodes--;
						return numColl;
					}
					
				}

				//if its a right node, and there is no left node
				else if ((tempParent->right == searchPtr) && (tempParent->left == NULL)){
					tempParent->right = searchPtr->right;
					collprint = searchPtr->numCollisions;
					//delete the entire chain starts here
					Node *collisionPtr = searchPtr;
					//get us to the end of the chain deleting as we go.
					while(searchPtr->repeat != NULL){
						collisionPtr = searchPtr;
						searchPtr = searchPtr->repeat;
						free(collisionPtr);
					}
					numNodes--;
					return collprint;
				}
				//if its a left node, and there is no right node
				else if ((tempParent->left == searchPtr) && (tempParent->right == NULL)){

					tempParent->left == searchPtr->left;
					collprint = searchPtr->numCollisions;
					//delete the entire chain starts here
					Node *collisionPtr = searchPtr;
					//get us to the end of the chain deleting as we go.
					while(searchPtr->repeat != NULL){
						collisionPtr = searchPtr;
						searchPtr = *searchPtr->repeat;
						free(collisionPtr);
					}
					numNodes--;
					return collprint;
				}
				//if the node we are trying to delete has both right and left children
				else if ((tempParent->right != NULL) && (tempParent->left != NULL)){
					Node *newPtr = searchPtr->right; 
					while(newPtr->left != NULL){ //go to leftmost node in the right subtree
						newPtr = newPtr->left;	
					}
					searchPtr->key = newPtr->key;
					if (newPtr->right != NULL){ // if newPtr has right children(can't have left)
						newPtr->parent->left = newPtr->right;
						collprint = searchPtr->numCollisions;
						//delete the entire chain starts here
						Node *collisionPtr = searchPtr;
						//get us to the end of the chain deleting as we go.
						while(searchPtr->repeat != NULL){
							collisionPtr = searchPtr;
							searchPtr = searchPtr->repeat;
							free(collisionPtr);
						}
						numNodes--;
						return collprint;
					} 
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
		while (searchPtr->right != NULL){
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
		while (searchPtr->left != NULL){
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
	if (searchPtr == NULL){
		printf("%s\n", "searchptr is null");
		return 0;
	}
	//if it were to break out of the while loop without choosing 0 or 1 some shits gone wrong
	printf("Something went wrong with search of value %d", &key);
}

//for predecessor and successor do the same thing we do to replace nodes after deleting them
//should find next largest key
int succ(int key, Node **rootPtr){
	//if the key is not in the tree return -1;
	if(search(key, &*rootPtr) == 0){
		return -1;
	}
	//if the key is the max return -1
	if(key == max(&*rootPtr)){
		return -1;
	}
	//if the tree is empty return -1
	if(rootPtr == NULL){
		return -1;
	}
	printf("\ttraversing tree\n");
	//set the searchPtr equal to the root
	Node *searchPtr = *rootPtr;
	Node *parentPtr = NULL;
	//find where the key is in the tree
	//search left of current spot in tree
	while(searchPtr != NULL){
		if(key < searchPtr->key){
			searchPtr = searchPtr->left;
		}
		//search right of current spot in tree
		else if  (key > searchPtr->key){;
			searchPtr = searchPtr->right;
		}
		else 
			break;
	}
	printf("out of loop, %d \n", searchPtr->key);
	//searchPtr = parentPtr; // point searchptr back on to tree

	//the key has been found
	if (key == searchPtr->key){
		printf("\t key found %d \n", searchPtr->key);
		//case 1 if it has a right pointer
		if(searchPtr->right != NULL){
			//go one to the right
				searchPtr = searchPtr->right;
			
			//go all the way to the left until it is a leaf
			while(searchPtr->left != NULL){ //go to leftmost node in the right subtree
				searchPtr = searchPtr->left;	
			}
			//return the value of the succ
			printf("actual successor is %d\n", searchPtr->key);
			return searchPtr->key;
		}
		//else if it is a leaf/doesnt have a right pointer
		else{
			//if the pointer we are trying to find the succesor of is a right node
			if(searchPtr == searchPtr->parent->right){
				searchPtr = searchPtr->parent->parent;
			}
			//if the pointer we are trying to find a succesor of is a left node
			else if (searchPtr == searchPtr->parent->left){
				searchPtr = searchPtr->parent;
			}
			return searchPtr->key;
		}
	}
}

//should find next smallest key
int pred(int key, Node **rootPtr){
	//if the key is not in the tree return -1;
	if(search(key,&*rootPtr) == 0){
		return -1;
	}
	//if the key is min return -1
	if(key == min(&*rootPtr)){
		printf("\t key is last\n");
		return -1;
	}
	//if the key is the max return -1
	//if the tree is empty return -1
	if(rootPtr == NULL){
		return -1;
	}
	//set the searchPtr equal to the root
	Node *searchPtr = *rootPtr;
	while(searchPtr != NULL){
		//search left of current spot in tree
		if(key < searchPtr->key){
			searchPtr = searchPtr->left;
		}
		//search right of current spot in tree
		else if (key > searchPtr->key){
			searchPtr = searchPtr->right;
		}
		else 
			break;
	}
	
	//find where the key is in the tree
	
	//the key has been found
	if (key == searchPtr->key){
		printf("\t key found, %d \n", key );
		//case 1 if it has a left pointer
		if(searchPtr->left != NULL){
			//go one to the left
				searchPtr = searchPtr->left;
			
			//go all the way to the right until it is a leaf
			while(searchPtr->right != NULL){ //go to rightmost node in the right subtree
				searchPtr = searchPtr->right;	
			}
			//return the value of the succ
			return searchPtr->key;
		}
		//else if it is a leaf/doesnt have a left pointer
		else{
			//if the pointer we are trying to find the pred of is a left node
			if(searchPtr == searchPtr->parent->left){
				searchPtr = searchPtr->parent->parent;
			}
			//if the pointer we are trying to find a pred of is a right node
			else if (searchPtr == searchPtr->parent->right){
				searchPtr = searchPtr->parent;
			}
			return searchPtr->key;
		}
	}
}

int printTree(Node **rootPtr){
/*	Node *ptr = *rootPtr;
	printf("%d\n", ptr->key);
	 if(rootPtr == NULL)
      return;
  	printf("not null\n");
    printTree(&ptr -> left);
    printf("%d\n",ptr -> key);
    printTree(&ptr ->right);*/

}

int main(int argc, char const *argv[]){
	printf("Start ** !\n");
	Node *root = NULL;
	char line[32];
	char instruct[3];
	int val = 0;

	FILE *input = fopen(argv[1], "r");
	while(fscanf(input, "%s %d", instruct, &val) != EOF){
		//printf("something here\n");

		// fscanf(input, "%s %d", instruct, &val);
		//strncpy(instruct, line, 3);

		;
		if (strcmp(instruct, "MIN") == 0 || strcmp(instruct, "MAX") == 0 ||
				strcmp(instruct, "HEI") == 0){
			val = 0;	
			printf("%s\n", "val = 0");
		}
		printf("%s\n ", instruct );

		if (strncmp(instruct, "INS", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf(" at insert!! \n");
			int returned = insert(val, &root);
			if (returned > 0){
				printf("returned value = %d\n", returned);
			}
		}
		else if (strncmp(instruct, "DEL", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf("at del!! \n");
			printf("num deleted %d \n", delete(val, &root));
		}
		else if (strncmp(instruct, "SEA", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf("at search!! \n");
			printf("%d ", search(val, &root));
		}
		else if (strncmp(instruct, "MIN", 3) == 0){
			//printf(instruct);;
			printf("at min!! \n");
			printf("%d ", min(&root));
		}
		else if (strncmp(instruct, "MAX", 3) == 0){
			//printf(instruct);;
			printf("at min!! \n");
			printf("%d ", max(&root));
		}
		else if (strncmp(instruct, "SUC", 3) == 0){
			//printf(instruct);
			printf("at succ for %d is ", val); 
			printf("%d ", succ(val, &root));
		}
		else if (strncmp(instruct, "PRE", 3) == 0){
			printf("at pred for %d is ", val);
			printf("%d \n", pred(val, &root));	
		}
		else if (strncmp(instruct, "HEI", 3) == 0){
			//printf(instruct);
			printf("height\n");
			float height = log10(numNodes+1)/log10(2);
			printf("%f\n", height);
		}
		else {
			printf("None of the above.\n");
		}
	}
	return 0;

}
/*Node *leftSucc = searchPtr->right;
						Node *rightSucc = searchPtr->left;
						while(leftSucc->left != NULL){
							leftSucc = leftSucc->left;
						}
						while(rightSucc->right != NULL){
							rightSucc = rightSucc->right;
						}*/