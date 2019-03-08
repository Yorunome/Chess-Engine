#include <cstdio>
#include "Definitions.h"

//for resetting the board, removing all pieces
void ResetBoard(S_BOARD *pos){
	//setting all the 120 positions as offboard
	for (int index = 0; index < BRD_SQ_NUM; index++)
		pos->pieces[index] = OFFBOARD;

	//setting the inside positions as empty 
	for (int index = 0; index < 64; index++)
		pos->pieces[SQ120(index)] = EMPTY;

	//resetting all the piece values as 0
	for (int index = 0; index < 3; index++) {
		pos->bigPiece[index] = 0;
		pos->majorPiece[index] = 0;
		pos->minorPiece[index] = 0;
		pos->pawns[index] = 0ULL;		//for the pawn data type
	}

	//setting the piece no. by piece type as 0
	for (int index = 0; index < 13; index++)
		pos->posNum[index] = 0;

	//setting both kings to no square
	pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

	//to clear assert false flags after resetting
	pos->side = BOTH;
	pos->enPas = NO_SQ;
	pos->fiftyMove = 0;

	pos->ply = 0;
	pos->hisPly = 0;

	pos->castlePerm = 0;

	pos->posKey = 0ULL;
}