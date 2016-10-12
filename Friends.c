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
		Node *newNode = malloc(sizeof(Node));
		newNode->key = key;
		if (key < parentPtr->key){
			parentPtr->left = newNode;
		}
		else if (key > parentPtr->key) {
			parentPtr->right = newNode;
		}
		else{
			printf("WtF happend.\n");
			free(newNode);
		}
	}
}
int main(int argc, char const *argv[])
{
	Node *root = NULL;
	printf("Hello World\n");
	insert(1, &root);
	return 0;
}


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