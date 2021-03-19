#include <Windows.h>
#include <gdiplus.h>

#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;

const int ADD_CLICKED = 55;
const int REMOVE_CLICKED = 56;

HWND removeBtn;
HWND addBtn;


LRESULT CALLBACK rmvBtnProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK addBtnProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


//createCustomBtn | Add the Button "Add" to the Window
int createCustomBtn(HWND hwnd, HINSTANCE hInstance) {
	const wchar_t szBtn[] = L"ToDo_Addbtn";

	WNDCLASS wc = {};

	wc.lpszClassName = szBtn;
	wc.lpfnWndProc = addBtnProc;
	wc.hInstance = hInstance;

	RegisterClass(&wc);

	addBtn = CreateWindow(szBtn, L"Add", WS_CHILD | WS_VISIBLE | WS_BORDER, 125, 380, 250, 50, hwnd, (HMENU)3, hInstance, NULL);


	const wchar_t szremoveBtn[] = L"ToDo_RemoveBtn";

	WNDCLASS wcA = {};

	wcA.lpszClassName = szremoveBtn;
	wcA.lpfnWndProc = rmvBtnProc;
	wcA.hInstance = hInstance;

	RegisterClass(&wcA);

	removeBtn = CreateWindow(szremoveBtn, L"Remove", WS_CHILD | WS_VISIBLE | WS_BORDER, 380, 380, 75, 50, hwnd, (HMENU)4, hInstance, NULL);
	return 0;
}


//drawCustomBtn()
void drawCustomAddBtn(HDC hdc, RECT rect) {
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
	stringFormat.SetAlignment(StringAlignmentCenter);
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

//BtnProc
LRESULT CALLBACK addBtnProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	static RECT rect;

	switch (msg) {

	case WM_SIZE:

		GetWindowRect(hwnd, &rect);

		return 0;

	case WM_PAINT:

		HDC hdc;
		PAINTSTRUCT ps;

		hdc = BeginPaint(hwnd, &ps);

		drawCustomAddBtn(hdc, rect);

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