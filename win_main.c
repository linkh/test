//#include <windows.h>
//#include <stdafx.h>
//#include <window_param.h>

#include "object.h"


Anim anim;
Map map;
Menu menu;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
ATOM RegMyWindowClass(HINSTANCE, LPCTSTR);




int APIENTRY WinMain(HINSTANCE hInstance,
             HINSTANCE         hPrevInstance,
             LPSTR             lpCmdLine,
             int               nCmdShow)
{

  LPCTSTR lpzClass = TEXT("mainWindowClass");

  if (!RegMyWindowClass(hInstance, lpzClass))
    return 1;

  RECT screen_rect;
  GetWindowRect(GetDesktopWindow(),&screen_rect);
  
  HWND hWnd = CreateWindow(lpzClass, TEXT("WINDOW_TITLE"), 
    WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, 
    hInstance, NULL);

  if(!hWnd) return 2; 

  MSG msg = {0};    
  int iGetOk = 0;   
  while ((iGetOk = GetMessage(&msg, NULL, 0, 0 )) != 0) 
  {
    if (iGetOk == -1) return 3;  
    TranslateMessage(&msg);    
    DispatchMessage(&msg);
  }

  return msg.wParam; 
}

ATOM RegMyWindowClass(HINSTANCE hInst, LPCTSTR lpzClassName)
{
  WNDCLASS wcWindowClass = {0};
  wcWindowClass.lpfnWndProc = (WNDPROC)WndProc;
  wcWindowClass.style = CS_HREDRAW|CS_VREDRAW;
  wcWindowClass.hInstance = hInst;
  wcWindowClass.lpszClassName = lpzClassName;
  wcWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);

  wcWindowClass.hbrBackground = (HBRUSH)COLOR_APPWORKSPACE;
  return RegisterClass(&wcWindowClass); 
}

LRESULT CALLBACK WndProc(
  HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hDc;
  HBITMAP hBmMem;
  HANDLE hOld;


  switch (message)
  {
  case WM_CREATE:
    break;
  case WM_LBUTTONUP:
    //xPos = GET_X_LPARAM(lParam); 
  //yPos = GET_Y_LPARAM(lParam); 
	//InvalidateRect(hWnd, NULL, 1);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);  
    break;
  case WM_SIZE:
	anim.w = LOWORD(lParam); 
	anim.h = HIWORD(lParam);
	InvalidateRect(hWnd, NULL, 1);
  case WM_PAINT:
	hDc = BeginPaint(hWnd, &ps);
    
	anim.hDc = CreateCompatibleDC(hDc);
    hBmMem = CreateCompatibleBitmap(hDc, anim.w, anim.h);
    hOld   = SelectObject(anim.hDc, hBmMem);

	Rectangle(anim.hDc, -1, -1, anim.w + 2, anim.h + 2);

	
	map.drawMap(anim, 0, MENU_SIZE);
	menu.draw(anim, 0, 0);
	//mrc.draw(hDcMem, xPos, yPos);

	BitBlt(hDc, 0, 0, anim.w, anim.h, anim.hDc, 0, 0, SRCCOPY);

	SelectObject(anim.hDc, hOld);
    DeleteObject(hBmMem);
    DeleteDC    (anim.hDc);

    EndPaint(hWnd, &ps);
    break;
  default:  
    return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
