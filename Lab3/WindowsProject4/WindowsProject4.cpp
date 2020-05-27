// Lab1.cpp : Определяет точку входа для приложения.
//

#include <random>
#include <time.h>
#include <tchar.h>
#include <string.h>

int WinWidth = 500;
int WinHeight = 500;
int Wx1 = 100;
int Wy1 = 100;

LRESULT CALLBACK WndProc1(HWND, UINT, WPARAM, LPARAM);

TCHAR Win1Name[] = _T("Main1Frame");
TCHAR Win1Title[] = _T("Потоки");
MSG msg;

HDC hdc;
HBRUSH brush;
PAINTSTRUCT ps;
HANDLE thread_1;

m_Window Win1;

int WINAPI _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode)
{
	Win1.WNDCLASSInit(This, Win1Name, WNDPROC(WndProc1));
	Win1.Register();
	Win1.m_CreateWindow(Win1Name, Win1Title, Wx1, Wy1, WinWidth, WinHeight, This);

	Win1.Show(mode);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LPRECT r;
DWORD WINAPI thread2(LPVOID t) {
	GetWindowRect(Win1.hWnd, r);

	HDC hdc;
	HBRUSH brush;
	PAINTSTRUCT ps;
	hdc = BeginPaint(Win1.hWnd, &ps);
	brush = CreateSolidBrush(RGB(0, 255, 0));
	SelectObject(hdc, brush);
	TextOut(hdc, 100, 300, _T("aqwaed"), 3);
	EndPaint(Win1.hWnd, &ps);

	return 0;
}

DWORD WINAPI thread1(LPVOID t)
{
	srand(time(0));

	brush = CreateSolidBrush(RGB(0, 255, 0));
	SelectObject(hdc, brush);
	while (true) {
		int r = rand() % 2;
		if (r == 0)
			Pie(hdc, 10, 10, 470, 200, 240, 200, 240, 10);
		else
			Pie(hdc, 10, 10, 470, 200, 240, 10, 240, 200);
		Sleep(1000);
		InvalidateRect(Win1.hWnd, NULL, TRUE);
	}

	return 0;
}

LRESULT CALLBACK WndProc1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		//HANDLE thread_2;
		thread_1 = CreateThread(NULL, 0, thread1, NULL, 0, NULL);
		//thread_2 = CreateThread(NULL, 0, thread2, NULL, 0, NULL);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		DeleteObject(brush);
		EndPaint(Win1.hWnd, &ps);
		break;
	case WM_PAINT:
		hdc = BeginPaint(Win1.hWnd, &ps);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


