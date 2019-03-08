//program for interchanging numbers by xor operations
#include <assert.h>

//input is ptr to position for which they key is needed
U64 GeneratePoskKey(const S_BOARD *pos){
	int sq = 0;					
	U64 finalKey = 0;			//final key to be returned
	int piece = EMPTY;	

	//looping through the board and setting value of the piece as per its position
	for (sq = 0; sq < BRD_SQ_NUM; sq++){
		piece = pos->pieces[sq];
		if (piece != NO_SQ && piece != EMPTY){		//piece from the actual chessboard
			assert(piece >= wP && piece <= bK);		//asserting the piece from the white to black range
			finalKey ^= PieceKeys[piece][sq];		//generating from the PieceKey array by hashing
		}
	}

	if (pos->side == WHITE)			//if it is a white piece
		finalKey ^= SideKey;		//then hash in the side key

	if (pos->enPas != NO_SQ){		//if pawn moved two blocks in the previous square = En Passant pawn
		assert(pos->enPas >= 0 && pos->enPas < BRD_SQ_NUM);		//again checking that the piece is within the bounds
		finalKey ^= PieceKeys[EMPTY][pos->enPas];
	}

	assert(pos->castlePerm >= 0 && pos->castlePerm <= 15);		//checking the castling bits
	finalKey ^= CastleKeys[pos->castlePerm];

	return finalKey;
}