#include <Windows.h>
#include <tchar.h>
#include <time.h>

int winWidth = 480;
int winHeight = 360;
int x = 750;
int y = 100;
unsigned int step = 100;

WNDCLASS wc;
int r = 0, g = 255, b = 255;

HBRUSH color_of_window = CreateSolidBrush(RGB(r, g, b));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame2");
TCHAR WinTitle[] = _T("Окно 2");

int WINAPI _tWinMain(HINSTANCE This,
	HINSTANCE Prev,
	LPTSTR cmd,
	int mode) {
	HWND hWnd;
	MSG msg;

	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = color_of_window;

	if (!RegisterClass(&wc)) return 0;

	hWnd = CreateWindow(WinName,
		WinTitle,
		WS_OVERLAPPEDWINDOW,
		x,
		y,
		winWidth,
		winHeight,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);

	ShowWindow(hWnd, mode);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_USER + 1:
		MessageBox(hWnd,
			_T("Дескриптор получен!\n"),
			_T("Еще одно очень важное сообщение"), MB_OK);
		break;
	case WM_USER + 2:
		ExitWindows(EWX_REBOOT, 0); // выход из системы
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}