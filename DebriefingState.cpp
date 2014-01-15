#include "DebriefingState.h"
#include "MyEngine.h";
#include <sstream>

DebriefingState::DebriefingState(GameEngine *engine) : GameState(engine)
{
	b1xMin = b1xMax = b1yMin = b1yMax = 0;
	clearStatistics();
}


DebriefingState::~DebriefingState()
{
}

void DebriefingState::setup()
{
	bool cursorVisible;
	do{
		cursorVisible = ShowCursor(true) < 0;
	} while (cursorVisible);
	width = engine->getParentEngine()->getWidth();
	height = engine->getParentEngine()->getHeight();

	glOrtho(0, width, height, 0, -1.0, 1.0);

	glClearColor(1.f, 1.f, 1.f, 1);

	b1xMin = width*.7f;
	b1xMax = width*.9f;
	b1yMin = height*.8f;
	b1yMax = height*.9f;

}

void DebriefingState::display(unsigned int u32Width, unsigned int u32Height)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	/*r = .5f; g = .5f; b = .5f;
	glColor4f(r, g, b, 1);

	glBegin(GL_QUADS);
	glVertex2f(b1xMin, b1yMin);
	glVertex2f(b1xMax, b1yMin);
	glVertex2f(b1xMax, b1yMax);
	glVertex2f(b1xMin, b1yMax);
	glEnd();*/

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);

	ostringstream oAccCancer, oInaccCancer; 
	ostringstream oAccBacteria, oInaccBacteria;
	ostringstream oAccBacteriaWaste, oInaccBacteriaWaste;
	ostringstream oAccVirus, oInaccVirus;
	string debrief1, debrief2, debrief3, debrief4;

	render_string(width *.3f, height *.2f, GLUT_BITMAP_9_BY_15, "DEBRIEFING");
	render_string((b1xMin + b1xMax) / 2, (b1yMin + b1yMax) / 2, GLUT_BITMAP_9_BY_15, "Next level");

	//SCORE:



	if (cancerAccuracy + cancerInaccuracy != 0)
	{
		oAccCancer << 100.f*cancerAccuracy / (cancerAccuracy + cancerInaccuracy);
		//oInaccCancer << (float)(cancerInaccuracy / (cancerAccuracy + cancerInaccuracy))*100.f;

		debrief1 = "vous avez tire ";
		debrief1 += oAccCancer.str();
		debrief1 += "% de lymphocytes sur les cellules cancereuses.";
		//debrief1 += oInaccCancer.str();
		//debrief1 += "% de monocyte et neutrophile";

		render_string(width *.3f, height *.40f, GLUT_BITMAP_9_BY_15, debrief1.c_str());
	}
	if (bacteriaAccuracy + bacteriaInaccuracy != 0)
	{
		oAccBacteria << 100.f*bacteriaAccuracy / (bacteriaAccuracy + bacteriaInaccuracy);
		//oInaccBacteria << (float)(bacteriaInaccuracy / (bacteriaAccuracy + bacteriaInaccuracy))*100.f;

		debrief2 = "vous avez tire ";
		debrief2 += oAccBacteria.str();
		debrief2 += "% de neutrophiles sur les bacteries.";
		//debrief2 += oInaccBacteria.str();
		//debrief2 += "% de monocyte et lymphocyte";

		render_string(width *.3f, height *.42f, GLUT_BITMAP_9_BY_15, debrief2.c_str());
	}

	if (bacteriaWasteAccuracy + bacteriaWasteInaccuracy != 0)
	{
		oAccBacteriaWaste << 100.f*bacteriaWasteAccuracy / (bacteriaWasteAccuracy + bacteriaWasteInaccuracy);
		//oInaccBacteriaWaste << (float)(bacteriaWasteInaccuracy / (bacteriaWasteAccuracy + bacteriaWasteInaccuracy))*100.f;

		debrief3 = "vous avez tire ";
		debrief3 += oAccBacteriaWaste.str();
		debrief3 += "% de monocytes sur les debris.";
		//debrief3 += oInaccBacteriaWaste.str();
		//debrief3 += "% de monocyte et lymphocyte";

		render_string(width *.3f, height *.44f, GLUT_BITMAP_9_BY_15, debrief3.c_str());
	}
	
	if (virusAccuracy + virusInaccuracy != 0)
	{
		oAccVirus << 100.f*virusAccuracy / (virusAccuracy + virusInaccuracy);
		//oInaccVirus << (float)(virusInaccuracy / (virusAccuracy + virusInaccuracy))*100.f;

		debrief4 = "vous avez tire ";
		debrief4 += oAccVirus.str();
		debrief4 += "% de lymphocytes sur les virus.";
		//debrief4 += oInaccVirus.str();
		//debrief4 += "% de monocyte et neutrophile";

		render_string(width *.3f, height *.46f, GLUT_BITMAP_9_BY_15, debrief4.c_str());
	}

}

void DebriefingState::update(float fDT)
{
}

void DebriefingState::render_string(float x, float y, void* font, const char* s)
{
	glColor3f(.5f, .5f, .5f);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glRasterPos2f(x, y);
	while (*s)
	{
		glutBitmapCharacter(font, *s);
		s++;
	}

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}

void DebriefingState::lButtonUp(POINT pos)
{
	if (pos.x > b1xMin && pos.x < b1xMax)
	{
		if (pos.y > b1yMin && pos.y < b1yMax)
		{
			engine->nextState(1);
			clearStatistics();
		}
	}
}

void DebriefingState::updateStatistics(ObjectType target, ObjectType ammo)
{
	if (target == virusType)
	{
		if (ammo == lymphocyteTagVirus)
		{
			virusAccuracy++;
		}
		else if (ammo != monocyteType && ammo != cellType)
		{
			virusInaccuracy++;
		}
		
	}

	if (target == cancerTypeDeclared || target == cancerTypeUndeclared)
	{
		if (ammo == lymphocyteTagCancer)
		{
			cancerAccuracy++;
		}
		else if (ammo != monocyteType && ammo != cellType)
		{
			cancerInaccuracy++;
		}
	}

	if(target == bacteriaType)
	{
		if (ammo == neutrophileType)
		{
			bacteriaAccuracy++;
		}
		else if (ammo != cellType)
		{
			bacteriaInaccuracy++;
		}
	}

	if (target == bacteriaWasteType)
	{
		if (ammo == monocyteType)
		{
			bacteriaWasteAccuracy++;
		}
		else if(ammo != cellType)
		{
			bacteriaWasteInaccuracy++;
		}
	}
}

void DebriefingState::clearStatistics()
{
	virusAccuracy = 0;
	virusInaccuracy = 0;
	cancerAccuracy = 0;
	cancerInaccuracy = 0;
	bacteriaAccuracy = 0;
	bacteriaInaccuracy = 0;
	bacteriaWasteAccuracy = 0;
	bacteriaWasteInaccuracy = 0;
}