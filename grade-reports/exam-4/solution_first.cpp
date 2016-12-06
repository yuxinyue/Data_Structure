#include "common.h"
#include <iostream>
#include <algorithm>

/*
	The algorithm library is included if needed, for the function:
	max: returns the largest of the values passed as arguments.
*/

using namespace std;

Node<int> *& findIop(Node<int> * &croot){
	if(croot->right == NULL) return croot;
	else return findIop(croot->right);
}

void remove(Node<int> *&croot){
	if(croot == NULL) return;
	if(croot->left == NULL && croot->right == NULL){
		delete croot;
		croot = NULL;
	}
	else if(croot->right == NULL && croot->left != NULL){
		Node<int> * temp = croot;
		croot = croot->left;
		delete temp;
	}
	else if(croot->left == NULL && croot->right != NULL){
		Node<int> * temp = croot;
		croot = croot->right;
		delete temp;
	}
	else{
		Node<int> *& iop = findIop(croot->left);
		croot->data = iop->data;

		int tempH = iop->height;
		iop->height = croot->height;
		croot->height = tempH;

		remove(iop);
	}
}

void delete_helper(Node<int> *& croot, int target){
	if (croot == NULL) return ;
	if(croot->data == target){
		remove(croot);
	}
	else if(croot->data < target){
		 delete_helper(croot->left, target);
	}
	else  delete_helper(croot->right, target);
	//croot->height = max(croot->left->height, croot->right->height) + 1;
}

Node<int>* deleteNode(Node<int> *&root, int target)
{
	// YOUR CODE HERE!
	if(root == NULL) return NULL;
	delete_helper(root, target);
	return root;
}
