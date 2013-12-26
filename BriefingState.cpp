#include "BriefingState.h"


BriefingState::BriefingState(GameEngine *engine) : GameState(engine)
{
	b1xMin = b1xMax = b1yMin = b1yMax = 0;
	b2xMin = b2xMax = b2yMin = b2yMax = 0;
	b3xMin = b3xMax = b3yMin = b3yMax = 0;
	r = .6f; g = .6f; b = .6f;

	//   --- load textures ---
	data[0] = ReadTGA("./assets/briefing/brief_lvl1.tga");
	//data[0] = ReadTGA("./assets/briefing/munition1.tga");
	data[1] = ReadTGA("./assets/briefing/munition1.tga");
	data[2] = ReadTGA("./assets/briefing/munition2.tga");
	data[3] = ReadTGA("./assets/briefing/munition3.tga");
	
}


BriefingState::~BriefingState()
{
}

void BriefingState::setup()
{
	width = engine->getParentEngine()->getWidth();
	height = engine->getParentEngine()->getHeight();

	glOrtho(0, width, height, 0, -1.0, 1.0);
	
	b1yMin = b2yMin = b3yMin = height * .65;	b1yMax = b2yMax = b3yMax = height * .9;
	b1xMin = width *.0625f;	b1xMax = width *.3125f;
	b2xMin = width *.375f;	b2xMax = width *.625f;
	b3xMin = width *.6875f;	b3xMax = width *.9375f;

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
		}
	}
}

void BriefingState::display(unsigned int u32Width, unsigned int u32Height)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, (GLuint)data[0]->pUserData);
	r = 1; g = 1; b = 1;
	glColor4f(r, g, b,1);

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

	glBindTexture(GL_TEXTURE_2D, (GLuint)data[1]->pUserData);
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
	glBindTexture(GL_TEXTURE_2D, (GLuint)data[2]->pUserData);

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

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, (GLuint)data[1]->pUserData);
	glColor3f(r, g, b);
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
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	
}

void BriefingState::lButtonUp(POINT pos)
{
	if (pos.x > b1xMin && pos.x < b1xMax)
	{
		if (pos.y > b1yMin && pos.y < b1yMax)
		{
			engine->nextState(2);
			engine->getHero()->setGenerator(1);
		}
	}

	if (pos.x > b2xMin && pos.x <b2xMax)
	{
		if (pos.y > b2yMin && pos.y < b2yMax)
		{
			engine->nextState(2);
			engine->getHero()->setGenerator(2);
		}
	}

	if (pos.x > b3xMin && pos.x <b3xMax)
	{
		if (pos.y > b3yMin && pos.y < b3yMax)
		{
			engine->nextState(2);
			engine->getHero()->setGenerator(3);
		}
	}
}




void BriefingState::update(float fDT)
{
}