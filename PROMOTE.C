//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Promote User Query Dialog (Promote.c)
//
//   Porter:    Ported to Windows 3.0 by Darly Baker
//
//   Porter:    Ported to OS/2 1.2+ by Kent Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  Remarks:    This code converted from Windows to PM using a straight port
//              method with some editing improvements.
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
#include <string.h>
#include "PmChess.h"
#include "GnuChess.h"
#include "Resource.h"


//
//  Define dialog procedure's prototypes.
//
MRESULT EXPENTRY PromoteProc(HWND hWnd, USHORT msg, MPARAM mp1, MPARAM mp2);


//***************************************************************************
//
//  Routine: PromoteDialog(In)
//
//  Remarks: This routine displays a dialog that queries the user of which
//           type of piece to promote a pawn.
//
//  Returns: The piece selected.
//
SHORT PromoteDialog(HWND hWnd)
  {
  SHORT status;


  status = (INT)(LONG)WinDlgBox(HWND_DESKTOP, hWnd, PromoteProc, 0,
                                IDD_PROMOTE, NULL);

  return (status);
  }


//***************************************************************************
//
//  Routine: PromoteProc(In, In, In, In)
//
//  Remarks: This routine displays a dialog that queries the user of which
//           type of piece to promote a pawn.
//
//  Returns: Depends on the message.
//
MRESULT EXPENTRY PromoteProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
  {
  SHORT idItem;


  switch (msg)
    {
    case WM_INITDLG:
      WinSendDlgItemMsg(hDlg, IDC_PROMOTE_QUEEN, BM_SETCHECK, MPFROMSHORT(TRUE), NULL);
      return (FALSE);

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
        {
        case IDC_OK:
          idItem = (SHORT)(LONG)WinSendDlgItemMsg(hDlg, IDC_PROMOTE_QUEEN,
                                           BM_QUERYCHECKINDEX, NULL, NULL);
          switch (idItem)
            {
            case 0:
              idItem = knight;
              break;

            case 1:
              idItem = bishop;
              break;

            case 2:
              idItem = rook;
              break;

            default:
              idItem = queen;
              break;
            }

          WinDismissDlg(hDlg, idItem);
          break;

        case IDC_CANCEL:
          WinDismissDlg(hDlg, FALSE);
          break;
        }
      return (0);
    }

  return (WinDefDlgProc(hDlg, msg, mp1, mp2));
  }
