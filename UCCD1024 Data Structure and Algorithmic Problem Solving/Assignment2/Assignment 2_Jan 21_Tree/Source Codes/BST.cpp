#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}


bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}

void BST::preOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}

void BST::inOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}

void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}


int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}

void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}

bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}

void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}


void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}


bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}

void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}


bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}

void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}

void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}


int BST::findMax(int a, int b){
	if (a > b) return a;
	else return b;
}


int BST::height(BTNode *cur) {
	if (cur == NULL) return 0;// handle special case
	return cur->height;// do normal process
}


void BST::allocateHeight() {
	if (root == NULL) return;// handle special case
	else allocateHeight2(root);// do normal process
}


void BST::allocateHeight2(BTNode *cur) {
	if (cur == NULL) return;// handle special case
	// do normal process
	allocateHeight2(cur->left);
	allocateHeight2(cur->right);
	cur->height = 1 + findMax(height(cur->left),height(cur->right));
}


int BST::getBalance(BTNode *cur) {
	if (cur == NULL) return 0;// handle special case
	return (height(cur->left) - height(cur->right));// do normal process
}


void BST::searchParent(BTNode *cur, BTNode * item) {
	if (cur == NULL) return;// handle special case
	if (cur == item) return;// handle spacial case 2
	// do normal process
	if (cur->left == item || cur->right == item) {
		parent = cur;
		return;
	}
	searchParent(cur->left, item);
	searchParent(cur->right, item);
}


void BST::balancing(BTNode *cur) {
	if (cur == NULL) return;// handle special case
	BTNode *sub, *sub2, *temp;
	balancing(cur->left);
	balancing(cur->right);

	int diff = getBalance(cur);
	searchParent(root, cur);

	if (diff > 1 || diff < -1) {
		if (diff > 1) {
			sub = cur->left;
			if (getBalance(sub) > 0) {
				// CASE LL
				// rotate right side
				sub = cur->left;
				sub2 = sub->right;

				sub->right = cur;
				cur->left = sub2;

				// relocate previous pointer
				if (cur == root) 
					root = sub;
				else {
					if (parent->item.id < sub->item.id)
						parent->right = sub;
					else
						parent->left = sub;
				}
				return;
			}
			else if (getBalance(sub) <= 0) {
				//CASE LR
				// rotate left side
				temp = cur->left;
				sub = temp->right;
				sub2 = sub->left;

				sub->left = temp;
				temp->right = sub2;
				cur->left = sub;
				// rotate right side
				sub = cur->left;
				sub2 = sub->right;

				sub->right = cur;
				cur->left = sub2;

				// relocate previous pointer
				if (cur == root)
					root = sub;
				else {
					if (parent->item.id < sub->item.id)
						parent->right = sub;
					else
						parent->left = sub;
				}
				return;
			}
		}
		else if (diff < -1) {
			sub = cur->right;
			if (getBalance(sub) <= 0) {
				// CASE RR
				// rotate left side
				sub = cur->right;
				sub2 = sub->left;

				sub->left = cur;
				cur->right = sub2;

				// relocate previous pointer
				if (cur == root)
					root = sub;
				else {
					if (parent->item.id < sub->item.id)
						parent->right = sub;
					else
						parent->left = sub;
				}
				return;
			}
			else if (getBalance(sub) > 0) {
				//CASE RL
				// rotate right side
				temp = cur->right;
				sub = temp->left;
				sub2 = sub->right;

				sub->right = temp;
				temp->left = sub2;
				cur->right = sub;
				// rotate left side
				sub = cur->right;
				sub2 = sub->left;

				// relocate previous pointer
				sub->left = cur;
				cur->right = sub2;

				if (cur == root)
					root = sub;
				else {
					if (parent->item.id < sub->item.id)
						parent->right = sub;
					else
						parent->left = sub;
				}
				return;
			}
		}
	}
}


bool BST::deepestNodes() {
	if (root == NULL) return false;
	BTNode			*cur;
	Queue		    q;
	int height_level = root->height;

	q.enqueue(root);	// Step 1: enqueue the first node

	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);

		if (cur->height == height_level) {

			if (cur->left != NULL && cur->left->height == height_level - 1) {
				q.enqueue(cur->left);
				if (cur->left->height == 1)
					cur->left->item.print(cout);
			}
			
			if (cur->right != NULL && cur->right->height == height_level - 1) {
				q.enqueue(cur->right);
				if (cur->right->height == 1)
					cur->right->item.print(cout);
			}
		}
		if (q.head != NULL) {
			if (q.head->item->height != height_level)
				height_level--;
		}
	}
	return true;
}


bool BST::display(int order, int source) {
	ofstream out;
	if (source == 1) {
		if (order == 1) {
			if(!ascendingPrint(cout))
				return false;
		}
		else if (order == 2) {
			if(!descendingPrint(cout))
				return false;
		}
	}
	else if (source == 2) {
		out.open("student-info.txt");
		if (order == 1) {
			if(!ascendingPrint(out))
				return false;
		}
		else if (order == 2) {
			if(!descendingPrint(out))
				return false;
		}
		out.close();
	}
	else
		cout << "< Input out of range >\n";
	return true;
}

bool BST::ascendingPrint(ostream &out) {
	if (root == NULL) return false;// handle special case
	else ascendingPrint2(root, out);// do normal process
	cout << endl;
	return true;
}

void BST::ascendingPrint2(BTNode *cur, ostream &out) {
	if (cur == NULL) return;// handle special case
	ascendingPrint2(cur->left, out);
	cur->item.print(out);
	ascendingPrint2(cur->right, out);
}


bool BST::descendingPrint(ostream &out) {
	if (root == NULL) return false;  // handle special case
	else descendingPrint2(root, out);// do normal process
	cout << endl;
	return true;
}

void BST::descendingPrint2(BTNode *cur, ostream &out) {
	if (cur == NULL) return;// handle special case
	descendingPrint2(cur->right, out);
	cur->item.print(out);
	descendingPrint2(cur->left, out);
}


bool BST::CloneSubtree(BST stuTree, type item) {
	BTNode *cur = stuTree.root;       // pass in t1 root;
	if (stuTree.empty())             // if t1 is empty return false else call CloneSubtree2()
		return false;
	CloneSubtree2(cur, item);
	return true;
}

void BST::CloneSubtree2(BTNode *cur, type item) {
	if (cur == NULL) return;	// handle special case
	if (cur->item.compare2(item)) {      // if cur item equal to the item then call CloneSubtree3()
		CloneSubtree3(cur);
		return;
	}
	CloneSubtree2(cur->left, item);
	CloneSubtree2(cur->right, item);
	return;
}

void BST::CloneSubtree3(BTNode *cur) {
	if (cur == NULL) return;	// handle special case
	insert(cur->item);              // insert the item in the clonetree
	CloneSubtree3(cur->left);
	CloneSubtree3(cur->right);
}


bool BST::printAncestor(type item) {
	if (root == NULL) return false;	// handle special case
	cout << "Node: " << item.id << "| Ancestors: ";
	if (root->item.id == item.id)	// handle special case 2
		cout << "No ancestor" << endl;
	return printAncestor2(root, item);	// do normal process
}

bool BST::printAncestor2(BTNode *cur, type item) {
	if (cur == NULL) return false;	// handle special case
	if (cur->item.id == item.id) return true; // do normal process
	if (printAncestor2(cur->left, item) || printAncestor2(cur->right, item)) {
		cout << cur->item.id << " ";
		return true;
	}
	return false;
}


bool BST::printSpiral(){
	if (root == NULL) return false;	// handle special case
	int h = root->height;
	//left to right equal to false, if variable is set, then the level is traversed from left to right.
	bool ltr = false;              
	for (int i = 1; i <= h; i++) {
		printSpiral2(root, i, ltr);
		//Revert ltr to traverse next level in opposite order
		ltr = !ltr;
	}
	return true;
}

void BST::printSpiral2(BTNode* cur, int level, int ltr){   //Print the nodes at a given level 
	if (cur == NULL) return; // handle special case
	if (level == 1)
		cout << cur->item.id << " ";

	else if (level > 1) {
		if (ltr) {
			printSpiral2(cur->left, level - 1, ltr);
			printSpiral2(cur->right, level - 1, ltr);
		}
		else {
			printSpiral2(cur->right,	level - 1, ltr);
			printSpiral2(cur->left, level - 1, ltr);
		}
	}
}