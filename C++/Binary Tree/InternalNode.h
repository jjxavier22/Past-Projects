#ifndef InternalNodeH
  #define InternalNodeH

#include "BTreeNode.h"

class InternalNode:public BTreeNode
{
  int internalSize;
  BTreeNode **children;
  int *keys;
public:
  InternalNode(int ISize, int LSize, InternalNode *p, BTreeNode *left, 
    BTreeNode *right);
  int getMinimum()const;
  void updateMinimums(); // called by child with new minimum
  InternalNode* insert(int value); // returns pointer to new InternalNode
    // if it splits else NULL
  void insert(BTreeNode *newNode); // from a sibling or BTree::insert()
  void print(Queue <BTreeNode*> &queue);
  int getCount();
  InternalNode *split(BTreeNode *splitted);
}; // InternalNode class

#endif
