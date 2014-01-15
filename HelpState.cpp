#include "HelpState.h"


HelpState::HelpState(GameEngine *engine) : GameState(engine)
{
	b1xMin = b1xMax = b1yMin = b1yMax = 0;

	data[0] = ReadTGA("./assets/menu/retour.tga");
	data[1] = ReadTGA("./assets/menu/helpBackground.tga");
}


HelpState::~HelpState()
{
}


void HelpState::setup()
{
	bool cursorVisible;
	do{
		cursorVisible = ShowCursor(true) < 0;
	} while (cursorVisible);

	width = engine->getParentEngine()->getWidth();
	height = engine->getParentEngine()->getHeight();

	//glOrtho(0, width, height, 0, -1.0, 1.0);

	b1xMin = width * .4; b1xMax = width * .6;

	b1yMin = height * 0.8;	b1yMax = b1yMin + height *.12;


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
			glTexEnvi(GL_TEXTURE, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
	}
}

void HelpState::display(unsigned int width, unsigned int height)
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
	glColor4f(0.6, 0.6, 0.6, 1);
	glBindTexture(GL_TEXTURE_2D, (GLuint)data[1]->pUserData);
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

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void HelpState::lButtonUp(POINT pos)
{
	if (pos.x > b1xMin && pos.x < b1xMax)
	{
		if (pos.y > b1yMin && pos.y < b1yMax)
		{
			engine->nextState(0);
		}
	}
}

void HelpState::update(float fDT)
{

}