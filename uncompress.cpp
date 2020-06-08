#include <stdio.h>
#include "HCTree.h"
#include <string>

#define TWO 2
#define THREE 3
#define CHAR 256

using namespace std;

int main(int argc, const char * argv[]) {
	//if number of arguments is incorrect
	if (argc != THREE){
		cout<<"Incorrect number of arguments";
		return 0;
	}
	ifstream infile;
	ofstream outfile;
	int unique = 0;
	int before = 0;
	int after = 0;
	int read_freq;
	int temp;
	int tempIndex;
	int total =0;
	int tempIntIndex;
	vector<int> freqs(CHAR,0);
	unsigned char ch;

	BitOutputStream bit_outfile(outfile);

	//count the number of original file
	infile.open(argv[1]);
	while(1){
		if(infile.is_open()){
			ch = infile.get();
			if (infile.eof() || !infile.good()){
				break;
			}
			++before;
		}
	}
	infile.close();

	// read smaller header
	infile.open(argv[1]);
	cout << "Reading from file header of: " << argv[1] << "...";
	if(infile.is_open()){
		for(int i=0;i<CHAR;i++) {
			if (infile.eof() || !infile.good()){
				break;
			}
			infile >> tempIndex;
			infile >> temp;
			//check if the last line of header
			if (tempIndex == 0 && temp == 0) {
				break;
			}
			freqs[tempIndex] = temp;
			total += temp;
			unique++;
		}
	}
	else{
		return 0;
	}

	total -= 1;
	unique -= 1;
	cout << "done." << endl;
	cout << "Uncompressed file will have " << unique;
	cout << " unique symbols and size " << total << " bytes." << endl;


	cout << "Building Huffman code tree...";
	HCTree* tempTree = new HCTree();
	//build the huffman tree with the frequency vector
	tempTree->build(freqs);
	char tempChar;
	cout << "done." << endl;
	cout << "Writing to file " << argv[TWO] << "...";
	outfile.open(argv[TWO]);
	tempChar = infile.get();

	BitInputStream bit_infile(infile);

	//get the characters from the input file and decode them to 
	//the output file
	if(outfile.is_open()){
		for(int i = 0; i < total; i++){
			if (infile.eof() || !infile.good()){
				break;
			}
			tempChar = tempTree->decode(bit_infile);
			outfile << tempChar;
		}
	}
	else{
		return 0;
	}
	cout << "done." << endl;
	infile.close();
	outfile.close();
	cout << "Uncompression ratio: " << (double)total/before << endl;
	delete tempTree;
	return 0;
}
