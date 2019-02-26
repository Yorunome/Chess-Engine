//initialization file
#include "Definitions.h"

int SQ120ToSQ64[BRD_SQ_NUM];
int SQ64ToSQ120[64];

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
}