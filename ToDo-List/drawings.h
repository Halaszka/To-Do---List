#pragma once
#include <gdiplus.h>
#include <Windows.h>

#pragma comment(lib, "Gdiplus.lib")

using namespace Gdiplus;


void draw_title(HDC hdc, RECT rect) {
	//Define new Objekt graphics
	Graphics graphics(hdc);
	//Make Font-Family with the Font Arial
	FontFamily fontFamily(L"Arial");
	//Define the Font with Size 24
	Font font(&fontFamily, 24, FontStyleBold, UnitPixel);
	//Get the RectF to position the Text in the Center
	RectF rectF(0, 0, rect.right - rect.left - 24, rect.bottom - rect.top);
	//Get a Gradient with Red and Orange
	LinearGradientBrush title_brush(Point(0, 10), Point(rectF.Width, 10), Color(255, 69, 178, 157), Color(255, 89, 216, 230));

	//New Object from Stringformat
	StringFormat stringFormat;
	//Set the Alignment to Center
	stringFormat.SetAlignment(StringAlignmentCenter);
	//Set Anti-Aliasing On
	graphics.SetTextRenderingHint(TextRenderingHintAntiAlias);

	//Go Lower from height
	rectF.Y = +20;

	//Draw the Title
	graphics.DrawString(L"To Do - List", -1, &font, rectF, &stringFormat, &title_brush);
}

