//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Playing Board Display (Board.c)
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
#include "Defs.h"


/* All units defined in pixels */

#define BRD_HORZFRONT   48
#define BRD_HORZBACK    32
#define BRD_VERT        32
#define BRD_EDGE        8
#define BRD_HORZMARGIN  32
#define BRD_BACKMARGIN  5
#define BRD_FRONTMARGIN 5

static LONG DrawOneSquare ( HPS hPS, short x, short y);
static int HilitSq;

void QueryBoardSize ( POINTL *pptl )
{
   pptl->x = 2*BRD_HORZMARGIN + 8*BRD_HORZFRONT;
   pptl->y = BRD_BACKMARGIN + 8*BRD_VERT + 2*BRD_FRONTMARGIN + 2*BRD_EDGE;
}

void QuerySqSize ( POINTL *pptl ) {
   pptl->x = BRD_HORZFRONT;
   pptl->y = BRD_VERT;
}

void QuerySqOrigin ( short x, short y, POINTL *pptl)
{
   pptl->x = BRD_HORZMARGIN + y * (BRD_HORZFRONT-BRD_HORZBACK)/2 +
             x * (y*BRD_HORZBACK + (8-y)*BRD_HORZFRONT)/8;
   pptl->y = (BRD_BACKMARGIN+8*BRD_VERT+BRD_FRONTMARGIN)  - y*BRD_VERT;

   pptl->y = cyClient - pptl->y;
}

void QuerySqCoords ( short x, short y, POINTL aptl[] )
{
   QuerySqOrigin ( x,  y,  aptl+0);
   QuerySqOrigin ( x+1,y,  aptl+1);
   QuerySqOrigin ( x+1,y+1,aptl+2);
   QuerySqOrigin ( x,  y+1,aptl+3);
}

static LONG DrawOneSquare(HPS hps, short x, short y)
  {
  POINTL     aptl[4] ;


  GpiBeginArea (hps, BA_ALTERNATE | BA_BOUNDARY) ;

  QuerySqCoords (x, y, aptl) ;

  GpiMove (hps, aptl + 3) ;
  GpiPolyLine (hps, 4L, aptl) ;
  return (GpiEndArea (hps));
  }


/*
   Draw the board.  Pass the routine the upper left connor and the
   colors to draw the squares.
*/

void Draw_Board(HPS hps, int reverse, ULONG DarkColor, ULONG LightColor)
  {
  AREABUNDLE abnd ;
  LINEBUNDLE lbnd ;
  POINTL     aptl[32];
  int x, y;


  GpiSavePS(hps) ;

  lbnd.lColor = CLR_BLACK ;
  GpiSetAttrs(hps, PRIM_LINE, LBB_COLOR, 0L, &lbnd);

  for (y=0; y<8; y++) {
    for (x=0; x<8; x++) {
      if ( reverse == 0 ) {
        abnd.lColor = (x + y) & 1 ? LightColor : DarkColor;
        GpiSetAttrs (hps, PRIM_AREA, LBB_COLOR, 0L, &abnd) ;
        DrawOneSquare (hps, x, y);
      } else {
        abnd.lColor = ((7-x) + (7-y)) & 1 ? LightColor : DarkColor;
        GpiSetAttrs (hps, PRIM_AREA, LBB_COLOR, 0L, &abnd) ;
        DrawOneSquare(hps, 7-x, 7-y);
      }
    }

  GpiRestorePS(hps, 1);
  }

/* Now draw the bottom edge of the board */

   for (x=0; x<8; x++) {
      QuerySqCoords ( x,0, aptl);

      aptl[2].x = aptl[1].x;
      aptl[2].y = aptl[1].y - BRD_EDGE;

      aptl[3].x = aptl[0].x;
      aptl[3].y = aptl[0].y - BRD_EDGE;

      abnd.lColor = (x & 1) ? LightColor : DarkColor;
      GpiSetAttrs (hps, PRIM_AREA, LBB_COLOR, 0L, &abnd) ;

      GpiBeginArea (hps, BA_ALTERNATE | BA_BOUNDARY) ;

      GpiMove (hps, aptl + 3) ;
      GpiPolyLine(hps, 4L, aptl) ;
      GpiEndArea(hps) ;
   }

  GpiRestorePS (hps, -1L) ;
  }


void DrawCoords(HPS hps, int reverse, ULONG clrBackGround, ULONG clrText)
  {
  short  xchar, ychar;
  FONTMETRICS fm;
  POINTL ptl;
  short  i;


  //
  //  Load the diamensions of the default system font.
  //
  GpiQueryFontMetrics(hps, sizeof(fm), &fm);
  xchar = (SHORT)fm.lEmInc;
  ychar = (SHORT)fm.lMaxBaselineExt+(SHORT)fm.lExternalLeading;


  GpiSetColor(hps, clrText);
  GpiSetBackColor(hps, clrBackGround);

   for ( i=0; i<8; i++) {
      QuerySqOrigin (0, i, &ptl);
      ptl.x -= xchar;
      ptl.y -= BRD_VERT/2 - ychar * 2; // -ychar/2;
      GpiCharStringAt(hps, &ptl, 1,
         (PCHAR)(reverse ? "87654321"+i : "12345678"+i));
      
      QuerySqOrigin (i,0, &ptl);
      ptl.x += BRD_HORZFRONT/2-xchar/2;
      ptl.y -= BRD_EDGE + ychar;
      GpiCharStringAt(hps, &ptl, 1,
         (PCHAR)(reverse ? "hgfedcba"+i : "abcdefgh"+i));
   }
  }


void DrawWindowBackGround(HPS hps, HWND hWnd, ULONG bkcolor)
  {
  RECTL rcl ;

  WinQueryWindowRect(hWnd, &rcl) ;
  WinFillRect(hps, &rcl, bkcolor);
  }


void HiliteSquare(HWND hWnd, int Square)
  {
  HPS hps;
  short x, y;


  hps = WinGetPS(hWnd);

  y = Square / 8;
  x = Square % 8;

  GpiSetMix(hps, FM_INVERT);

  DrawOneSquare(hps, x, y);

  WinReleasePS(hps);

  HilitSq = Square;
  }

void UnHiliteSquare(HWND hWnd, int Square)
  {
  HPS hps;
  short x, y;


  if (HilitSq == -1)
    return;

  hps = WinGetPS(hWnd);

  y = Square / 8;
  x = Square % 8;

  GpiSetMix(hps, FM_INVERT);

  DrawOneSquare(hps, x, y);

  WinReleasePS(hps);

  HilitSq = -1;
  }


     /*---------------------------------------------------------------
        CkdQueryHitCoords: Obtains coords from mouse pointer position
       ---------------------------------------------------------------*/

VOID CkdQueryHitCoords (HPS hps, PPOINTL ptlMouse, SHORT *px, SHORT *py)
     {
     SIZEL sizlAperture;


     sizlAperture.cx = 1 ;
     sizlAperture.cy = 1 ;
     GpiSetPickApertureSize (hps, PICKAP_REC, &sizlAperture) ;

     GpiSetPickAperturePosition (hps, ptlMouse) ;

     GpiSetDrawControl (hps, DCTL_DISPLAY,   DCTL_OFF) ;
     GpiSetDrawControl (hps, DCTL_CORRELATE, DCTL_ON) ;

     for (*py = 0; *py < 8; (*py)++)
        {
        for (*px = 0; *px < 8; (*px)++)
          {
          if (DrawOneSquare(hps, *px, *py) == GPI_HITS)
            goto Done;
          }
        }

     *px = -1;
     *py = -1;

Done:
     GpiSetDrawControl (hps, DCTL_DISPLAY,   DCTL_ON) ;
     GpiSetDrawControl (hps, DCTL_CORRELATE, DCTL_OFF) ;
     }
