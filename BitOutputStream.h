#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>

using namespace std;

class BitOutputStream{
	private:
		//bitwise buffer
		unsigned char buf;
		//number of bits that have been written to the bitwise buffer
		int nbits;
		//reference to the bytewise output stream
		std::ostream & out;

	public:
		//constructor
		BitOutputStream(ostream & os) : out(os), buf(0), nbits(0) {}
		void flush();
		void writeBit(unsigned int bit);
                void writeLast();
};

#endif

