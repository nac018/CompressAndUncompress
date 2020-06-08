#include "HCNode.h"

using namespace std;

//overload < operator to compare frequencies and ascii value of symbols
bool HCNode::operator<(const HCNode& other){
	if(this->count != other.count){
		return this->count > other.count;
	}
	return this->symbol < other.symbol;
};
