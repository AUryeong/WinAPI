#include "pch.h"

BG* InitBG(DOUBLEBUFFER* db)
{
	BG* Temp;
	Temp = (BG*)malloc(sizeof(BG));
	Temp->DB = db;

	LoadBMP(db, L"./Image/BG/aquarium1.bmp");
	
	return Temp;
}

void ChangeBackground(BG* bg, int backgroundNumber) 
{
	switch (backgroundNumber) {
	default:
	case BLUEAR:
		LoadBMP(bg->DB, L"./Image/BG/aquarium1.bmp");
		break;
	case PINKAR:
		LoadBMP(bg->DB, L"./Image/BG/aquarium2.bmp");
		break;
	case SKYBLUEAR:
		LoadBMP(bg->DB, L"./Image/BG/aquarium3.bmp");
		break;
	case PURPLEAR:
		LoadBMP(bg->DB, L"./Image/BG/aquarium4.bmp");
		break;
	case DARKAR:
		LoadBMP(bg->DB, L"./Image/BG/aquarium5.bmp");
		break;
	case GREENAR:
		LoadBMP(bg->DB, L"./Image/BG/aquarium6.bmp");
		break;
	}
}

void Process(BG* bg) 
{

}

void Render(BG* bg) 
{
	int x, y; //좌표
	int w, h; //크기

	x = bg->DB->BufferSize.left;
	y = bg->DB->BufferSize.top;
	w = bg->DB->BufferSize.right - bg->DB->BufferSize.left; //너비
	h = bg->DB->BufferSize.bottom - bg->DB->BufferSize.top; //높이

	//이미지에서 정보 얻기
	BITMAP bmpInfo;
	GetObject(bg->DB->hbmImage, sizeof(BITMAP), &bmpInfo);
	int ImgW = bmpInfo.bmWidth;
	int ImgH = bmpInfo.bmHeight;

	//BitBlt(Obj->hdcBack, x, y, w, h, Obj->hdcImage, 0, 0, SRCCOPY);
	StretchBlt(bg->DB->hdcBack, x, y, w, h,
		bg->DB->hdcImage, 0, 0, ImgW, ImgH, SRCCOPY);
}

void Release(BG* bg)
{
	DeleteObject(bg->DB->hbmImage);
	free(bg);
}