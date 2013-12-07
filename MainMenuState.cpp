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
	
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	
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

	drawHub();

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

void MainMenuState::drawHub()
{
	string s1 = "SCORE : ";
	string s2 = to_string(score);
	string s = s1 + s2;
	const char *c = s.c_str();
	render_string(10, 20, 0, GLUT_BITMAP_9_BY_15, c);

	string t1 = "TEMPS : ";
	string t2 = to_string((int)tim);
	string t = t1 + t2;
	const char *ct = t.c_str();
	render_string(width/2 - 80, 20, 0, GLUT_BITMAP_9_BY_15, ct);

	setColorRtoG(c1, c2, mun);
	glColor3f(c1, c2, 0);
	drawQuads(1700, 20, 200 * mun, 10);

	setColorRtoG(c1, c2, mun1);
	glColor3f(c1, c2, 0);
	drawQuads(1700, 40, 200 * mun1, 10);

	setColorRtoG(c1, c2, mun2);
	glColor3f(c1, c2, 0);
	drawQuads(1700, 60, 200*mun2,10);
}

void MainMenuState::setColorRtoG(float &r, float &g, float position)
{
	if (position <= .5f)
	{
		r = 1;
		g = 2 * position;
	}
	else{
		r = 2 * (1 - position);
		g = 1;
	}
}

void MainMenuState::drawQuads(float x, float y, float width, float height)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

void MainMenuState::render_string(float x, float y, float z, void* font, const char* s)
{
	glColor3f(.0f, .0f, .0f);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2f(x, y);
	while (*s)
	{
		glutBitmapCharacter(font, *s);
		s++;
	}
}

void MainMenuState::update(float fDT)
{
	score++;
	tim += fDT;

	if (mun <= .0f){
		coeff = .016f;
	}
	else if (mun >= 1.f)
	{
		coeff= -.016f;
	}
	mun += coeff;

	if (mun1 <= .0f){
		coeff1 = .016f;
	}
	else if (mun1 >= 1.f)
	{
		coeff1 = -.016f;
	}
	mun1 += coeff1;

	if (mun2 <= .0f){
		coeff2 = .016f;
	}
	else if (mun2 >= 1.f)
	{
		coeff2 = -.016f;
	}
	mun2 += coeff2;
}