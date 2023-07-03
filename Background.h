#pragma once

#define BLUEAR 1
#define PINKAR 2
#define SKYBLUEAR 3
#define PURPLEAR 4
#define DARKAR 5
#define GREENAR 6

typedef struct tagBACKGROUND 
{
	DOUBLEBUFFER* DB;
	
	//HBITMAP
}BG;

BG* InitBG(DOUBLEBUFFER* db);
void Process(BG* bg);
void ChangeBackground(BG* bg, int backgroundNumber = 0);
void Render(BG* bg);
void Release(BG* bg);