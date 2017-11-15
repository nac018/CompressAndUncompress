/* Authors: Nang Chen (cs100fao)
 *          Haonan Huang (cs100fbd)		 
 * Date: 11/05/2017
 * Description: This class implements the nodes of huffman coding tree.
 * Assignment: PA3
 * File: HCNode.cpp
 */


#include "HCNode.h"

using namespace std;

//overload < operator to compare frequencies and ascii value of symbols
bool HCNode::operator<(const HCNode& other){
	if(this->count != other.count){
		return this->count > other.count;
	}
	return this->symbol < other.symbol;
};
