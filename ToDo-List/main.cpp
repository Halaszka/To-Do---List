#include <Windows.h>
#include <string>
#include <fstream>
#include <gdiplus.h>
#include <CommCtrl.h>

#include "customBtn.h"
#include "colors.h"
#include "todo.h"
#include "drawings.h"

#define VERSION "Banana V - 1.2"


#pragma comment(lib, "Gdiplus.lib")

using namespace std;
using namespace Gdiplus;
//HFONT "hFont" with Arial
HFONT hFont = CreateFontA(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 0, "Arial");
HFONT hFontList = CreateFontA(19, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 0, "Arial");


HWND listBox;

HWND editBox;



int setEntries() {
	//Set the Entries
	if (entries.size() != 0) {
		for (int i = 0; i != entries.size(); i++) {
			SendMessageA(listBox, LB_ADDSTRING, 0, (LPARAM)entries.at(i).c_str());
		}
	}
	
	return 0;
}





LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static RECT rect;

	static RECT clientRect;

	static HINSTANCE hInstance = GetModuleHandle(NULL);

	switch (msg) {

	case WM_CREATE:
		//Add the List-Box to the Window to show the current To-Do List
		listBox = CreateWindow(WC_LISTBOX, NULL, WS_CHILD | WS_VISIBLE | LBS_HASSTRINGS | LBS_NOTIFY | WS_VSCROLL, 125, 100, 250, 250, hwnd, (HMENU)1, hInstance, NULL);
		//Add the Edit-Box to the Window to add new Items
		editBox = CreateWindow(WC_EDIT, NULL, WS_CHILD | WS_VISIBLE | ES_LEFT , 125, 350, 250, 23, hwnd, (HMENU)2, hInstance, NULL);
		
		createCustomBtn(hwnd, hInstance);

		//Change the Font to Arial
		SendMessage(listBox, WM_SETFONT, (WPARAM) hFontList, TRUE);
		SendMessage(editBox, WM_SETFONT, (WPARAM)hFont, TRUE);

		//Set Max Len for EditBox
		SendMessage(editBox, EM_LIMITTEXT, 16, 0);

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
			if (len < 2) {
				MessageBoxA(hwnd, "Please enter more characters!", "Error", MB_OK | MB_ICONERROR);
				return 0;
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
				MessageBoxA(hwnd, "You have to select an item to be able to remove it!", "Error", MB_OK | MB_ICONERROR);
			}
			else {
				//Get the Text of the selected Item
				SendMessageA(listBox, LB_GETTEXT, rc, (LPARAM)text.c_str());

				int rs;
				//Delete Item
				rs = deleteItem(text.c_str());

				if (rs == -1) {
					MessageBoxA(hwnd, "Error something went wrong!", "Error", MB_OK | MB_ICONERROR);
				}
				else {
					MessageBoxA(hwnd, "Deleted!", "Information", MB_OK | MB_ICONINFORMATION);
				}

				//Delete Item from List-Box
				rs = SendMessage(listBox, LB_DELETESTRING, rc, 0);

				if (rs == LB_ERR) {
					MessageBoxA(hwnd, "Error something went wrong!", "Error", MB_OK | MB_ICONERROR);
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