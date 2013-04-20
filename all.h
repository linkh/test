#include <Windows.h>
#include <stdio.h>
#include "game_param.h"

typedef struct 
{
	int w, h, wCellSize, hCellSize;
	HDC hDc;
}Anim;

 class colorArray
{
public:
	static int* getRgb(int num)
	{
		int color[3];

		switch(num)
		{
			case 0:
				color[0] = 255;
				color[1] = 0;
				color[2] = 0;
				break;
			case 1:
				color[0] = 0;
				color[1] = 255;
				color[2] = 0;
				break;
			case 2:
				color[0] = 0;
				color[1] = 0;
				color[2] = 255;
				break;
			case 3:
				color[0] = 13;
				color[1] = 77;
				color[2] = 25;
				break;
			case 4:
				color[0] = 255;
				color[1] = 255;
				color[2] = 0;
				break;
			case 5:
				color[0] = 0;
				color[1] = 255;
				color[2] = 255;
				break;
			case 6:
				color[0] = 255;
				color[1] = 0;
				color[2] = 255;
				break;
			default:
				color[0] = 255;
				color[1] = 255;
				color[2] = 255;
				break;
		}
	}
};

class object
{
public:
	virtual void draw(Anim anim, int x, int y);
};

class emptyCell
{
	public:
	void draw(Anim anim, int x, int y)
	{
	};
};

class ball:object
{
protected:
	int color;
public:
	void draw(Anim anim, int x, int y)
	{
		HGDIOBJ hBrush, hOldBrush;
		int *rgb = new int[3];
		rgb = colorArray::getRgb(color);

		hOldBrush = GetStockObject(WHITE_BRUSH);
		hBrush = CreateSolidBrush(RGB(rgb[0], rgb[1], rgb[2]));
		SelectObject(anim.hDc, hBrush);

		int cs = min(anim.hCellSize, anim.wCellSize);
		Ellipse(anim.hDc, x + (anim.wCellSize - cs) / 2, y + (anim.hCellSize - cs) / 2, 
			x + (anim.wCellSize + cs) / 2, y + (anim.hCellSize + cs) / 2); 

		
		SelectObject(anim.hDc, hOldBrush);
		DeleteObject(hOldBrush);
		DeleteObject(hBrush);
	}
};

class selectedBall:ball
{
public:
	void draw(Anim anim, int x, int y)
	{
		int cs = min(anim.hCellSize, anim.wCellSize) / 2;
		Ellipse(anim.hDc, x + (anim.wCellSize - cs) / 2, y + (anim.hCellSize - cs) / 2, 
			x + (anim.wCellSize + cs) / 2, y + (anim.hCellSize + cs) / 2); 
	}
};

class step:object
{
	public:
	void draw(Anim anim, int x, int y)
	{
		int cs = min(anim.hCellSize, anim.wCellSize) / 2;
		Ellipse(anim.hDc, x + (anim.wCellSize - cs) / 2, y + (anim.hCellSize - cs) / 2, 
			x + (anim.wCellSize + cs) / 2, y + (anim.hCellSize + cs) / 2); 
	}
};




class Path
{
public:
	int numToDraw, sizePath, *way;
	void freeMemory();
	void findWay(object *map)
	{

	}
};

class Map
{
protected:
	object *map[NUM_CELL * NUM_CELL];
	Path path;
public:
	void drawMap(Anim anim, int x, int y)
	{
		int wCellSize = (int)( (anim.w - x) / (double)NUM_CELL), hCellSize = (int)( ( anim.h - y ) / (double)NUM_CELL );
		for (int i = 1; i < NUM_CELL; i++)
		{
			MoveToEx(anim.hDc, x + wCellSize * i, MENU_SIZE, NULL);
			LineTo(anim.hDc, x + wCellSize * i, anim.h);

			MoveToEx(anim.hDc, x, y + hCellSize * i, NULL);
			LineTo(anim.hDc, anim.w, y + hCellSize * i);
		}
	}

	void drawMapContent(Anim anim, int x, int y)
	{
		int wCellSize = (int)( (anim.w - x) / (double)NUM_CELL), hCellSize = (int)( ( anim.h - y ) / (double)NUM_CELL );

		for (int i = 0; i < NUM_CELL; i++)
			for (int j = 0; i < NUM_CELL; j++)
			{
				map[ i * NUM_CELL + j]->draw(anim,  x + wCellSize * i, y + hCellSize * i );
			}
	}
};

class Menu
{
protected:
	int points;
public:
	void draw(Anim anim, int x, int y)
	{
		HGDIOBJ hBrush, hOldBrush;

		hOldBrush = GetStockObject(WHITE_BRUSH);
		hBrush = GetStockObject(DKGRAY_BRUSH);
		SelectObject(anim.hDc, hBrush);


		Rectangle(anim.hDc, 0, 0, anim.w, MENU_SIZE);
		wchar_t buf[10] = TEXT("points:");
		swprintf(buf + wcslen(buf),L"%d",x);
		SetBkMode(anim.hDc, TRANSPARENT);
		TextOut(anim.hDc, 0, 0, (LPCWSTR)buf, 10);

		SelectObject(anim.hDc, hOldBrush);
		DeleteObject(hOldBrush);
		DeleteObject(hBrush);
	}
};

/*
class render
{
	struct data mapData;
	
	void addNewBalls()
	{
	}

	void getRender()
	{
		if(mapData.way.numToDraw != 0)
		{
			//mapData.way.add1StepTodRraw();
			//InvalidateRect();
		}
		else if(mapData.way.sizePath != 0)
		{
			addNewBalls();
			mapData.way.freeMemory();
			//InvalidateRect();
		}
	}

	void onMouse()
	{
		//
		//InvalidateRect();
	}
};
*/

/*
	case WM_PAINT:
		render.getRender();
		draw.DrawAll
*/
