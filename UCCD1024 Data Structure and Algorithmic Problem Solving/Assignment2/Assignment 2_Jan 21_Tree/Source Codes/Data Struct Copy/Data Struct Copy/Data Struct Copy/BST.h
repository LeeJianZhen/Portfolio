#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

		int		count;
		BTNode	*root;

		// print operation for BST (same as BT)					
		void preOrderPrint2(BTNode *);	// recursive function for preOrderPrint()
		void inOrderPrint2(BTNode *);	// recursive function for inOrderPrint()
		void postOrderPrint2(BTNode *);	// recursive function for postOrderPrint()

		// sample operation (extra functions) - same as BT
		void countNode2(BTNode *, int &);		// recursive function for countNode()
		bool fGS2(type, BTNode *);					// recursive function for findGrandsons(): to find the grandfather
		void fGS3(BTNode *, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found
		
		// basic functions for BST
		void insert2(BTNode *, BTNode *);		// recursive function for insert() of BST
		void case3(BTNode *);					// recursive function for remove()
		void case2(BTNode *, BTNode *);		// recursive function for remove()
		bool remove2(BTNode *, BTNode *, type);	// recursive function for remove()



		// basic functions for BST
		BST();
		bool empty();
		int size();
		bool insert (type);		// insert an item into a BST
		bool remove(type);			// remove an item from a BST
		
		// print operation for BST (same as BT)
		void preOrderPrint();			// print BST node in pre-order manner
		void inOrderPrint();			// print BST node in in-order manner
		void postOrderPrint();			// print BST node in post-order manner
		void topDownLevelTraversal();	// print BST level-by-level

		// sample operation (extra functions) - same as BT
		int countNode();		// count number of tree nodes
		bool findGrandsons(type);	// find the grandsons of an input father item

		// NEW ADD
		// function for balancing the tree
		BTNode *parent;
		int findMax(int a, int b);		// calculate the height for two integer
		int height(BTNode *);			// return the hight of a node
		void allocateHeight();			// allocate height for each node
		void allocateHeight2(BTNode *);	// recursive function for allocateHeight()
		int getBalance(BTNode *);		// calculate the different between node's left and right height
		void searchParent(BTNode *, BTNode *);	//search parent node
		void AVLsort(BTNode *);			// sort deepest unbalance tree

		// New add
		bool deepestNodes();			// display deepest node from a BST
		void deepestNodes2(BTNode *);	// recursive function for deepestNode()
		bool display(int, int);			// print the content of a BST
		void ascendingPrint(ostream &);	// print node by ascending order
		void ascendingPrint2(BTNode *, ostream &);	// recursive function for ascendingPrint(ostream &)
		void descendingPrint(ostream &);			// print node by descending order
		void descendingPrint2(BTNode *, ostream &);	// recursive function for descendingPrint(ostream &)
		ofstream out;
};




#endif