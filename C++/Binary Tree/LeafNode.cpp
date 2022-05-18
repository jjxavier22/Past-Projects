#include <iostream>
#include "LeafNode.h"
#include "InternalNode.h"
#include "QueueAr.h"

using namespace std;


LeafNode::LeafNode(int LSize, InternalNode *p,
  BTreeNode *left, BTreeNode *right) : BTreeNode(LSize, p, left, right)
{

  values = new int[LSize];

}  // LeafNode()



int LeafNode::getMinimum()const
{
  if(count > 0)  // should always be the case
    return values[0];
  else
    return 0;

} // LeafNode::getMinimum()


LeafNode* LeafNode::insert(int value)
{
  // students must write this

	if(count<leafSize){
		if (count == 0){
			values[0] = value;
			//count++;

		} else{
			//cout<<"count is not 0\n";
			for (int pos = count - 1; pos >= 0; pos--){

					/*for (int i = 0; i < leafSize; i++){
						cout<<values[i]<<" ";
					}*/


				if (values[pos] > value){
					values[pos+1] = values[pos];
					values[pos] = value;
					//count++;

				}

				else{
					values[pos+1] = value;
					//count++;
					break;

				}
				//count++;;


			}
			//count++;



		}count++;

	} else if (leftSibling && leftSibling->getCount() < leafSize){
	
		if(value < getMinimum()){
			leftSibling->insert(value);
		} else if (value > getMinimum()){
			leftSibling->insert(values[0]);
			for (int pos = 0; pos < count-1; pos++){
				values[pos] = values[pos+1];

			}
			values[count-1] = 0;
			count--;
			insert(value);


		}


	} else if (rightSibling && rightSibling->getCount() < leafSize){

		if(value > values[leafSize-1]){

			rightSibling->insert(value);
		}
		else if (value < values[leafSize-1]) {

			rightSibling->insert(values[leafSize-1]);
			values[leafSize-1] = 0;
			count--;
			insert(value);

		}


	} else {
		LeafNode* newNode = split(value);
	
		return newNode;
	}







	if(parent){

		parent->updateMinimums();

	}

    return NULL; // to avoid warnings for now.
}  // LeafNode::insert()

void LeafNode::print(Queue <BTreeNode*> &queue)
{
  cout << "Leaf: ";
  for (int i = 0; i < count; i++)
    cout << values[i] << ' ';
  cout << endl;
} // LeafNode::print()




LeafNode* LeafNode::split(int value){
	LeafNode* splittedNode = NULL;


	if(rightSibling){
		splittedNode = new LeafNode(leafSize, parent,this,rightSibling);
		rightSibling->setLeftSibling(splittedNode);
	}
	else{
		splittedNode = new LeafNode(leafSize, parent,this,NULL);
	}

	rightSibling = splittedNode;


	//even number split
	if (leafSize%2!=0){

		if (values[leafSize/2] > value){

			for(int pos = leafSize/2; pos < leafSize; pos++){

				splittedNode->insert(values[pos]);
				values[pos] = 0;
				count--;

			}
			LeafNode::insert(value);

		}
		else{
		
			for(int pos = (leafSize/2) + 1; pos < leafSize; pos++){
				
				splittedNode->insert(values[pos]);
				values[pos] = 0;
				count--;

			}
			splittedNode->insert(value);
		}




	} else{
		if (values[(leafSize/2)-1] < value){
			splittedNode->insert(value);
			for(int pos = leafSize/2; pos < leafSize; pos++){
				splittedNode->insert(values[pos]);
				values[pos] = 0;
				count--;
			}



		}
		else {
			for(int pos = (leafSize/2) -1; pos < leafSize; pos++){
				splittedNode->insert(values[pos]);
				values[pos] = 0;
				count--;
			}
			LeafNode::insert(value);

		}
	}


	
	return splittedNode;
}
