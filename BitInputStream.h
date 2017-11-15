/* Authors: Nang Chen (cs100fao)
 *          Haonan Huang (cs100fbd)		 
 * Date: 11/05/2017
 * Description: Header file of BitInputStream.cpp
 * Assignment: PA3
 * File: BitInputStream.h
 */

#ifndef BITINPUTSTREAM_H
#define BITINPUTSTREAM_H

#include <iostream>

using namespace std;

class BitInputStream{
	private:
		//bitwise buffer
		unsigned char buf;
		//number of bits that have been read from the bitwise buffer
		int nbits;
		//reference to the bytewise input stream
		std::istream & in;

	public:
		//constructor
		BitInputStream(istream & is):in(is), buf(0), nbits(8){}
		void fill();
		unsigned int readByte();
        	unsigned int readBit();
};

#endif
