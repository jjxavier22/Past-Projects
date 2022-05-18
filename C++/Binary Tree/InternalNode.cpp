#include <iostream>
#include "InternalNode.h"

using namespace std;

InternalNode::InternalNode(int ISize, int LSize,
  InternalNode *p, BTreeNode *left, BTreeNode *right) :
  BTreeNode(LSize, p, left, right), internalSize(ISize)
{
  keys = new int[internalSize]; // keys[i] is the minimum of children[i]
  children = new BTreeNode* [internalSize];
} // InternalNode::InternalNode()


int InternalNode::getMinimum()const
{
  if(count > 0)   // should always be the case 
    return children[0]->getMinimum();
  else
    return 0;
} // InternalNode::getMinimum()


InternalNode* InternalNode::insert(int value)
{
  // students must write this
 BTreeNode* splitted;
 
    for(int pos  = count - 1; pos >= 0; pos--){

      if ((value<keys[pos] && value>keys[pos-1]) && pos>0){


        splitted = children[pos-1]->insert(value);
        break;

      } else if (value > keys[count-1]){
        splitted = children[count-1]->insert(value);
        break;
      } else if (value<keys[0]){

        splitted = children[0]->insert(value);
        break; 
      }
        else if (pos == 1){

        splitted = children[0]->insert(value);
        break;
      }

    }
    updateMinimums();

  if (splitted){
 
    if(count<internalSize){
 
      insert(splitted);

    } else {

        if( leftSibling && leftSibling->getCount() < internalSize) {
          if(splitted->getMinimum() < getMinimum()){
            ((InternalNode*)leftSibling)->insert(splitted);
          } else if (splitted->getMinimum() > getMinimum()){
            children[0]->setParent(((InternalNode*)leftSibling));
            ((InternalNode*)leftSibling)->insert(children[0]);
            for (int pos = 0; pos < count-1; pos++){
              children[pos] = children[pos+1];
              keys[pos]=keys[pos+1];

            }
            keys[count-1] = 0;
            children[count-1] = NULL;
            count--;
            insert(splitted);


          }

        } else if(rightSibling && rightSibling->getCount() < internalSize){
            if(splitted->getMinimum() > keys[count-1]){
              ((InternalNode*)rightSibling)->insert(splitted);
            } else{
              children[count-1]->setParent(((InternalNode*)rightSibling));
              ((InternalNode*)rightSibling)->insert(children[count-1]);
              keys[count-1] = 0;
              children[count-1] = NULL;
              for(int i = 0; i < count; i++){
                cout<<keys[i]<<" ";
              }
              cout<<","<<count;
              count--;
              insert(splitted);
            }
        } else {
          InternalNode* newNode = split(splitted);
          return newNode;
        }


    }

  }
  return NULL; 
} 


void InternalNode::insert(BTreeNode *newNode) // from a sibling or BTree::insert
{
  // students must write this
  if (count < internalSize){
  
    children[count] = newNode;
 
    keys[count]=newNode->getMinimum();

      for (int pos = count - 1; pos >= 0; pos--){
      
        if (keys[pos] > newNode->getMinimum()){
          keys[pos+1] = keys[pos];
          keys[pos] = newNode->getMinimum();
          children[pos+1]=children[pos];
          children[pos]=newNode;
        }

        else{
     
          keys[pos+1] = newNode->getMinimum();
          children[pos+1]=newNode;
          break;

        }

      }

    count++;
  }
  newNode->setParent(this);
} // InternalNode::insert()

void InternalNode::print(Queue <BTreeNode*> &queue)
{
  int i;

  cout << "Internal: ";
  for (i = 0; i < count; i++)
    cout << keys[i] << ' ';
  cout << endl;

  for(i = 0; i < count; i++)
    queue.enqueue(children[i]);

} // InternalNode::print()


void InternalNode::updateMinimums()
{ // called by child with a new minimum
  // students must write this
  for(int pos = 0; pos < count; pos++){
    keys[pos] = children[pos]->getMinimum();
  }

}   // InternalNode::updateMinimums


int InternalNode::getCount(){
  return(count);
}


InternalNode * InternalNode::split(BTreeNode* splitted){


  InternalNode *splittedInternalNode;
  if(rightSibling){
    splittedInternalNode = new InternalNode(internalSize,leafSize,parent,this,rightSibling);
    rightSibling->setLeftSibling(splittedInternalNode);
  } else {
    splittedInternalNode = new InternalNode(internalSize,leafSize,parent,this,NULL);
  }
  rightSibling=splittedInternalNode;







  if (internalSize%2!=0){
    if (keys[internalSize/2] > splitted->getMinimum()){
      for(int pos = internalSize/2; pos < internalSize; pos++){
 
        children[pos]->setParent(splittedInternalNode);
        splittedInternalNode->insert(children[pos]);
        keys[pos] = 0;
        children[pos]=NULL;
        count--;
      }
  
      insert(splitted);

    }
    else{
 
      for(int pos = (internalSize/2) + 1; pos < internalSize; pos++){
 
        children[pos]->setParent(splittedInternalNode);
        splittedInternalNode->insert(children[pos]);
        keys[pos] = 0;
        children[pos] = NULL;
        count--;

      }
      splittedInternalNode->insert(splitted);
    }


//ODD NUMBER SPLIT

  } else{
    if (keys[(internalSize/2)-1] < splitted->getMinimum()){
      splittedInternalNode->insert(splitted);
      for(int pos = internalSize/2; pos < internalSize; pos++){
        splittedInternalNode->insert(children[pos]);
        keys[pos] = 0;
        children[pos]=NULL;
        count--;
      }



    }
    else {
      for(int pos = (internalSize/2) -1; pos < internalSize; pos++){
        splittedInternalNode->insert(children[pos]);
        keys[pos] = 0;
        children[pos]=NULL;
        count--;
      }
      insert(splitted);
    }
  }


  updateMinimums();
  splittedInternalNode->updateMinimums();
  return splittedInternalNode;

}
