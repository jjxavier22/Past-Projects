#ifndef LeafNodeH
#define LeafNodeH

#include "BTreeNode.h"

class LeafNode:public BTreeNode
{
  int *values;
public:
  LeafNode(int LSize, InternalNode *p, BTreeNode *left,
    BTreeNode *right);
  int internalSize;
  int getMinimum() const;  // called by parent
  LeafNode* insert(int value); // called by parent, sibling, or BTree::insert()
    // Returns pointer to new Leaf if it splits else NULL
  void print(Queue <BTreeNode*> &queue);
  LeafNode* split(int value);
}; //LeafNode class

#endif
