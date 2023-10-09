//
//  Copyright (C) 1986, 1987, 1988, 1989, 1990 Free Software Foundation, Inc.
//  Copyright (C) 1988, 1989, 1990  John Stanback
//
//  Project:    OS/2 PM Port of GNU CHESS 3.1 (PmChess)
//
//  Version:    1990-11-17
//
//  Include:    Header file for the GNU Chess Interface Logic (Defs.h)
//
//   Porter:    Ported to Windows 3.0 by Darly Baker
//
//   Porter:    Ported to OS/2 1.2+ by Kent Cedola
//
//   System:    OS2 1.2 using Microsoft C 6.0
//
//  Remarks:    Editing changes to convert Windows code to OS/2 PM.
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

extern int parse (FILE * fd, short unsigned int *mv, short int side);
extern void GetOpenings (HWND hWnd);
extern void OpeningBook (unsigned short int *hint);
extern void repetition (short int *cnt);
extern void SelectMove (HWND hWnd, short int side, short int iop);
extern int search (short int side,
		   short int ply,
		   short int depth,
		   short int alpha,
		   short int beta,
		   short unsigned int *bstline,
		   short int *rpt);
#if ttblsz
extern int ProbeTTable (short int side,
			short int depth,
			short int *alpha,
			short int *beta,
			short int *score);
extern void PutInTTable (short int side,
			 short int score,
			 short int depth,
			 short int alpha,
			 short int beta,
			 short unsigned int mv);
extern void ZeroTTable (void);
extern void ZeroRPT (void);
#ifdef HASHFILE
extern int ProbeFTable (short int side,
			short int depth,
			short int *alpha,
			short int *beta,
			short int *score);
extern void PutInFTable (short int side,
			 short int score,
			 short int depth,
			 short int alpha,
			 short int beta,
			 short unsigned int f,
			 short unsigned int t);
#endif /* HASHFILE */
#endif /* ttblsz */
extern void Initialize_moves (void);
extern void MoveList (short int side, short int ply);
extern void CaptureList (short int side, short int ply);
extern int castle (short int side, short int kf, short int kt, short int iop);
extern void MakeMove (short int side,
		      struct leaf far * node,
		      short int *tempb,
		      short int *tempc,
		      short int *tempsf,
		      short int *tempst,
		      short int *INCscore);
extern void UnmakeMove (short int side,
			struct leaf far * node,
			short int *tempb,
			short int *tempc,
			short int *tempsf,
			short int *tempst);
extern void InitializeStats (void);
extern int SqAtakd (short int sq, short int side);
extern int evaluate (short int side,
		     short int ply,
		     short int alpha,
		     short int beta,
		     short int INCscore,
		     short int *slk,
		     short int *InChk);
extern void ScoreLoneKing (short int side, short int *score);
extern void ScorePosition (short int side, short int *score);
extern void ExaminePosition (void);
extern void UpdateWeights (void);

extern void Initialize (void);
extern void InputCommand (void);
extern void ExitChess (void);
extern void ClrScreen (void);
extern void SetTimeControl (void);
extern void SelectLevel (void);
extern void UpdateDisplay (HWND hWnd, short int f,
			   short int t,
			   short int flag,
			   short int iscastle);
extern void ElapsedTime (short int iop);
extern void ShowSidetoMove(void);
extern void SearchStartStuff (short int side);
extern void ShowDepth (char ch);
extern void ShowResults (short int score,
			 short unsigned int *bstline, char ch);
extern void algbr (short int f, short int t, short int flag);
extern void OutputMove (HWND hWnd);
extern void ShowCurrentMove (short int pnt, short int f, short int t);
extern void ShowMessage (HWND hWnd, PSZ pszText);
extern void ClrScreen (void);
extern void gotoXY (short int x, short int y);
extern void ClrEoln (void);
extern void DrawPiece (HWND hWnd, short int sq);
extern void UpdateClocks (void);
extern void ataks (short int side, short int *a);
extern void ListGame (HWND hWnd, char *fname);
extern void NewGame (HWND hWnd);

extern void QuerySqSize ( POINTL *pptl ) ;
extern void QueryBoardSize ( POINTL *pptl );
extern void QuerySqOrigin ( short x, short y, POINTL *pptl);
extern void QuerySqCoords ( short x, short y, POINTL aptl[] );
extern void Draw_Board (HPS hps, int reverse,
                  ULONG DarkColor, ULONG LightColor );
extern HPS  LoadChessPieces(HAB hab);
extern void DrawAllPieces (HPS hps, HPS hpsPieces, short reverse, short *pbrd,
                           short *color, ULONG xblack, ULONG xwhite);
extern void DrawWindowBackGround ( HDC hDC, HWND hWnd, ULONG bkcolor);
extern BOOL ChessInit (INT hInstance);
VOID CkdQueryHitCoords (HPS hps, PPOINTL ptlMouse, SHORT *px, SHORT *py);
extern void HiliteSquare ( HWND hWnd, int Square);
extern void UnHiliteSquare ( HWND hWnd, int Square);
extern void Hittest_Destructor ( VOID);
extern void SetStandardColors ( VOID );
extern void SaveColors ( PCHAR appname );
extern void GetStartupColors ( PCHAR appname );
extern int ColorDialog ( HWND hWnd, ULONG Param );
extern int TimeControlDialog(HWND hWnd);
extern void Create_Children ( HWND hWnd, short xchar, short ychar);
extern int ReviewDialog ( HWND hWnd, INT hInst);
extern void SaveGame (HWND hWnd, char *fname);
extern void GetGame (HWND hWnd, char *fname);
extern void Undo (HWND hWnd);
extern void GiveHint (HWND hWnd);
extern int VerifyMove (HWND hWnd, char *s, short int iop, short unsigned int *mv);
extern int init_main (HWND hWnd);
extern void ShowSidetoMove (void);
extern BOOL About(HWND, unsigned, USHORT, LONG);
extern long ChessWndProc( HWND hWnd, unsigned message, USHORT wParam, LONG lParam);
extern void Init_Menus (HWND hWnd, MPARAM mp1, MPARAM mp2);
extern void FreeBook (void);
extern void DrawCoords ( HDC hDC, int reverse, ULONG clrBackGround, ULONG clrText);
extern void TestDialog ( HWND hWnd);
extern int  StatDialog ( HWND hWnd);
extern int  PromoteDialog ( HWND hWnd);
extern void pick (short int p1, short int p2);
extern void SMessageBox ( HWND hWnd, SHORT str_num, SHORT str1_num );
extern void ShowPlayers (void);
extern void FreeGlobals (void);
extern void algbr (short int f, short int t, short int flag);

extern int DoGetNumberDlg (HWND, char *, int);

extern char mvstr[4][6];
