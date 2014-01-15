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
	b3xMin = b3xMax = b3yMin = b3yMax = 0;

	r = .6f; g = .6f; b = .6f;
	data[0] = ReadTGA("./assets/menu/play.tga");
	data[1] = ReadTGA("./assets/menu/help.tga");
	data[2] = ReadTGA("./assets/menu/quit.tga");
	data[3] = ReadTGA("./assets/menu/background.tga");
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

	//glOrtho(0, width, height, 0, -1.0, 1.0);

	b1xMin = b2xMin = b3xMin = width * .4;	b1xMax = b2xMax = b3xMax =  width * .6;

	b1yMin = height * 0.4;	b1yMax = b1yMin + height *.12;
	b2yMin = b1yMax + height *.01;	b2yMax = b2yMin + height *.12;
	b3yMin = b2yMax + height *.01;	b3yMax = b3yMin + height *.12;

	glClearColor(r, g, b, 1);

	for (int i = 0; i < 4; i++)
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
			glTexEnvi(GL_TEXTURE, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
	}
}

void MainMenuState::display(unsigned int u32Width, unsigned int u32Height)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glTranslatef(0, 1.* height, 0);
	glScalef(1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, (GLuint)data[3]->pUserData);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);
	glVertex2f(0, 0);
	glTexCoord2i(0, 1);
	glVertex2f(0, height);
	glTexCoord2i(1, 1);
	glVertex2f(width, height);
	glTexCoord2i(1, 0);
	glVertex2f(width, 0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, (GLuint)data[0]->pUserData);
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

	glBindTexture(GL_TEXTURE_2D, (GLuint)data[1]->pUserData);
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

	glBindTexture(GL_TEXTURE_2D, (GLuint)data[2]->pUserData);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);
	glVertex2f(b3xMin, b3yMin);
	glTexCoord2i(0, 1);
	glVertex2f(b3xMin, b3yMax);
	glTexCoord2i(1, 1);
	glVertex2f(b3xMax, b3yMax);
	glTexCoord2i(1, 0);
	glVertex2f(b3xMax, b3yMin);
	glEnd();

	glDisable(GL_BLEND);
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
			engine->nextState(3);
		}
	}

	if (pos.x > b3xMin && pos.x <b3xMax)
	{
		if (pos.y > b3yMin && pos.y < b3yMax)
		{
			exit(0);
		}
	}
}




void MainMenuState::update(float fDT)
{
}