#include "MainMenuState.h"
#include <string.h>

ofstream f("./log/menu.txt");

int score = 0;
float tim = 0;
float c1, c2;
float mun = 1.f, mun1 = .0f, mun2 = .5f;
float coeff = .016f, coeff1 = .016f, coeff2 = .016f;

MainMenuState::MainMenuState(GameEngine *engine) : GameState(engine)
{
	b1xMin = b1xMax = b1yMin = b1yMax = 0;
	b2xMin = b2xMax = b2yMin = b2yMax = 0;

	r = .6f; g = .6f; b = .6f;
	data[0] = ReadTGA("./assets/menu/play.tga");
	data[1] = ReadTGA("./assets/menu/quit.tga");
}


MainMenuState::~MainMenuState(void)
{
	f.close();
}

void MainMenuState::setup()
{	
	bool cursorVisible;
	do{
		cursorVisible = ShowCursor(true) < 0;
	} while (cursorVisible);

	width = engine->getParentEngine()->getWidth();
	height = engine->getParentEngine()->getHeight();

	glOrtho(0, width, height, 0, -1.0, 1.0);

	b1xMin = b2xMin = width * .4;	b1xMax = b2xMax = width * .6;
	b1yMin = height *.2;	b1yMax = height *.4;
	b2yMin = height *.6;	b2yMax = height *.8;

	glClearColor(r, g, b, 1);

	for (int i = 0; i < 2; i++)
	{
		if (data[i]){
			data[i]->pUserData = new GLuint();
			GLuint id;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			data[i]->pUserData = (GLuint*)id;

			int format;
			int nb;

			if (data[i]->PixelFormat == PIXELFORMAT_R8G8B8){
				format = GL_RGB;
				nb = 3;
			}
			else{
				format = GL_RGBA;
				nb = 4;
			}

			glTexImage2D(GL_TEXTURE_2D, 0, nb, data[i]->u32Width, data[i]->u32Height, 0, format, GL_UNSIGNED_BYTE, data[i]->pu8Pixels);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
	}
}

void MainMenuState::display(unsigned int u32Width, unsigned int u32Height)
{
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, (GLuint)data[0]->pUserData);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);
	glVertex2f(b1xMin, b1yMin);
	glTexCoord2i(0, 1);
	glVertex2f(b1xMin, b1yMax);
	glTexCoord2i(1, 1);
	glVertex2f(b1xMax, b1yMax);
	glTexCoord2i(1, 0);
	glVertex2f(b1xMax, b1yMin);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, (GLuint)data[1]->pUserData);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);
	glVertex2f(b2xMin, b2yMin);
	glTexCoord2i(0, 1);
	glVertex2f(b2xMin, b2yMax);
	glTexCoord2i(1, 1);
	glVertex2f(b2xMax, b2yMax);
	glTexCoord2i(1, 0);
	glVertex2f(b2xMax, b2yMin);
	glEnd();
	glDisable(GL_TEXTURE_2D);

}

void MainMenuState::lButtonUp(POINT pos)
{
	if (pos.x > b1xMin && pos.x < b1xMax)
	{
		if (pos.y > b1yMin && pos.y < b1yMax)
		{
			engine->nextState(1);
		}
	}

	if (pos.x > b2xMin && pos.x <b2xMax)
	{
		if (pos.y > b2yMin && pos.y < b2yMax)
		{
			exit(0);
		}
	}
}




void MainMenuState::update(float fDT)
{
}