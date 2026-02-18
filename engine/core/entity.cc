#include "config.h"
#include "core/entity.h"

using namespace Thingies;

Thingies::Entity::Entity()
{
	//std::cout << "Entity Created!" << std::endl;
}

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


void Thingies::Entity::Update(float dt)
{
	for (size_t i = 0; i < this->compList.size(); i++)
	{
		this->compList[i]->Update(dt);
	}
}


void Thingies::Entity::Draw()
{
	for (size_t i = 0; i < this->compList.size(); i++)
	{
		this->compList[i]->Draw();
	}
}