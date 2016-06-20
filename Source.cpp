
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>       //TCHAR and _T() ,anything related with UNICODE and ASCII .
#include <atlimage.h>    // for using the Cimage class . 




int WINAPI WinMain (
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	/*HWND hWnd = GetConsoleWindow ();
	ShowWindow (hWnd, SW_HIDE);         //hide the Console Window ,if your build target is console application I guess .
	Sleep (1000);*/


	int x = GetSystemMetrics (SM_CXVIRTUALSCREEN);    // get the max width of the screen 
	int y = GetSystemMetrics (SM_CYVIRTUALSCREEN);    // same as above



	HDC hScreenDC = GetDC (NULL);    //get the fullscreen device context ,maybe this object is unique in the whole system ,only one app can call it each time
	HDC hDC = CreateCompatibleDC (hScreenDC);   //create a compatibale device context for copying ?
	HBITMAP hBitmap = CreateCompatibleBitmap (hScreenDC, x, y);  //create a compatibale bitmap to mess up with the Compatible DC mentioned above 
	SelectObject (hDC, hBitmap);   //messing up hBitmap with the hDC ,both were newly created .
	BitBlt (hDC, 0, 0, x, y, hScreenDC, 0, 0, SRCCOPY); // messing up two DCs , I don't know the internal stuffs ,sorry . 

	//OpenClipboard (NULL);
	//EmptyClipboard ();
	//SetClipboardData (CF_BITMAP, hBitmap);   //dealing with clipboard stuffs .....
	//HBITMAP hBitmap1 = (HBITMAP)GetClipboardData (CF_BITMAP);  //get the bitmap handle from clipboard 

	CImage image;       // these parts dealing with image saving 
	image.Attach (hBitmap);     //these parts are from atlimage.h header ,it is a MFC and ATL shared libary or framework 
	TCHAR name[10] = _T ("test.png");    //Codeblocks doesn't include this ATL stuffs by default , you have to use Visual Studio to compile this 
	image.Save (name, Gdiplus::ImageFormatPNG);   // these parts dealing with image saving 

	/*CloseClipboard ();*/

	DeleteDC (hDC);   //delete the compatible DC object you've created and used 
	DeleteObject (hBitmap);  // delete the compatible bitmap object .
	ReleaseDC (NULL, hScreenDC);  //release the system device context you've called. 


	return 0;

	// This program works well ,under windows 7 environment .
}
