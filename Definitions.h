//To protect against multiple includes during compiler linking programs

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <cstdlib>

//for file debugging
/*#define DEBUG

#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n)		\
if (!(n)){		\
printf("%s - Failed", #n);		\
printf("On %s ", __DATE__);		\
printf("On %s ", __TIME__);		\
printf("In File %s ", __FILE__);	\
printf("At Line %s ", __LINE__);	\
exit(1);
#endif
*/
typedef unsigned long long U64;			//for bitboard

#define NAME "Engine 1.0"
#define BRD_SQ_NUM 120					//total required positions of concern

#define MAXGAMEMOVES 2048				//maximum no. of moves to contain history of the game

//board pieces and positions definition

enum { EMPTY, wP, wN, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };								//board pieces
enum { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };		//horizontal positions
enum { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };		//vertical positions

enum { WHITE, BLACK, BOTH };		//colours

enum{
	A1 = 21, B1, C1, D1, E1, F1, G1, H1,
	A2 = 31, B2, C2, D2, E2, F2, G2, H2,
	A3 = 41, B3, C3, D3, E3, F3, G3, H3,
	A4 = 51, B4, C4, D4, E4, F4, G4, H4,
	A5 = 61, B5, C5, D5, E5, F5, G5, H5,
	A6 = 71, B6, C6, D6, E6, F6, G6, H6,
	A7 = 81, B7, C7, D7, E7, F7, G7, H7,
	A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};													//board positions

enum { FALSE, TRUE };								//constants for true/false

//castling information (eg. King goes from E1 to G1 and Rook goes from H1 to F1 for King Castling)
enum { WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8 };

//for storing game history that enables undo moves
typedef struct{
	int move;
	int castlePerm;
	int enPas;
	int fiftyMove;
	U64 posKey;
} S_UNDO;

typedef struct{
	int pieces[BRD_SQ_NUM];			//all required board and beyond positions
	U64 pawns[3];					//bit representation of the colours: 0 - white, 1 - black, 2 - both
	
	int KingSq[2];
	
	int side;				//current side to move
	int enPas;
	int fiftyMove;			//draw condition if no pieces are captured within 50 moves
	
	int ply;				//half moves in the game (goes up to 100)
	int hisPly;				//total no. of half moves in the game so far

	int castlePerm;			//possible castling permutations

	U64 posKey;				//unique key generated for each position

	int posNum[13];			//no. of pieces remaining on the board (from the enum)
	int bigPiece[3];		//pieces that are pawns (black, white and both)
	int majorPiece[3];		//rooks and queens
	int minorPiece[3];		//knights and bishops

	S_UNDO history[MAXGAMEMOVES];		//object for storing board history indexed by hisPly

	//piece list (for generating moves, based on colour), 
	//enhances search and move generation
	//10 is maximum possibility for a single piece type (eg. 2R + 8 Promoted Pawns)
	// eg. plist[wN][0] = E1  --- add white knight to position and 
	//keep generating positions until no square
	int pList[13][10];			
	


} S_BOARD;

//macro that returns a number based on the 120 positions array given the file and rank
#define FR2SQ(f, r) ( (21 + (f) ) + ( (r) * 10) ) 
//macro for shortening the array 
#define SQ64(sq120) SQ120ToSQ64[sq120]
//macro for the popping function
#define POP(b) popBit(b)
//macro for counting
#define cnt(b) countBits(b)
//macro for setting up and clearing the masks
#define setbit(bb, sq) ((bb) &= SetMask[(sq)])
#define clrbit(bb, sq) ((bb) |= ClearMask[(sq)])

//globals for deriving the piece position from the 120 bit board to 64 bit board and vice versa
extern int SQ120ToSQ64[BRD_SQ_NUM];
extern int SQ64ToSQ120[64];

//globals for setting and clearing positions on bitboard
extern U64 SetMask[64];
extern U64 ClearMask[64];


//initialization functions
extern void AllInit();

//bitboard functions
extern void printBitBoard(U64 bb);
extern int popBit(U64 *bb);
extern int countBits(U64 b);

#endif