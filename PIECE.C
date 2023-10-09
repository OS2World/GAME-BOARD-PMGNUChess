//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Piece Display (Piece.c)
//
//   Porter:    Ported to Windows 3.0 by Darly Baker
//
//   Porter:    Ported to OS/2 1.2+ by Kent Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  Remarks:    This code is based on Ideas and code segments of Charles
//              Petzold from artices in Micrsoft Systems Journal.  This code
//              is mostly just editing changes to convert to PM.
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
#define INCL_PM
#include <os2.h>
#include <stdio.h>
#include "PmChess.h"
#include "GnuChess.h"
#include "Defs.h"
#include "Resource.h"


//
//  Define local variables.
//
static USHORT cxBitmap, cyBitmap;           // Size of the chess piece bitmap.


#define PIECE_XAXIS 32
#define PIECE_YAXIS 32


static void  QuerySqCenter (short x, short y, POINTL *pptl);
static short ConvertCoordToIndex ( short x, short y);
static void  PieceOriginFromCenter ( POINTL *pptl);
static void  QuerySqPieceOrigin ( short x, short y, POINTL *pptl);
static void  DrawOnePiece ( HPS hps, HPS hpsPieces, short x, short y, short piece, ULONG color);
static void  ShowPiece(HPS hps, HPS hpsPieces, POINTL *pptl, short piece,
                  ULONG Color );


//***************************************************************************
//
//  Routine: LoadChessPieces(In):Original Code by Kent Cedola
//
//  Remarks: This routine is called during the initialization process to load
//           the bitmaps used to draw the various chess pieces into a memory
//           presentation space.  This permits us to use fast GpiBitBlt's
//           without the overhead of moving each bitmap into a memory ps.
//
//  Returns: Handle of memory presentation space.
//
HPS LoadChessPieces(HAB hab)
  {
  HDC     hdc, hdcTemp;
  HPS     hps, hpsTemp;
  HBITMAP hbm;

#ifdef M_I386
  BITMAPINFOHEADER2 bmp;
#else
  BITMAPINFOHEADER bmp;
#endif

  POINTL  aptl[3];
  SIZEL   sizel;
  SHORT   row, col;


  //
  //  Allocate a tempoary presentation space (just for loading bitmaps).
  //
  hdcTemp  = DevOpenDC(hab, OD_MEMORY, "*", 0L, NULL, NULL);
  sizel.cx = 0L;
  sizel.cy = 0L;
  hpsTemp  = GpiCreatePS(hab, hdcTemp, &sizel,
                         PU_PELS | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC);

  //
  //  Load and release a bitmap piece to determine the size of it.  Thus we
  //  will know how big to create the monochrome bitmap to hold them all.
  //
  hbm = GpiLoadBitmap(hpsTemp, 0, IDB_PAWNBASE + 1, 0, 0);
  bmp.cbFix = sizeof(bmp);

#ifdef M_I386
  GpiQueryBitmapInfoHeader(hbm, &bmp);
#else
  GpiQueryBitmapParameters(hbm, &bmp);
#endif

  cxBitmap = bmp.cx;
  cyBitmap = bmp.cy;

  GpiDeleteBitmap(hbm);

  //
  //  Allocate memory presentation space.
  //
  hdc = DevOpenDC(hab, OD_MEMORY, "*", 0L, NULL, NULL);
  sizel.cx = 0L;
  sizel.cy = 0L;
  hps = GpiCreatePS(hab, hdc, &sizel,
                    PU_PELS | GPIF_DEFAULT | GPIT_MICRO | GPIA_ASSOC);

  //
  //  Create the master bitmap that will contain all other bitmaps.
  //
  bmp.cbFix     = sizeof(bmp);
  bmp.cx        = cxBitmap * 6;
  bmp.cy        = cyBitmap * 3;
  bmp.cPlanes   = 1;
  bmp.cBitCount = 1;

  hbm = GpiCreateBitmap(hps, &bmp, 0, 0, 0);
  GpiSetBitmap(hps, hbm);

  //
  //  Load each bitmap and copy over to the pieces memory presentation space.
  //
  aptl[2].x = 0;
  aptl[2].y = 0;
  for (row = 0; row < 3; row++)
    {
    for (col = pawn; col <= king; col++)
      {
      hbm = GpiLoadBitmap(hpsTemp, 0, IDB_PAWNBASE + row * king + col, 0, 0);

      GpiSetBitmap(hpsTemp, hbm);

      aptl[0].x = cxBitmap * (col - 1);
      aptl[0].y = cyBitmap * row;
      aptl[1].x = aptl[0].x + cxBitmap;
      aptl[1].y = aptl[0].y + cyBitmap;

      GpiBitBlt(hps, hpsTemp, 3, aptl, ROP_SRCCOPY, 0);

      GpiSetBitmap(hpsTemp, NULL);
      GpiDeleteBitmap(hbm);
      }
    }

  //
  //  Free the tempoary memory presentation space.
  //
  GpiDestroyPS(hpsTemp);
  DevCloseDC(hdcTemp);

  return (hps);
  }


static void QuerySqCenter ( short x, short y, POINTL *pptl)
{
   POINTL aptl[4];

   QuerySqCoords ( x, y, aptl );

   pptl->x = (aptl[0].x + aptl[1].x + aptl[2].x + aptl[3].x)/4;
   pptl->y = (aptl[0].y + aptl[2].y)/2;
}


static void PieceOriginFromCenter ( POINTL *pptl)
{
   pptl->x -= PIECE_XAXIS / 2;
   pptl->y -= PIECE_YAXIS / 2;
}

static void QuerySqPieceOrigin ( short x, short y, POINTL *pptl)
{
      QuerySqCenter ( x, y, pptl);
      PieceOriginFromCenter (pptl);
}


/*
   Draw a piece in the specificed point

   Piece_bitmap is a structure with the handles for the mask,
   outline and piece.

*/

static void ShowPiece(HPS hps, HPS hpsPieces, POINTL *pptl, short piece,
                      ULONG Color)
  {
  POINTL aptl[3];


  //
  //  Setup the destination to write out the chess piece.
  //
  aptl[0].x = pptl->x;
  aptl[0].y = pptl->y;
  aptl[1].x = pptl->x + cxBitmap;
  aptl[1].y = pptl->y + cyBitmap;

  //
  //  Select the bitmap for the specified chess piece.
  //
  aptl[2].x = (piece - 1) * cxBitmap;

  //
  //  Mask out the space so we can store a multi-color chess piece.
  //
  aptl[2].y = 0;
  GpiSetColor(hps, CLR_WHITE);
  GpiSetBackColor(hps, CLR_BLACK);
  GpiBitBlt(hps, hpsPieces, 3, aptl, ROP_SRCAND, 0);

  //
  //  Fill in the piece's color.
  //
  aptl[2].y = 32;
  GpiSetColor(hps, CLR_BLACK);
  GpiSetBackColor(hps, Color);
  GpiBitBlt(hps, hpsPieces, 3, aptl, ROP_SRCPAINT, 0);

  //
  //  Draw the piece's outline.
  //
  aptl[2].y = 64;
  GpiSetColor(hps, CLR_WHITE);
  GpiSetBackColor(hps, CLR_BLACK);
  GpiBitBlt(hps, hpsPieces, 3, aptl, ROP_SRCAND, 0);
  }


static short ConvertCoordToIndex ( short x, short y)
{
   return (y*8 + x );
}

static void DrawOnePiece(HPS hps, HPS hpsPieces, short x, short y, short piece, ULONG color)
  {
  POINTL origin;


  QuerySqPieceOrigin(x, y, &origin);
  ShowPiece (hps, hpsPieces, &origin, piece, color);
  }



void DrawAllPieces(HPS hps, HPS hpsPieces, short reverse, short *pbrd, short *color,
                     ULONG clrblack, ULONG clrwhite )
  {
  short x,y;
  short i;


  for ( y=0; y<8; y++)
    {
    for (x=0; x<8; x++)
      {
      i = ConvertCoordToIndex(x, y);

      if ( *(color+i) != NETURAL)
        {
        if (reverse == 0)
          DrawOnePiece(hps, hpsPieces, x, y, *(pbrd+i), (*(color+i)==BLACK) ? clrblack : clrwhite );
        else
          DrawOnePiece(hps, hpsPieces, 7-x, 7-y, *(pbrd+i), (*(color+i)==BLACK) ? clrblack : clrwhite );
        }
      }
    }
  }
