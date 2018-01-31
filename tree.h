#ifndef _TREE_H
#define _TREE_H

#include <cstdlib>   // necessary in order to use NULL
#include <iostream>

using namespace std;

class TreeNode
{
public:
	TreeNode() : left(NULL), right(NULL) {}

	TreeNode* left;
	TreeNode* right;
	int value;
};

class Tree
{
public:
	// Default constructor
	Tree();

	// Copy constructor
	Tree(const Tree& other);

	//Destructor
	~Tree();

	// overloaded Assignment Operator
	Tree& operator=(const Tree& other);

	// Similar to insert function we discussed earlier
	// creates node and inserts it at appropriate position.
	void push(int value);

	// Returns the address of the node containing the value.
	TreeNode* find(int value) const;

	// Print the tree data
	void print() const;

	// Deletes the node with value in the tree and deallocates its memory.
	void deleteNode(int value);

private:
	// Root of the tree.
	TreeNode* start;

	//copyOther
// you should implement and use this helper function inside your
// copy constructor and overloadedAssignment operator.
	void copyOther(const Tree& other);

	// clear
// you should implement and use this function inside your 
// destructor to delete all the nodes and free memory
	void clear();

	// pushFrom
// Recursively push a single element into a tree.
// Use it in your push function.
	void pushFrom(TreeNode* startingPoint, TreeNode* nodeToPush);
	
	// findFrom
// Recursively find a single element in a tree.
	TreeNode* findFrom(TreeNode* startingPoint, int value) const;

	// printFrom
//
// Recursively print the values in a tree. Use
// pre-order traversal.
//
// If a tree looks like this:
//
//           6
//          /  \
//         /    \
//        5      8
//       /      / \
//      /      /   \
//     0      7     9
//
// then it should be printed like this:
//
// 6
//   5
//     0
//   8
//     7
//     9
// 
//  Helper function that you should use inside your print function
	void printFrom(TreeNode* startingPoint, int numSpaces) const;

	// copyFrom
// Recursively copy another tree's nodes. Use
// pre-order traversal. Use this in CopyOther function.
	void copyFrom(TreeNode* startingPoint);

	// deleteFrom
// should implement and use in the delete function.
// Deletes the node with the value specified in the below function. 
	void deleteFrom(TreeNode* startingPoint, int value);

	// clearFrom
// Recursively delete nodes. Use post-order traversal.
	// Use it in clear function.
	void clearFrom(TreeNode* startingPoint);
};

#endif
