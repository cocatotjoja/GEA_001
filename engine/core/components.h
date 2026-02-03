#pragma once

#include <iostream>
#include "core/entity.h" // IS this correct ASK FREDRIK!!!!

namespace Thingies
{
class BaseComponent
{
private:
	// Variable to store owner entity
	Entity* owner;

public:
	BaseComponent();
	~BaseComponent();
	virtual void Update();
	// Function to get parent
	Entity* GetOwner();
};
}