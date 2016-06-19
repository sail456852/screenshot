
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <atlimage.h>


void Save (HWND hWnd);

int WINAPI WinMain (
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	HWND hWnd = GetConsoleWindow ();
	ShowWindow (hWnd, SW_HIDE);
	Sleep (1000);

	int x = GetSystemMetrics (SM_XVIRTUALSCREEN);
	int y = GetSystemMetrics (SM_YVIRTUALSCREEN);
	int x1 = GetSystemMetrics (SM_CXVIRTUALSCREEN);
	int y1 = GetSystemMetrics (SM_CYVIRTUALSCREEN);

	int w = x1 - x;
	int h = y1 - y;

	HDC hScreenDC = GetDC (NULL);
	HDC hDC = CreateCompatibleDC (hScreenDC);
	HBITMAP hBitmap = CreateCompatibleBitmap (hScreenDC, w, h);
	HGDIOBJ old_obj = SelectObject (hDC, hBitmap);
	BOOL bRet = BitBlt (hDC, 0, 0, w, h, hScreenDC, x, y, SRCCOPY);

	OpenClipboard (NULL);
	EmptyClipboard ();
	SetClipboardData (CF_BITMAP, hBitmap);
	Save (hWnd);
	CloseClipboard ();
	return 0;

}

void Save (HWND hWnd)
{
	if (!IsClipboardFormatAvailable (CF_DIB))
		return;
	if (!OpenClipboard (hWnd))
		return;

	HBITMAP hBitmap = (HBITMAP)GetClipboardData (CF_BITMAP);

	TCHAR szName[MAX_PATH] = { 0 };
	SYSTEMTIME st = { 0 };
	::GetLocalTime (&st);
	_stprintf_s (szName, _T ("%02d-%02d-%02d-%03d.bmp"), st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
	CImage image;
	image.Attach (hBitmap);
	image.Save (szName, Gdiplus::ImageFormatBMP);
	CloseClipboard ();
}