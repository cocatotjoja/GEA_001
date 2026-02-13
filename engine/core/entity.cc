#include "config.h"
#include "core/entity.h"

using namespace Thingies;

Entity::~Entity()
{
	compList.clear();
}

void Thingies::Entity::AddComp(BaseComponent* newComp)
{
	compList.push_back(newComp);
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
