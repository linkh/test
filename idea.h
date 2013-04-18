class object
{
public:
  virtual void draw();
};

class ball:object
{
protected:
	int color;
public:
	void draw()
	{
		//drawRound();
	}
};

class selectedBall:object
{
protected:
	int color;
public:
	void draw()
	{
		//drawRound();
	}
};

class step:object
{
	public:
	void draw()
	{
		//drawStepPoint();
	}
};




class path
{
public:
	int numToDraw, sizePath, *way;
};

struct data
{
	object map[8 * 8];
	int points;
	path way;
};

class draw
{
	void drawAll(object *map)
	{
		//drawEmptyMap();
		//drawMenu();//point & new game

		for (int i = 0; i < 8 * 8; i++)
			map[i].draw();
	}
};

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
			invalidateRect()
		}
		else if(mapData.way.sizePath != 0)
		{
			addNewBalls();
			mapData.way.freeMemory();
			invalidateRect()
		}
	}

	void onMouse()
	{
		//
		invalidateRect();
	}
};


...
	case WM_PAINT:
		render.getRender();
		draw.DrawAll
...
