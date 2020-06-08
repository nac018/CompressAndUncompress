#include "BitInputStream.h"

/** Fill the bitwise buffer by reading one byte from the input stream.
 */
void BitInputStream::fill(){
	buf = in.get();
	nbits = 0;
}

/** Read byte from the bitwise buffer
 */
unsigned int BitInputStream::readByte(){
	if(nbits == 8){
		fill();
	}
	
	unsigned int nextBit = 1 & (buf >>(7-nbits));
	nbits++;
	return nextBit;
}
/** Read bit from the bitwise buffer
 */
unsigned int BitInputStream::readBit(){
    if(nbits == 8){
        buf = in.get();
        nbits = 0;
    }
    char c = buf >> (nbits) & 1;
    nbits++;
    return (int) c;
}
