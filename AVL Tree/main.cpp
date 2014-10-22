#include <stdlib.h>
#include <iostream>
#include <stdio.h>

using namespace std;

struct node {
	int data;
	node* left, *right;
};

node* doBalanceTree(node *z, node* y, node *x);


node* createNode(int data) {
	node* aNewNode = (node*)malloc(sizeof(node));
	aNewNode->data = data;
	aNewNode->left = NULL;
	aNewNode->right = NULL;

	return aNewNode;
}

void printTreeInOrder(node* root) {
	if (root == NULL) return;
	printf("%d ",root->data);
	if (root->left) printTreeInOrder(root->left);
	if (root->right) printTreeInOrder(root->right);
}

int sizeTree(node *root) {
	if (root == NULL) return 0;
	return (1 + sizeTree(root->left) + sizeTree(root->right));
}


int sizeDifferent(node *root) {
	return(sizeTree(root->left) - sizeTree(root->right));
}


int max(int a, int b) {
	return (a > b)? a: b;
}

int heightTree(node *root) {
	if (root == NULL) return 0;
	return (1 + max(heightTree(root->left), heightTree(root->right) ));
}

int heightDifferent(node *root) {
	if (root == NULL) return 0;
	return (heightTree(root->left) - heightTree(root->right));
}


//balanced if size difference in [-1..1]
// < -1 : right tree bigger than left tree
// > 1 : left tree bigger than right tree
bool isBalanced(node *root) { 
	int difference = heightDifferent(root);

	if (abs(difference) <=1 ) return true;
	return false;
}


// node z is the first node that unbalanced
// node y is the child on the way of inserting W
// node z is the grandchild of z on the way of inserting W
node* insertNode(node *root, int W, node* z, node* y, node *x, bool *foundPath) {
	if (root == NULL) {
		root = createNode(W);
		return root;
	}

	if (root->data > W) { // insert on left subTree
		root->left = insertNode(root->left,W,z,y,x, foundPath);

	} else if (root->data < W) {
		root->right = insertNode(root->right,W,z,y,x, foundPath);

	}
	
	if (!(*foundPath) && !isBalanced(root)) {
		*foundPath = true; // already found needed node, no need other node
		z = root;
		
		// find y
		if (W > z->data) y = z->right;
		else y = z->left;

		if (W > y->data) x = y->right;
		else x = y->left;

		root = doBalanceTree(z,y,x);
	}
	return root;
}


// 4 cases to take care
// with assumption that already known that tree from root is unbalanced
node* doBalanceTree(node *z, node* y, node *x) { 
	// case1: left left case
	if ( (y == z->left) && (x == y->left) ) {
		node* rightY = y->right;
		y->right = z;
		z->left = rightY;
		z = y;

		return z;
	}

	if ( (y == z->left) && (x == y->right) ) {
		// left rotate (y)
		node* leftX = x->left;
		z->left = x;
		x->left = y;
		y->right = leftX;

		// right rotate (z)
		node* rightX = x->right;
		x->left = z;
		z->left = rightX;

		return x;
	}
	
	if ( (z->right == y) && (x == y->right) ) {
		//left rotate z
		node* leftY = y->left;
		y->left = z;
		z->right = leftY;

		return y;
	}

	if ( (z->right == y) && (x == y->left) ) {
		//right rotate y
		y->left = x->right;
		x->right = y; //leftZ
		z->right = x;

		//left rotate z
		z->right = x->left;
		x->left = z;

		return x;
	}
}


void main() {

	//follow the example at http://jriera.webs.ull.es/Docencia/avl_handout.pdf
	node* root = NULL;
	node* z = NULL;
	node* y = NULL;
	node* x = NULL;
	bool foundPath = false;
	root = insertNode(root,3, z, y, x, &foundPath);

	foundPath = false;
	root = insertNode(root,2, z, y, x, &foundPath);
	
	foundPath = false;
	root = insertNode(root,1, z, y, x, &foundPath);
	
	foundPath = false;
	root = insertNode(root,4, z, y, x, &foundPath);
	
	foundPath = false;
	root = insertNode(root,5, z, y, x, &foundPath);

	foundPath = false;
	root = insertNode(root,6, z, y, x, &foundPath);

	foundPath = false;
	root = insertNode(root,7, z, y, x, &foundPath);

	foundPath = false;
	root = insertNode(root,16, z, y, x, &foundPath);

	foundPath = false;
	root = insertNode(root,15, z, y, x, &foundPath);

	
	foundPath = false;
	root = insertNode(root,14, z, y, x, &foundPath);

	cout<< "Tree inOrder: " ; 
	printTreeInOrder(root);
	cout << "\n";

	//cout << "Balance Property: " << isBalanced(root);
	//cout << "\n";
}