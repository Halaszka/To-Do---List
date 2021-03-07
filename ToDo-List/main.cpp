#include <Windows.h>
#include <string>
#include <fstream>
#include <gdiplus.h>
#include <CommCtrl.h>

#include "customBtn.h"
#include "colors.h"
#include "todo.h"

const int ADD_CLICKED =  55;
const int REMOVE_CLICKED = 56;

#pragma comment(lib, "Gdiplus.lib")

using namespace std;
using namespace Gdiplus;
//HFONT "hFont" with Arial
HFONT hFont = CreateFontA(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 0, "Arial");
HFONT hFontList = CreateFontA(19, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 0, "Arial");

HWND customBtn;

HWND listBox;

HWND editBox;

HWND removeBtn;

//drawCustomBtn()
void drawCustomBtn(HDC hdc, RECT rect) {
	//Graphics Object
	Graphics graphics(hdc);

	//Gradient
	LinearGradientBrush gradient(Point(0, 75), Point(250, 0), Color(255, 80, 222, 127), Color(255, 58, 140, 125));
	//Draw a Rect
	graphics.FillRectangle(&gradient, 0, 0, rect.bottom, rect.right);
	//FontFamily
	FontFamily fontFamily(L"Arial");
	//Define the Font with Size 24
	Font font(&fontFamily, 26, FontStyleBold, UnitPixel);

	StringFormat stringFormat;
	stringFormat.SetAlignment(StringAlignmentCenter );
	stringFormat.SetLineAlignment(StringAlignmentCenter);

	RectF rectF(0, 0, rect.right - rect.left, rect.bottom - rect.top);

	SolidBrush white(Color(255, 255, 255, 255));

	graphics.DrawString(L"Add", -1, &font, rectF, &stringFormat, &white);


	

}

//drawRmvCustomBtn()
void drawRmvCustomBtn(HDC hdc, RECT rect) {
	//Graphics Object
	Graphics graphics(hdc);

	graphics.SetSmoothingMode(SmoothingMode::SmoothingModeAntiAlias);

	//Gradient
	LinearGradientBrush gradient(Point(380, 0), Point(455, 0), Color(255, 255, 33, 96), Color(255, 242, 62, 46));
	//Draw a Rect
	graphics.FillRectangle(&gradient, 0, 0, rect.bottom, rect.right);
	//FontFamily
	FontFamily fontFamily(L"Arial");
	//Define the Font with Size 24
	Font font(&fontFamily, 26, FontStyleRegular, UnitPixel);

	StringFormat stringFormat;
	stringFormat.SetAlignment(StringAlignmentCenter);
	stringFormat.SetLineAlignment(StringAlignmentCenter);

	RectF rectF(0, 0, rect.right - rect.left, rect.bottom - rect.top);

	SolidBrush white(Color(255, 255, 255, 255));

	graphics.DrawString(L"X", -1, &font, rectF, &stringFormat, &white);




}


int setEntries() {
	//Set the Entries
	if (entries.size() != 0) {
		for (int i = 0; i != entries.size(); i++) {
			SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM)entries.at(i).c_str());
		}
	}
	
	return 0;
}

//BtnProc
LRESULT CALLBACK btnProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static RECT rect;

	switch (msg) {

	case WM_SIZE:

		GetWindowRect(hwnd, &rect);

		return 0;

	case WM_PAINT:

		HDC hdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hwnd, &ps);

		drawCustomBtn(hdc, rect);

		EndPaint(hwnd, &ps);

		return 0;

	case WM_LBUTTONUP:

		SendMessage(GetParent(hwnd), WM_COMMAND, ADD_CLICKED, 0);

		return 0;
	}


	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//rmvBtnProc
LRESULT CALLBACK rmvBtnProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static RECT rect;

	switch (msg) {

	case WM_SIZE:

		GetWindowRect(hwnd, &rect);

		return 0;

	case WM_PAINT:

		HDC hdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hwnd, &ps);

		drawRmvCustomBtn(hdc, rect);

		EndPaint(hwnd, &ps);

		return 0;

	case WM_LBUTTONUP:

		SendMessage(GetParent(hwnd), WM_COMMAND, REMOVE_CLICKED, 0);

		return 0;
	}


	return DefWindowProc(hwnd, msg, wParam, lParam);
}



//createCustomBtn | Add the Button "Add" to the Window
int createCustomBtn(HWND hwnd, HINSTANCE hInstance) {
	const wchar_t szBtn[] = L"ToDo_Addbtn";

	WNDCLASS wc = {};

	wc.lpszClassName = szBtn;
	wc.lpfnWndProc = btnProc;
	wc.hInstance = hInstance;

	RegisterClass(&wc);

	customBtn = CreateWindow(szBtn, L"Add", WS_CHILD | WS_VISIBLE | WS_BORDER, 125, 380, 250, 50, hwnd, (HMENU)3, hInstance, NULL);


	const wchar_t szremoveBtn[] = L"ToDo_RemoveBtn";

	WNDCLASS wcA = {};

	wcA.lpszClassName = szremoveBtn;
	wcA.lpfnWndProc = rmvBtnProc;
	wcA.hInstance = hInstance;

	RegisterClass(&wcA);

	removeBtn = CreateWindow(szremoveBtn, L"Remove", WS_CHILD | WS_VISIBLE | WS_BORDER, 380, 380, 75, 50, hwnd, (HMENU) 4, hInstance, NULL);
	return 0;
}

void draw_title(HDC hdc, RECT rect) {
	//Define new Objekt graphics
	Graphics graphics(hdc);
	//Make Font-Family with the Font Arial
	FontFamily fontFamily(L"Arial");
	//Define the Font with Size 24
	Font font(&fontFamily,24, FontStyleBold, UnitPixel);
	//Get the RectF to position the Text in the Center
	RectF rectF(0, 0, rect.right - rect.left - 24, rect.bottom - rect.top);
	//Get a Gradient with Red and Orange
	LinearGradientBrush title_brush(Point(0, 10), Point(rectF.Width, 10), Color(255, 252, 162, 66), Color(255, 230, 71, 108));

	//New Object from Stringformat
	StringFormat stringFormat;
	//Set the Alignment to Center
	stringFormat.SetAlignment(StringAlignmentCenter);
	//Set Anti-Aliasing On
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	//Go Lower from height
	rectF.Y =+ 20;

	//Draw the Title
	graphics.DrawString(L"To Do - List", -1, &font, rectF, &stringFormat, &title_brush);
}


int timer_id = 1;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static RECT rect;

	static RECT clientRect;

	static HINSTANCE hInstance = GetModuleHandle(NULL);

	switch (msg) {

	case WM_CREATE:
		//Add the List-Box to the Window to show the current To-Do List
		listBox = CreateWindow(WC_LISTBOX, NULL, WS_CHILD | WS_VISIBLE | LBS_HASSTRINGS | LBS_NOTIFY, 125, 100, 250, 250, hwnd, (HMENU)1, hInstance, NULL);
		//Add the Edit-Box to the Window to add new Items
		editBox = CreateWindow(WC_EDIT, NULL, WS_CHILD | WS_VISIBLE | ES_LEFT , 125, 350, 250, 23, hwnd, (HMENU)2, hInstance, NULL);
		
		createCustomBtn(hwnd, hInstance);

		//Change the Font to Arial
		SendMessage(listBox, WM_SETFONT, (WPARAM) hFontList, TRUE);
		SendMessage(editBox, WM_SETFONT, (WPARAM)hFont, TRUE);

		InvalidateRect(listBox, NULL, TRUE);


		return 0;

		//WM_CLOSE
	case WM_CLOSE: {
		//Call WM_DESTROY
		DestroyWindow(hwnd);
		return 0;
	}
		//WM_DESTROY
	case WM_DESTROY: {
		//Quit the Window with Message 0
		PostQuitMessage(0);
		return 0;
	}
		//WM_SIZE
	case WM_SIZE: {
		//Get the Window Size
		GetWindowRect(hwnd, &rect);

		//Redraw the Window
		InvalidateRect(hwnd, NULL, TRUE);

		return 0;
	}

		//WM_PAINT
	case WM_PAINT:
		HDC hdc;
		PAINTSTRUCT ps;

		//Begin Paint
		hdc = BeginPaint(hwnd, &ps);

		//Call draw_title()
		draw_title(hdc, rect);

		EndPaint(hwnd, &ps);

		return 0;

		//WM_COMMAND
	case WM_COMMAND:

		//Check if Add Button is clicked
		if (LOWORD(wParam) == ADD_CLICKED) {
			//Buffer and Len
			char buffer[256];
			int len;
			//Get the length of the Text in the Edit Box
			len = GetWindowTextLength(editBox);

			//If Len is zero
			if (len == 0) {
				MessageBoxA(hwnd, "Please enter more characters!", "Error", MB_OK | MB_ICONERROR);
			}

			//Get the Text from the Edit Box
			GetWindowTextA(editBox, buffer, len + 1);

			string buffer_str(buffer);

			//Add the Item to List
			int rc = addItem(buffer_str);

			if (rc == 0) {
				//Add new Item
				SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM)buffer_str.c_str());
			}
			else {
				MessageBoxA(hwnd, "Error when adding!", "Error", MB_OK | MB_ICONERROR);
			}


			return 0;
		}

		//Check if Remove Button clicked
		if (LOWORD(wParam) == REMOVE_CLICKED) {
			string text = "";
			int rc;
			//Check if Selected
			rc = SendMessage(listBox, LB_GETCURSEL, 0, 0);
			//Error if nothing is selected
			if (rc == LB_ERR) {
				MessageBoxA(NULL, "You have to select an item to be able to remove it!", "Error", MB_OK | MB_ICONERROR);
			}
			else {
				//Get the Text of the selected Item
				SendMessageA(listBox, LB_GETTEXT, rc, (LPARAM)text.c_str());

				//Delete Item
				rc = deleteItem(text.c_str());

				if (rc == -1) {
					MessageBoxA(NULL, "Error something went wrong!", "Error", MB_OK | MB_ICONERROR);
				}
				else {
					MessageBoxA(NULL, "Deleted!", "Information", MB_OK | MB_ICONINFORMATION);
				}

				//Delete Item from List-Box
				int rs = SendMessage(listBox, LB_DELETESTRING, rc + 1, 0);

				if (rs == LB_ERR) {
					MessageBoxA(NULL, "Error something went wrong!", "Error", MB_OK | MB_ICONERROR);
				}

			}
		}
		return 0;

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {

	//Start GDI+
	ULONG_PTR gdiToken;
	GdiplusStartupInput gdiplusStartupInput;

	GdiplusStartup(&gdiToken, &gdiplusStartupInput, NULL);


	//Main-Window
	HWND hwnd;
	const wchar_t szMain[] = L"ToDo";
	WNDCLASS wc = {};
	MSG msg;

	//Define WNDCLASS "wc"
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = szMain;
	wc.hbrBackground = main_bg;

	//Register WNDCLASS "wc"
	RegisterClass(&wc);

	//Create Window
	hwnd = CreateWindow(szMain, L"ToDo-List", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZE | WS_MINIMIZEBOX , CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);

	//Show the Window 
	ShowWindow(hwnd, iCmdShow);

	//Create Directory "todo"
	int rc = createToDo();

	if (rc == -1) {
		MessageBoxA(hwnd, "Error while creating the folder!", "Error", MB_OK | MB_ICONERROR);
	}
	//Create .txt File
	rc = createToDoTXT();

	if (rc == -1) {
		MessageBoxA(hwnd, "Error while creating a file!", "Error", MB_OK | MB_ICONERROR);
	}

	//read the List
	rc = getList();

	if (rc == -1) {
		MessageBoxA(hwnd, "Error while reading a file!", "Error", MB_OK | MB_ICONERROR);
	}

	//Set the Entries
	setEntries();

	//Get Windows-Messages
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	//GDI+ Shutdown
	GdiplusShutdown(gdiToken);

	return 0;
}