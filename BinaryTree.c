/*
Authors: Daniel Brennan, Henry Shen, Conor Culleton
Project: Binary Tree for Algorithms
Due Date: 10/15/16
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node
{	 
	int key;
	int numCollisions;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
	struct Node *repeat;
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
		
		//creates new node for when we need to insert it
		Node *newNode = malloc(sizeof(Node));
		
		//this while loop finds where to input the key
		while(searchPtr != NULL){
			//if the key is already in the tree
			if(key == searchPtr->key){
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
		newNode->key = key;
		//if it should be a left leaf
		if (key < parentPtr->key){
			parentPtr->left = newNode;
			newNode->parent = parentPtr;
			newNode->numCollisions++;
			return searchPtr->key;
		}
		//if it should be a right leaf
		else if (key > parentPtr->key) {
			parentPtr->right = newNode;
			newNode->parent = parentPtr;
			newNode->numCollisions++;
			return searchPtr->key;
		}
		//if we fucked up
		else{
			printf("WtF happend.\n");
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
		
		//finding where the fuck dat key node is bruh
		while(!((searchPtr->key == key) || (searchPtr == NULL))){
			if(key < searchPtr->key){
				searchPtr = searchPtr->left;
			}
			else{ //searchPtr->key > key
				searchPtr = searchPtr->right;
			}
		}
		//if we were to go through the whole tree without finding the key
		if(searchPtr == NULL){
			printf("key was not found in the binary tree...fuck off.");
			return 0;
		}
		else{
			//if the node we want to delete is a leaf
			if ((searchPtr->right == NULL) && (searchPtr->left == NULL)){ 
				Node *tempParent = searchPtr->parent;
				//if the leaf we are trying to delete is a right node
				if(tempParent->right == searchPtr){
					tempParent->right = NULL;
					//so that you can print the number of collisions
					collprint = searchPtr->numCollisions;
					//delete the entire chain starts here
					Node *collisionPtr = searchPtr;
					//get us to the end of the chain deleting as we go.
					while(searchPtr->repeat != NULL){
						collisionPtr = searchPtr;
						searchPtr = searchPtr->repeat;
						free(collisionPtr);
					}
					return collprint;
				}
				//if the leaf we are trying to delete is a left node
				else if(tempParent->left == searchPtr){
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
					return collprint;
				}	
				//how can we return the amount of collisions after freeing the value?
				//should we create a new variable and set it equal to searchPtr->numCollisions? 
				return searchPtr->numCollisions;
			}
			else{ //not a leaf
				Node *tempParent = searchPtr->parent;
				//if its a right node, and there is no left node
				if((tempParent->right == searchPtr) && (tempParent->left == NULL)){
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
						searchPtr = searchPtr->repeat;
						free(collisionPtr);
					}
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
	//if it were to break out of the while loop without choosing 0 or 1 some shits gone wrong
	printf("Something went wrong with search of value %d", key);
}

//for predecessor and successor do the same thing we do to replace nodes after deleting them
//should find next largest key
int succ(int key, Node **rootPtr){
	//if the key is not in the tree return -1;
	if(search(key,&*rootPtr) == 0){
		return -1;
	}
	//if the key is min return -1
	if(key == min(&*rootPtr)){
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
		//case 1 if it has a right pointer
		if(searchPtr->right != NULL){
			//go one to the right
				searchPtr = searchPtr->right;
			
			//go all the way to the left until it is a leaf
			while(searchPtr->left != NULL){ //go to leftmost node in the right subtree
				searchPtr = searchPtr->left;	
			}
			//return the value of the succ
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


int main(int argc, char const *argv[]){
	Node *root = NULL;
	int numNodes = 0;
	char line[32];
	FILE *input = fopen(argv[1], "r");
	while(fgets(line, 32, input) != NULL){
		//printf("something here\n");

		char instruct[3];
		int val = 0;
		// fscanf(input, "%s %d", instruct, &val);
		//strncpy(instruct, line, 3);
		fscanf(input, "%s %d", instruct, &val);

		/*for (int i = 0; i < 3; ++i){
			printf("some\n");
			instruct[i] = line[i];
			//printf(instruct[i]);
		};*/

		// scanf("%s %d", line)
		// strncopy(instruct, line, 3);
		
		if (strncmp(instruct, "INS", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf(" at insert!! \n");
			printf("%d", insert(val, &root));
			numNodes++;
		}
		else if (strncmp(instruct, "DEL", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf(" at del!! \n");
			printf("%d", delete(val, &root));
			numNodes--;
		}
		else if (strncmp(instruct, "SEA", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf(" at seach!! \n");
			printf("%d", search(val, &root));
		}
		else if (strncmp(instruct, "MIN", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf(" at min!! \n");
			printf("%d", min(&root));
		}
		else if (strncmp(instruct, "SUC", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf(" succ \n");
			printf("%d", succ(val, &root));
		}
		else if (strncmp(instruct, "HEI", 3) == 0){
			//printf(instruct);
			printf("%d", val);
			printf(" height\n");
			printf("dicks out for harambe \n");
			float height = log10(numNodes+1)/log10(2);
			printf("%f\n", height);
		}
		else {
			printf("None of the above.\n");
		}
		printf("end of loop\n");
	}
	printf("\nHello World\n");

	insert(1, &root);
	fclose(input);
	return 0;

}
