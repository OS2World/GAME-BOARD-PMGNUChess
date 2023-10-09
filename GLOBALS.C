//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Main Module (PmChess.c)
//
//   Porter:    Ported to Windows 3.0 by Darly Baker
//
//   Porter:    Ported to OS/2 1.2+ by Kent Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  Remarks:    This code converted to OS/2 almost as is.  Mostly minor changes
//              to remove Windows code not required under OS/2.
//
//  License:
//
//    CHESS is distributed in the hope that it will be useful, but WITHOUT ANY
//    WARRANTY.  No author or distributor accepts responsibility to anyone for
//    the consequences of using it or for whether it serves any particular
//    purpose or works at all, unless he says so in writing.  Refer to the
//    CHESS General Public License for full details.
//
//    Everyone is granted permission to copy, modify and redistribute CHESS,
//    but only under the conditions described in the CHESS General Public
//    License.  A copy of this license is supposed to have been given to you
//    along with CHESS so you can know your rights and responsibilities.  It
//    should be in a file named COPYING.  Among other things, the copyright
//    notice and this notice must be preserved on all copies.
//

#define INCL_DOS
#include <os2.h>
#include <stdio.h>
#include "GnuChess.h"


#if ttblsz
unsigned long hashkey, hashbd;
struct hashval far hashcode[2][7][64];

#ifdef M_I386
struct hashentry ttable[2][ttblsz];
#else
struct hashentry far ttable[2][ttblsz];
#endif

#endif /* ttblsz */

FILE *hashfile;
struct leaf far Tree[2000], far *root;

short TrPnt[maxdepth];
short PieceList[2][16], PawnCnt[2][8];
#define wking PieceList[white][0]
#define bking PieceList[black][0]
#define EnemyKing PieceList[c2][0]
short castld[2], Mvboard[64];
short svalue[64];
struct flags flag;
short opponent, computer, Awindow, Bwindow, dither, INCscore;
long ResponseTime, ExtraTime, Level, et, et0, time0, ft;
long NodeCnt, ETnodes, EvalNodes, HashCnt, FHashCnt, HashCol;
short player, xwndw, rehash;

struct GameRec far GameList[512];

short Sdepth, GameCnt, Game50, MaxSearchDepth;
short epsquare, contempt;
struct BookEntry *Book;
struct TimeControlRec TimeControl;
short TCflag, TCmoves, TCminutes, OperatorTime;
unsigned short hint, PrVar[maxdepth];
short Pindex[64];
short PieceCnt[2];
short c1, c2, *atk1, *atk2, *PC1, *PC2, atak[2][64];
short mtl[2], pmtl[2], emtl[2], hung[2];
short FROMsquare, TOsquare, Zscore, zwndw;
short HasKnight[2], HasBishop[2], HasRook[2], HasQueen[2];
short ChkFlag[maxdepth], CptrFlag[maxdepth], PawnThreat[maxdepth];
short Pscore[maxdepth], Tscore[maxdepth];
unsigned short killr0[maxdepth], killr1[maxdepth];
unsigned short killr2[maxdepth], killr3[maxdepth];
unsigned short PV, Swag0, Swag1, Swag2, Swag3, Swag4;
unsigned char far history[8192];

short rpthash[2][256];
short Mwpawn[64], Mbpawn[64], Mknight[2][64], Mbishop[2][64];
short Mking[2][64], Kfield[2][64];
short KNIGHTPOST, KNIGHTSTRONG, BISHOPSTRONG, KATAK;
short PEDRNK2B, PWEAKH, PADVNCM, PADVNCI, PAWNSHIELD, PDOUBLED, PBLOK;
short RHOPN, RHOPNX, KHOPN, KHOPNX, KSFTY;
short ATAKD, HUNGP, HUNGX, KCASTLD, KMOVD, XRAY, PINVAL;
short stage, stage2, Developed[2];
short PawnBonus, BishopBonus, RookBonus;

short far distdata[64][64], far taxidata[64][64];

short board[64], color[64];
unsigned char far nextpos[8][64][64];
unsigned char far nextdir[8][64][64];


short otherside[3] = {1, 0, 2};

#if ttblsz
#if HASHFILE
/*
  In a networked enviroment gnuchess might be compiled on different
  hosts with different random number generators, that is not acceptable
  if they are going to share the same transposition table.
*/
static unsigned long int next = 1;

unsigned int urand (void)
{
  next *= 1103515245;
  next += 12345;
  return ((unsigned int) (next >> 16) & 0xFFFF);
}

void srand (unsigned int seed)
{
  next = seed;
}
#endif /*HASHFILE*/
#endif /*ttblsz*/

HWND hComputerColor;
HWND hComputerMove;
HWND hWhosTurn;
HWND hClockComputer;
HWND hClockHuman;
HWND hMsgComputer;
HWND hMsgHuman;
HWND hStats;
