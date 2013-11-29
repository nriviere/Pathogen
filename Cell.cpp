#include "Cell.h"
#include "GameEngine.h"
#include "SelfMovingPhysicalComponent.h"


Cell::Cell(GameEngine *engine) : ReplicableGameObject(engine)
{
	
}

Cell::Cell(GameEngine *engine,RenderableComponent *model, PhysicalComponent *physicalComponent) : ReplicableGameObject(engine,model, physicalComponent, 3)
{

}

Cell::Cell(const Cell &cell) : ReplicableGameObject(cell)
{
	
}

Cell &Cell::operator=(const Cell &cell)
{
	Cell::Cell(cell);
	return *this;
}

Cell::~Cell()
{

}

void Cell::replicate()
{
	if (GameEngine::CURRENT_CELL_COUNT < GameEngine::MAX_CELL_COUNT && GameEngine::CURRENT_CELL_COUNT < GameEngine::MAX_GAME_OBJECT_COUNT)
	{
		Cell *cell = new Cell(*this);
		engine->addObject(cell);
	}
}

void Cell::selfAdd()
{
	GameEngine::CURRENT_CELL_COUNT++;
}
void Cell::selfRemove()
{
	if (gameEngineIndex != UINT_MAX)
	{
		GameEngine::CURRENT_CELL_COUNT--;
	}
}
