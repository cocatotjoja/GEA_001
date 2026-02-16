#pragma once

#include <iostream>
#include <vector>
#include "components.h"

namespace Thingies
{

class Entity
{
private:
	std::vector<BaseComponent*> compList;

public:
	Entity();
	~Entity();

	// Adds a given BaseComponent* to the components vector, takes a BaseComponent*
	void AddComp(BaseComponent* newComp);

	// Searches the vector of components and returns a BaseComponent*, takes a CompType(ENUM)
	BaseComponent* GetComp(CompType typeC);

	void Draw();

	void PrintCompNum();
};
}