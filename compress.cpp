/* Authors: Nang Chen (cs100fao)
 *          Haonan Huang (cs100fbd)		 
 * Date: 11/05/2017
 * Description: This class implements the way to read a file
 * 		with bitwise input stream and write all the symbols
 * 		into the Huffman encoding tree to encode it. Then 
 * 		we output the encoded strings to a output file.
 * Assignment: PA3
 * File: compress.cpp
 */

#include <stdio.h>
#include "HCTree.h"
#include <utility>
#define TWO 2
#define THREE 3
#define FULLCHAR 256

using namespace std;

int main(int argc, const char * argv[]) {
	//if number of arguments is incorrect
	if (argc != THREE){
		cout<<"Incorrect number of arguments"<<endl;
		return 0;
	}
	cout<<"a";
	//create ifstream and ofstream objects
	ifstream infile;
	ofstream outfile;
	unsigned char nextChar;
	//count of unique symbols
	int unique = 0;
	//count of original bytes
	int before = 0;
	//count of bytes after compression
	int after = 0;
	vector<int> freqs(FULLCHAR,0);
	BitInputStream bit_infile(infile);
	BitOutputStream bit_outfile(outfile);
	infile.open(argv[1],ios::binary);

	cout << "Reading from file: " << argv[1] << "...";
	//read from input file
	while (1) {
		if(infile.is_open()){
			if (infile.eof() || !infile.good()){
				break;
			}
			nextChar = infile.get();
			freqs[nextChar]++;
			++before;
			if(freqs[nextChar] == 1){
				unique++;
			}
		}
		else{
			return 0;
		}
	}
	cout << "done." << endl;
	cout << "Found " << unique << " unique symbols in input file of size ";
	cout << before << " bytes." << endl;
	infile.close();


	//building a smaller vector
	int j=0;
	vector<pair<int,int>> smalleFreqs(unique,std::make_pair(0,0));
	for (int i=0; i<FULLCHAR; i++) {
		if (freqs[i]!=0) {
			smalleFreqs[j]=make_pair(i,freqs[i]);
			j++;
		}
		if (j==unique) {
			break;
		}
	}
	// use a smaller vector to write the file
	outfile.open(argv[TWO]);
	cout << "Writing to file " << argv[TWO] << "...";
	if(outfile.is_open()){
		for(int i = 0; i < smalleFreqs.size();i++){
			outfile << smalleFreqs[i].first;
			outfile << " ";
			outfile << smalleFreqs[i].second << endl;
		}
	}
	//set a line to indicate the end of header
	outfile << 0;
	outfile << " ";
	outfile << 0 << endl;


	cout << "Building Huffman code tree...";
	HCTree* tempTree = new HCTree();
	//build the huffman tree with the frequency vector
	tempTree->build(freqs);
	cout << "done." << endl;

	infile.open(argv[1]);
	//get the characters from the input file and encode them to the
	//output file
	while (1) {
		if(infile.is_open()){
			nextChar = infile.get();
			if (infile.eof() || !infile.good()){
				break;
			}
			tempTree->encode(nextChar,bit_outfile);
		}
		else{
			return 0;
		}
	}
	//deal with the "less than 8 bits" situation
	bit_outfile.writeLast();

	cout << "done." << endl;

	infile.open(argv[1]);
	outfile.close();
	ifstream readOut;
	readOut.open(argv[TWO]);
	nextChar=' ';

	//count the number of bytes of the output file
	while(1){
		if(readOut.is_open()){
			nextChar = readOut.get();
			if (readOut.eof() || !readOut.good()){
				break;
			}
			++after;
		}
	}

	cout << "Output file has size " << after << " bytes." << endl;
	cout << "Compression ratio: " << (double)after/before << endl;

	infile.close();
	outfile.close();
	bit_outfile.flush();
	delete tempTree;
	return 0;
}
