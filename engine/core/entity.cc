#include "config.h"
#include "entity.h"

using namespace Thingies;

Entity::~Entity()
{
	compList.clear();
}


BaseComponent* Entity::GetComp(CompType typeC)
{
	for (BaseComponent* comp : compList)
	{
		if (comp->GetType() == typeC)
		{
			return comp;
		}
	}
	return nullptr;
}
