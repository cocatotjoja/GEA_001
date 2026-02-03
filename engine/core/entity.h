#pragma once

#include <iostream>
#include <vector>
#include "core/components.h"

namespace Thingies
{
class Entity
{
private:
	std::vector<BaseComponent*> compList;

public:
	Entity();
	~Entity();

};
}