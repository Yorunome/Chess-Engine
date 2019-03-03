//main program
#include "stdafx.h"
#include <iostream>
#include "init.cpp"
#include <assert.h>


using namespace std;

int main(){
	AllInit();
	/*int ctr = -1;
	for (auto index = 0; index < 64; index++) {
		ctr++;
		if (ctr == 8) {
			cout << endl; ctr = 0;
		}
		cout << SQ64ToSQ120[index] << "\t";
	}
	
	cout << endl << endl;

	for (int index = 0; index < BRD_SQ_NUM; ++index)
	{
		if (index % 10 == 0) cout << endl;
		cout << SQ120ToSQ64[index] << "\t";
	}

	//assert(0);
	*/
	
	U64 playBitBoard = 0ULL;

	cout << "Start:" << endl;
	printBitBoard(playBitBoard);

	playBitBoard = (1ULL << SQ64(D2)) | playBitBoard;
	cout << "D2 added:" << endl;
	printBitBoard(playBitBoard);

	playBitBoard = (1ULL << SQ64(G2)) | playBitBoard;
	cout << "G2 added:" << endl;
	printBitBoard(playBitBoard);

	int count = cnt(playBitBoard);
	cout << "Count: " << count << endl;

	int index = POP(&playBitBoard);
	cout << "Index: " << index << endl;
	printBitBoard(playBitBoard);

	for (int index = 0; index < 64; index++) {
		cout << "Index: " << index << endl;
		printBitBoard(SetMask[index]);
		cout << endl;
	}

	return 0;
}

