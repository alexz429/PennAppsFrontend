// PennAppsFrontend.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "PennAppsFrontend.h"
#include <map>

#define IDC_MAIN_EDIT 101
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

static int frameWidth = 1400;
static int frameHeight = 750;
int optionYOffset = 120;
static std::map<LPCWSTR, COLORREF> colourScheme;
static LPCWSTR defaultFontType = L"Segoe UI";


HWND parentWindow;
HWND titleBox;

void initColourScheme() {
	COLORREF lightBlue = 0xffa670;
	COLORREF midBlue = 0xf48642;
	COLORREF darkBlue = 0xfc271b;
	COLORREF midCharcoal = 0x3d3d3d;
	COLORREF darkCharcoal = 0x262626;
	COLORREF accentGold = 0x49f2ff;
	COLORREF white = 0xf2f2f2;

	colourScheme.insert(std::pair<LPCWSTR, COLORREF>(L"lightBlue", lightBlue));
	colourScheme.insert(std::pair<LPCWSTR, COLORREF>(L"midBlue", midBlue));
	colourScheme.insert(std::pair<LPCWSTR, COLORREF>(L"darkBlue", darkBlue));
	colourScheme.insert(std::pair<LPCWSTR, COLORREF>(L"midCharcoal", midCharcoal));
	colourScheme.insert(std::pair<LPCWSTR, COLORREF>(L"darkCharcoal", darkCharcoal));
	colourScheme.insert(std::pair<LPCWSTR, COLORREF>(L"accentGold", accentGold));
	colourScheme.insert(std::pair<LPCWSTR, COLORREF>(L"bg", darkCharcoal));
	colourScheme.insert(std::pair<LPCWSTR, COLORREF>(L"white", white));
}

HFONT getFont(LPCWSTR fontChoice) {
	return CreateFont(-17, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, fontChoice);
}

void setFont(HWND hw, LPCWSTR fontChoice) {
	SendMessage(hw, WM_SETFONT, (WPARAM)getFont(fontChoice), TRUE);
}

HWND createTitleBox() {
	int x = 300;
	int y = 65 + optionYOffset;
	int w = 250;
	int h = 30;

	HWND hw = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", L"",
		WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
		x, y, w, h, parentWindow, (HMENU)IDC_MAIN_EDIT, GetModuleHandle(NULL), NULL);
	setFont(hw, defaultFontType);
	return hw;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	parentWindow = CreateWindow(
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		frameWidth, frameHeight,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	initColourScheme();
	titleBox = createTitleBox();
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PENNAPPSFRONTEND, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PENNAPPSFRONTEND));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PENNAPPSFRONTEND));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)CreateSolidBrush(colourScheme.at(L"bg"));
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PENNAPPSFRONTEND);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
