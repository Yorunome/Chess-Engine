#include <iostream>

using namespace std;

//array with 64 integers
const int bitTable[64] = { 
	63, 30,  3, 32, 25, 41, 22, 33, 
	15, 50, 42, 13, 11, 53, 19, 34,
	61, 29,  2, 51, 21, 43, 45, 10,
	18, 47,  1, 54,  9, 57,  0, 35, 
	62, 31, 40,  4, 49,  5, 52,	26,
	60,  6, 23, 44, 46, 27, 56, 16,
	 7, 39, 48, 24, 59, 14, 12, 55,
	38, 28, 58, 20, 37, 17, 36,  8
};

//takes a pointer to bitboard, starting from LSB
//finds the index where the first bit is set and then removes it
int popBit(U64 *bb){
	U64 b = *bb ^ (*bb - 1);
	unsigned int fold = (unsigned)((b & 0xffffffff));
	*bb &= (*bb - 1);
	return bitTable[(fold * 0x783a9b23) >> 26];
}

//takes a bitboard and count the number of set bits
int countBits(U64 b){
	int r;
	for (r = 0; b; r++, b &= b - 1);
	return r;
}

void printBitBoard(U64 bb){
	U64 shiftMe = 1ULL;			//for the shift operations

	int rank = 0;				//for board positions
	int file = 0;				//for board positions
	int sq = 0;
	int sq64 = 0;

	cout << endl;

	for (rank = RANK_8; rank >= RANK_1; --rank)	{
		for (file = FILE_A; file <= FILE_H; ++file){
			sq = FR2SQ(file, rank);			//120 based index
			sq64 = SQ64(sq);				//64 based index for the 64 bit number
			if ((shiftMe << sq64) & bb)		//1ULL << position_on_64bitboard (eg. 11) & bitboard 
				cout << 'X';				//print X if a bit is set at current square 
			else
				cout << '-';				//otherwise print blank marker (dash)
		}
		cout << endl;
	}
	cout << endl << endl;
	/*eg. Taking position E4, we get 55 from the 120 positions board and then get
	 *	  25 in the 64 positions board. If E4 is set, then it will have 1 in its position.
	 *	  Performing bitwise & will yield true for that position and hence print X for the same.
	 */

}