#pragma once

#include <iostream>
#include "core/entity.h" // IS this correct ASK FREDRIK!!!!


enum CompType
{
	TRANSFORM,
	MOVE,
	DRAW,
	LIGHT
};



namespace Thingies
{
class BaseComponent
{
private:
	// Variable to store owner entity
	Entity* owner;
	CompType type;

public:
	BaseComponent();
	~BaseComponent();

	// Performs all component behavior
	virtual void Update();


	// Sets up any needed connecuions to other components
	void Start();
	
	// Function to get owner entity
	Entity* GetOwner();
	CompType GetType();
};
}