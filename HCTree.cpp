#include "HCTree.h"

using namespace std;

/** Build the huffman coding tree with priority queue.
 *  Combine two smallest nodes into a parent node and 
 *  push that node into the queue for next operaton.
 *  Stop until there's a root.
 */ 
void HCTree::build(const vector<int>& freqs){
	//make a priority queue
	std::priority_queue<HCNode*,std::vector<HCNode*>,HCNodePtrComp> pq;
	//push all the frequencies that are larger than 0 to the queue
	for(int i=0; i <256; i++){
		if(freqs[i]!=0){
			leaves[i] = new HCNode(freqs[i],i);
			pq.push(leaves[i]);
		}
	}
	//construction of the tree by finding two nodes with
	//highest priorities
	while(pq.size()>1){
		HCNode* child1 = pq.top();
		pq.pop();
		HCNode* child2 = pq.top();
		pq.pop();

		int sumCount = child1->count + child2->count;

		HCNode* parentNode = new HCNode(sumCount,0,child1,child2,0);
		child1->p=parentNode;
		child2->p=parentNode;
		pq.push(parentNode);
	}
	//if there is only one node
	if(pq.size() == 1)
	{
		root = pq.top();
		pq.pop();
	}
}

/** Encode the tree with a stack. Starting from the leaves 
 *  and find the path until the root. Pop the bits out of 
 *  the stack and write that to an ofstream output file.
 */ 
void HCTree::encode(byte symbol,ofstream& out) const{
	//start from leaves
	HCNode* current = leaves[symbol];
	//create stack
	stack<int> pathStack;
	//stop when current node has no parent
	while(current->p != 0){
		if(current == current->p->c0){
			pathStack.push(0);
		}		
		else if(current == current->p->c1){
			pathStack.push(1);
		}
		current = current->p;
	}
	//pop out the bits from the stack and write to output file
	while(pathStack.size()!=0){
		out << pathStack.top();
		pathStack.pop();
	}
}

/** Encode the tree with a stack. Starting from the leaves 
 *  and find the path until the root. Pop the bits out of 
 *  the stack and write that to an bitstream output file.
 */ 
void HCTree::encode(byte symbol,BitOutputStream& out) const{
	//start from leaves
	HCNode* current = leaves[symbol];
	//create stack
	stack<int> pathStack;
	//stop when current node has no parent
	while(current->p != 0){
		if(current == current->p->c0){
			pathStack.push(0);
		}
		else if(current == current->p->c1){
			pathStack.push(1);
		}
		current = current->p;
	}
	//pop out the bits from the stack and write to output file
	while(pathStack.size()!=0){
		out.writeBit(pathStack.top());
		pathStack.pop();
	}
}

/** Decode the tree. Starting from the root and find the path
 *  until the leaves. Stop when the node has no child. This 
 *  method takes in an ifstream input file.
 */ 
int HCTree::decode(ifstream& in) const{
	//start from root
	HCNode* current = root;
	int bit=0;
	//stop when current node has no child
	while(current->c0 != 0 && current->c1 != 0){
		//read bit from input file
		bit = in.get() >> (0) & 1;
		if(bit == 0){
			current = current->c0;
		}
		else if(bit == 1){
			current = current->c1;
		}
	}
	return current->symbol;
}

/** Decode the tree. Starting from the root and find the path
 *  until the leaves. Stop when the node has no child. This 
 *  method takes in an bitstream input file.
 */ 
int HCTree::decode(BitInputStream& in) const{
	//start from root
	HCNode* current = root;
	//stop when current node has no child
	while(current->c0 != 0 && current->c1 != 0){
		//read bit from input file
		int bit = in.readBit();
		if(bit == 0){
			current = current->c0;
		}
		else if(bit == 1){
			current = current->c1;
		}
	}
	return current->symbol;
}

/** Delete all the created points on heap.
 */ 
void HCTree::deleteAll(HCNode* n){
	if(n != 0){
		deleteAll(n->c0);
		deleteAll(n->c1);
		delete n;	
	}
}

/** Destructor
 */ 
HCTree::~HCTree(){
	deleteAll(root);
}
