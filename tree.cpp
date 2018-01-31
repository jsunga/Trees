#include "tree.h"

Tree::Tree(): start(NULL) {}

Tree::Tree(const Tree& other) {
	start = NULL; //initialization
	copyOther(other); //copy nodes
}

Tree::~Tree() {
	clear(); //delete nodes
}

Tree& Tree::operator=(const Tree& other) {
	if (this != &other) { 
		clear(); //delete tree if it is not empty
		copyOther(other); //copy nodes
	}
	return *this;
}

void Tree::push(int value) {
	TreeNode* temp = new TreeNode(); //create node
	temp->value = value;
	if (start == NULL) { //if tree empty then insert node to root
		start = temp;
		return;
	}
	pushFrom(start, temp); //else pushFrom
} 

TreeNode* Tree::find(int value) const {
	return findFrom(start, value);
}

void Tree::print() const {
	printFrom(start, 0);
}

void Tree::deleteNode(int value) {
	deleteFrom(start, value);
} 

//private functions
void Tree::copyOther(const Tree& other) {
	copyFrom(other.start);
}

void Tree::clear() {
	if (start == NULL) return;
	clearFrom(start);
}

void Tree::pushFrom(TreeNode* startingPoint, TreeNode* nodeToPush) {
	if (startingPoint->value < nodeToPush->value) { //case 1: value is greater than root
		if (startingPoint->right == NULL) //sub case 1: right side of root is empty
			startingPoint->right = nodeToPush; 
		else //sub case 2: not empty
			pushFrom(startingPoint->right, nodeToPush); //traverse through nodes to find NULL
	} else { //case 2: value is less than root
		if (startingPoint->left == NULL) //sub case 1:left side of root is empty
			startingPoint->left = nodeToPush;
		else //sub case 2: NOT EMPTY
			pushFrom(startingPoint->left, nodeToPush); //traverse through nodes to find NULL
	}
}

TreeNode* Tree::findFrom(TreeNode* startingPoint, int value) const {
	if (startingPoint == NULL) return NULL; //base case
	if (startingPoint->value == value) return startingPoint; //case 1: value = root
	else if (value < startingPoint->value) //case 2: value in left root
		return findFrom(startingPoint->left, value); //traverse left
	else // case 3: value in right root
		return findFrom(startingPoint->right, value); //case 3: value in right root
}

void Tree::printFrom(TreeNode* startingPoint, int numSpaces) const {
	if (startingPoint == NULL) return; //base case
	for (int i = 0; i < numSpaces; i++)	
		cout << " ";
	cout << startingPoint->value << endl;
	numSpaces = numSpaces + 2; //2 spaces for wider diagonal
	printFrom(startingPoint->left, numSpaces); //traverse left
	printFrom(startingPoint->right, numSpaces); //traverse right
}

void Tree::copyFrom(TreeNode* startingPoint) {
	if (startingPoint == NULL) return; //base case
	push(startingPoint->value); //push pre-order
	copyFrom(startingPoint->left); //traverse left
	copyFrom(startingPoint->right); //traverse right
}

void Tree::deleteFrom(TreeNode* startingPoint, int value) {
	bool found = false;
	TreeNode* p = NULL; //parent
	TreeNode* c = startingPoint; //cursor
	
	if (c == NULL) return;
	
	//find the node
	while (c != NULL) {
		if (c->value == value) {
			found = true;
			break;
		} else {
			p = c;
			if (value > c->value)
				c = c->right;
			else
				c = c->left;
		}
	}
	
	if (!found) return; //return if node to be deleted does not exist in the tree
	
	//case 1: node with a single child
	if ((c->left == NULL && c->right != NULL) || (c->left != NULL && c->right == NULL)) {
		if (c->left == NULL && c->right != NULL) { //case: child is a right leaf
			if (p->left == c) { //parent's left tree is current
				//parent's left tree becomes currents's right tree and delete current
				p->left = c->right;
				delete c;
				c = NULL;
			} else { //parent's right tree is current
				//parent's right tree becomes current's right tree and delete current
				p->right = c->right;
				delete c;
				c = NULL;
			}
		} else { //case: child is left leaf
			if (p->left == c) {
				p->left = c->left;
				delete c;
				c = NULL;
			} else {
				p->right = c->left;
				delete c;
				c = NULL;
			}
		}
	//case 2: leaf
	} else if (c->left == NULL && c->right == NULL) {
		if (p->left == c)
			p->left = NULL;
		else
			p->right = NULL;
		delete c;
	//case 3: node has two children then replace node with smallest value in right subtree
	} else if (c->left != NULL && c->right != NULL) {
		TreeNode* temp = c->right;
		if (c->left == NULL && c->right == NULL) {
			c = temp;
			delete temp;
			c->right = NULL;
		} else { 
			/*
			case: right child has children
			if the current's right child has a left child then 
			move all the way down left
			*/
			if (c->right->left != NULL) {
				TreeNode* leftC;
				TreeNode* leftCP;
				leftCP = c->right;
				leftC = c->right->left;
				while (leftC->left != NULL) {
					leftCP = leftC;
					leftC = leftC->left;
				}
				c->value = leftC->value;
				delete leftC;
				leftCP->left = NULL;
			} else {
				TreeNode* temp = c->right;
				c->value = temp->value;
				c->right = temp->right;
				delete temp;
			}
		}
	}
}

void Tree::clearFrom(TreeNode* startingPoint) {
	if (startingPoint == NULL) return; //base case
	clearFrom(startingPoint->left); //traverse left
	clearFrom(startingPoint->right); //traverse right
	delete startingPoint; //delete node postorder
	start = NULL; 
}
