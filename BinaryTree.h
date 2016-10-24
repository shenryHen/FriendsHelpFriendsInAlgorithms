typedef struct Node 
{	 
	int key;
	int numCollisions;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
	struct Node *repeat;
} Node;
int insert(int key, Node **rootPtr);
int delete(int key, Node **rootPtr);
int max(Node **rootPtr);
int min(Node **rootPtr);
int search(int key, Node **rootPtr);
int succ(int key, Node **rootPtr);
int pred(int key, Node **rootPtr);