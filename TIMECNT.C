//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Time Setting Dialog Logic (TimeCnt.c)
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
#include "PmChess.h"
#include "Resource.h"


extern int TCmoves, TCminutes, TCflag;

//
//  Define dialog procedure's prototypes.
//
MRESULT EXPENTRY TimeProc(HWND hWnd, USHORT msg, MPARAM mp1, MPARAM mp2);



int TimeControlDialog(HWND hWnd)
  {
  int status;

  status = (int)(LONG)WinDlgBox(HWND_DESKTOP, hWnd, TimeProc, 0,
                                IDD_SKILL_TIME, NULL);

  return (status);
  }


MRESULT EXPENTRY TimeProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
  {
  register i;


  switch (msg)
    {
    case WM_INITDLG:
      if (TCminutes == 5)
        i = IDC_SKILL_T5;
      else if (TCminutes == 15)
        i = IDC_SKILL_T15;
      else if (TCminutes == 30)
        i = IDC_SKILL_T30;
      else if (TCminutes == 60)
        i = IDC_SKILL_T60;
      else
        i = IDC_SKILL_T600;

      WinSendDlgItemMsg(hDlg, i, BM_SETCHECK, MPFROMSHORT(TRUE), NULL);

      if (TCmoves == 1)
        i = IDC_SKILL_M1;
      else if (TCmoves == 10)
        i = IDC_SKILL_M10;
      else if (TCmoves == 20)
        i = IDC_SKILL_M20;
      else if (TCmoves == 40)
        i = IDC_SKILL_M40;
      else
        i = IDC_SKILL_M60;

      WinSendDlgItemMsg(hDlg, i, BM_SETCHECK, MPFROMSHORT(TRUE), NULL);
      return (FALSE);

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
        {
        case IDC_OK:
          i = (SHORT)(LONG)WinSendDlgItemMsg(hDlg, IDC_SKILL_T5,
                                             BM_QUERYCHECKINDEX, NULL, NULL);
          if (i == 0)
            TCminutes = 5;
          else if (i == 1)
            TCminutes = 15;
          else if (i == 2)
            TCminutes = 30;
          else if (i == 3)
            TCminutes = 60;
          else
            TCminutes = 600;

          i = (SHORT)(LONG)WinSendDlgItemMsg(hDlg, IDC_SKILL_M1,
                                             BM_QUERYCHECKINDEX, NULL, NULL);

          if (i == 0)
            TCmoves = 1;
          else if (i == 1)
            TCmoves = 10;
          else if (i == 2)
            TCmoves = 20;
          else if (i == 3)
            TCmoves = 40;
          else
            TCmoves = 60;

          WinDismissDlg(hDlg, TRUE);
          break;

        case IDC_CANCEL:
          WinDismissDlg(hDlg, FALSE);
          break;
        }
      return (0);
    }

  return (WinDefDlgProc(hDlg, msg, mp1, mp2));
  }
