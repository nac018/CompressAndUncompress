/* Authors: Nang Chen (cs100fao)
 *          Haonan Huang (cs100fbd)		 
 * Date: 11/05/2017
 * Description: This class implements the way to write on bit
 * 		from the buffer and also send the buffer to 
 * 		the output stream and clear it.
 * Assignment: PA3
 * File: BitOutputStream.cpp
 */

#include "BitOutputStream.h"

/** Send the bitwise buffer to the output stream,
 *  and clear the bitwise buffer
 */  
void BitOutputStream::flush(){
	out.put(buf);
	out.flush();
	buf = 0;
	nbits = 0;
}

/** Write bit to the bitwise buffer
 */  
void BitOutputStream::writeBit(unsigned int bit){
	if(nbits == 8){
		flush();
	}
	if(bit==1){
		buf=buf|(bit)<<nbits;
	}
	else{
		buf=buf& ~(1<<nbits); 
	}
	nbits++;
}

/** Deal with the case that when nbits is not full
 */ 
void BitOutputStream::writeLast(){
	if(nbits != 0)
		out.put(buf);
}

