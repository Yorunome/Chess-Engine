//initialization file
#include "Definitions.h"
#include "bitboard.cpp"
#include "HashKey.cpp"
#include "board.cpp"
#include <cstdlib>

//filling 64 bits with random numbers
//rand() generates a 15 bit random number
/* line 0: 0000 000000000000000 000000000000000 000000000000000 000000000000000 
 * line 1: 0000 000000000000000 000000000000000 000000000000000 001111001111010 (random no. generated)
 * line 2: 0000 000000000000000 000000000000000 001111001111010 000000000000000	(shifted by 15 bits)
 * line 3: 0000 000000000000000 001111001111010 000000000000000 000000000000000	(shifted by 30 bits)
 * line 4: 0000 001111001111010 000000000000000 000000000000000 000000000000000	(shifted by 45 bits)
 * line 5: 0011 000000000000000 000000000000000 000000000000000 000000000000000 (taking the four bits of the rn and then shifting by 60)
 */
#define RAND_64 (	(U64)rand + \
					(U64)rand << 15 + \
					(U64)rand << 30 + \
					(U64)rand << 45 + \
					((U64)rand & 0xf) << 60 )

int SQ120ToSQ64[BRD_SQ_NUM];
int SQ64ToSQ120[64];

U64 SetMask[64];
U64 ClearMask[64];

U64 PieceKeys[13][120];		//13 is for indexing pieces, 120 is for indexing board positions
U64 SideKey;				//just one random number for the side positions
U64 CastleKeys[16];			//for castling positions

//function for initializing the piece keys with random 64 bit numbers
void InitHashKeys(){
	for (int index_1 = 0; index_1 < 13; index_1++)
		for (int index_2 = 0; index_2 < 120; index_2++)
			PieceKeys[index_1][index_2] = RAND_64;
	SideKey = RAND_64;
	for (int index = 0; index < 16; index++)
		CastleKeys[index] = RAND_64;
}

void InitBitMask(){
	/*for (int index = 0; index < 64; index++) {
		SetMask[index] = 0ULL;
		ClearMask[index] = 0ULL;
	}*/
	for (int index = 0; index < 64; index++){
		SetMask[index] |= (1ULL << index);
		ClearMask[index] = ~SetMask[index];
	}
}

//for initializing the SQ120toSQ64 array
void InitSQ120To64(){
	int index = 0;
	int file = FILE_A;
	int rank = RANK_1;
	int sq = A1;
	int sq64 = 0;
	
	//since 65 should not be returned
	for (index = 0; index < 64; index++)
		SQ64ToSQ120[index] = 120;
	//since 120 should not be returned
	for (index = 0; index < BRD_SQ_NUM; index++)
		SQ120ToSQ64[index] = 65;

	//
	for (rank = RANK_1; rank <= RANK_8; rank++){
		for (file = FILE_A; file <=FILE_H; file++){
			sq = FR2SQ(file, rank);			//getting the square at that index
			SQ64ToSQ120[sq64] = sq;			//setting the value in the bigger board
			SQ120ToSQ64[sq] = sq64;			//setting the value in smaller board
			sq64++;							//moving one position in the smaller board
		}
	}
}

void AllInit(){
	InitSQ120To64();
	InitBitMask();
	InitHashKeys();
}