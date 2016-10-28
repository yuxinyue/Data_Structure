/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	//cout<<"tkey"<<t->key<<endl;
	Node * y = t->right;
        //cout<<"ykey"<<y->key<<endl;
	t->right = y->left;
	y->left = t;
	t = y;
	t->left->height = 1 + max(heightOrNeg1(t->left->left), heightOrNeg1(t->left->right));
	t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}


template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	Node * y = t->left;
	t->left = y->right;
	y->right = t;
	t = y;
	t->right->height = 1 + max(heightOrNeg1(t->right->left), heightOrNeg1(t->right->right));
	t->height = 1 + max(heightOrNeg1(t->left), heightOrNeg1(t->right));
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl; // Outputs the rotation name (don't remove this)
    // your code here
	rotateRight(t->right);
	rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
	if(subtree == NULL) return;
	//rebalance(subtree->left);
	//rebalance(subtree->right);
	//cout<<subtree->value<<endl;
	//cout<<__LINE__<<endl;
	int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
	//cout<<"balance"<<balance<<endl;
	if(balance == -2){
		int leftBalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
		//cout<<"leftbalance"<<leftBalance<<endl;
		if(leftBalance == -1)
			rotateRight(subtree);
		else
			rotateLeftRight(subtree);
	}
	if(balance == 2){
		int rightBalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
		if(rightBalance == 1)
			rotateLeft(subtree);
		else
			rotateRightLeft(subtree);
	}
	//cout<<__LINE__<<endl;
	subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
	//cout<<__LINE__<<endl;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
	if(subtree == NULL){
		subtree = new Node(key, value);
		return;
	}
	if(key < subtree->key)
		insert(subtree->left, key, value);
	if(key > subtree->key)
		insert(subtree->right, key, value);	
	rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
	remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
		delete subtree;
		subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
		Node * & iop = rightMostChild(subtree->left);
		swap(subtree, iop);
		remove(iop, iop->key);		
        } else {
            /* one-child remove */
            // your code here
		Node * temp = subtree;
		if(subtree->left == NULL) subtree = subtree->right;
		else subtree = subtree->left;
		delete temp;
        }
        // your code here
	//rebalance(subtree);
    }
	rebalance(subtree);
}

template <class K, class V>
typename AVLTree<K, V>::Node *& AVLTree<K, V>::rightMostChild(Node * & sroot){

	if(sroot->right == NULL) return sroot;
	else return rightMostChild(sroot->right);
}

