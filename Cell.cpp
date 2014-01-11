#include "Cell.h"
#include "GameEngine.h"
#include "MyEngine.h"
#include "SelfMovingPhysicalComponent.h"
#include "CellPhysicalComponent.h"


Cell::Cell(GameEngine *engine) : ReplicableGameObject(engine)
{
	objectType = cellType;
	this->model = &engine->getParentEngine()->getRenderer()->getModels()[Renderer::CELL_MODEL_INDEX];
	physicalComponent = new CellPhysicalComponent();
	physicalComponent->setGameObject(this);
}

Cell::Cell(GameEngine *engine, RenderableComponent *model, PhysicalComponent *physicalComponent) : ReplicableGameObject(engine, model, physicalComponent, 3)
{
	objectType = cellType;
}

Cell::Cell(const Cell &cell) : ReplicableGameObject(cell)
{
	objectType = cellType;
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
	if (false &&GameEngine::CURRENT_CELL_COUNT < GameEngine::MAX_CELL_COUNT && GameEngine::CURRENT_CELL_COUNT < GameEngine::MAX_GAME_OBJECT_COUNT)
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
	ReplicableGameObject::selfRemove();
	if (gameEngineIndex != UINT_MAX)
	{
		GameEngine::CURRENT_CELL_COUNT--;
	}
}
