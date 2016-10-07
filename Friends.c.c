#include <stdio.h>
using namespace std;

struct COLL
{
	int key;
	COLL *next = NULL;

};

struct Node
{	
	
	int key;
	Node *successor = NULL;
	Node *left = NULL;
	Node *right = NULL;
}; 
//the root pointer of the tree 
Node *rootPtr = NULL;
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

int insert(int key){
	if (rootPtr == NULL){
		rootPtr = new Node();
		rootPtr->key = key;
	}
	else{
		//only for inserting at root
		//move this this block somewhere else 
		Node *searchPtr = rootPtr;
		Node *parentPtr = NULL;
		if (key <= rootPtr->key){
			searchPtr = searchPtr->left;
		}
		else{
			searchPtr = searchPtr->right;
		}
		//everything else after root
		while(searchPtr != NULL){
			if(key == searchPtr->key){
				if (searchPtr->left == NULL){
					//insert key in to left 
					searchPtr->left = new Node;
					searchPtr = searchptr->left; //this step for referencing only
					searchPtr->key = key;
					searchPtr->successor = parentPtr;
				}
				else if (searchPtr->right == NULL){
					searchPtr->right = new Node;
					searchPtr = searchptr->right; //this step for referencing only
					searchPtr->key = key;
					searchPtr->successor = parentPtr;
				}
				else{
					parentPtr = searchptr;
					searchPtr = searchPtr->left;
				}
			}
			else if (key < searchPtr->key){
				//something happens...magic
			}
			else { //when key is > searchptr->key

			}	
		}
	}
}
int main(int argc, char const *argv[])
{
	printf("Hello World\n");
	return 0;
}