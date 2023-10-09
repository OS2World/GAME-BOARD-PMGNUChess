//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (c) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//   Module:    Init/Update Menu Logic (MenuInit.c)
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

#define INCL_DOS
#define INCL_PM
#include <os2.h>
#include <string.h>
#include "PmChess.h"
#include "Resource.h"


static short NumberDlgInt;
static char  NumberDlgChar[80];

int DoGetNumberDlg (HWND hWnd, char * szPrompt, int def);

MRESULT EXPENTRY NumberProc(HWND hDlg, USHORT msg, MPARAM mp1, MPARAM mp2)
  {
  short temp, Ier;


  switch (msg)
    {
    case WM_INITDLG:
      WinSetDlgItemText(hDlg, IDC_NUMDLG_CHAR, NumberDlgChar);
      WinSetDlgItemShort(hDlg, IDC_NUMDLG_INT, NumberDlgInt, TRUE);
      return (FALSE);

    case WM_COMMAND:
      switch (SHORT1FROMMP(mp1))
        {
        case IDC_OK:
          if (WinQueryDlgItemShort(hDlg, IDC_NUMDLG_INT, &temp, TRUE))
            {
            NumberDlgInt = temp;
            WinDismissDlg(hDlg, TRUE);
            }
          break;

        case IDC_CANCEL:
          WinDismissDlg(hDlg, FALSE);
          break;
        }
      return (0);
    }

  return (WinDefDlgProc(hDlg, msg, mp1, mp2));
  }


int DoGetNumberDlg(HWND hWnd, char * szPrompt, int def)
{

   strcpy ( NumberDlgChar, szPrompt);
   NumberDlgInt = def;

   WinDlgBox(HWND_DESKTOP, hWnd, NumberProc, 0, IDD_NUMDLG, NULL);

   return NumberDlgInt;
}
