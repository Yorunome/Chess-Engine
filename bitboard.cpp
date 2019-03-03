#include <iostream>

using namespace std;

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