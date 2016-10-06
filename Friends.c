#include <stdio.h>
using namespace std;

struct Node
{	
	int key;
	Node *successor = NULL;
	Node *left = NULL;
	Node *right = NULL;
}; 
//the root pointer of the tree 
Node *rootPtr = NULL;

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
		Node 
		if (key <= rootPtr->key){
			searchPtr = searchPtr->left;
		}
		else{
			searchPtr = searchPtr->right;
		}
		//everything else after root
		while(searchPtr != NULL){
			if(key <= searchPtr->key){

			}
		}
	}
}
int main(int argc, char const *argv[])
{
	printf("Hello World\n");
	return 0;
}