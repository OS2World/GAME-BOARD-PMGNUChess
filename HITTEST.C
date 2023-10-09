//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Color Support Logic (Color.c)
//
//   Porter:    Ported to Windows 3.0 by Darly Baker
//
//   Porter:    Ported to OS/2 1.2+ by Kent Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  Remarks:    This code converted from Windows to PM using a straight port
//              method with some editing improvements.  Based on ideas and
//              code segments of Charles Petzold from artices in Microsoft
//              Systems Journal.
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
#include <OS2.h>
#include <Stdio.h>
#include "PmChess.h"
#include "Defs.h"



static int deltay;
static HRGN hitrgn[8];

void InitHitTest ( void )
  {
  POINTL ptls[4];
  POINTL toppt, botpt;
  int i;


   for (i=0; i<8; i++) {
      QuerySqOrigin ( i, 0, ptls+0 );
      //QuerySqOrigin ( i, 8, ptls+1 );
      QuerySqOrigin ( i+1, 8, ptls+1 );
      //QuerySqOrigin ( i+1, 0, ptls+3 );
      hitrgn[i] = GpiCreateRegion(hpsClient, 1, (PRECTL)ptls);
   }
      QuerySqOrigin ( 0, 0, &botpt );
      QuerySqOrigin ( 0, 8, &toppt );
      deltay = botpt.y-toppt.y;
 }

void Hittest_Destructor (VOID)
{
   int i;
   for (i=0; i<8; i++)
      GpiDestroyRegion(hpsClient, hitrgn[i] );
}

static int HorzHitTest ( int x, int y)
{
   POINTL ptl;
   int i;

   for ( i=0; i<8; i++) {
      ptl.x = x;
      ptl.y = y;
      if ( GpiPtInRegion (hpsClient, hitrgn[i], &ptl) ) return i;
   }
   return -1;
}

int HitTest ( int x, int y)
{
   int xsq, ysq;
   POINTL sq00;

   xsq = HorzHitTest ( x, y );
   if (xsq==-1) return -1;

   QuerySqOrigin ( 0,0, &sq00);

   if ( y > sq00.y ) return -1;
   if ( y < (sq00.y-deltay) ) return -1;

   ysq = 7 - (y - (sq00.y-deltay) ) / (deltay/8);
   return ( ysq*8 + xsq );
}
