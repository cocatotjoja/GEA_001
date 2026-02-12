#pragma once

#include <iostream>
#include "config.h"
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "core/random.h"


enum CompType
{
	TRANSFORM,
	MOVE,
	MESH,
	LIGHT
};



namespace Thingies
{
//----------------------------------------------------------------------------------------------------------------------------------


class BaseComponent
{
private:
	// Variable to store owner entity
	Entity* owner;
	CompType type;

public:
	BaseComponent();
	virtual ~BaseComponent();

	// Performs all component behavior
	virtual void Update();


	// Sets up any needed connecuions to other components
	virtual void Start();
	
	// Function to get owner entity
	Entity* GetOwner();
	CompType GetType();
};

//----------------------------------------------------------------------------------------------------------------------------------

// Child component classes

class MeshComp : public BaseComponent
{
private:
	Render::ModelId mesh;
	TransformComp* transform;
	
public:
	void Start() override;
	MeshComp(Render::ModelId mID) : mesh(mID) {} ;
	~MeshComp();
	Render::ModelId GetMesh();
	glm::mat4 GetTransform();

};

class TransformComp : public BaseComponent
{
private:
	glm::mat4 transform;

public:
	TransformComp(glm::mat4 trans) : transform(trans) {} ;
	~TransformComp();
	glm::mat4 GetTransform();
};

class ColliderComp : public BaseComponent
{
private:
	Physics::ColliderId collider;

public:
	ColliderComp(Physics::ColliderId cID) : collider(cID) {} ;
	~ColliderComp();
	Physics::ColliderId GetCollider();
};







//----------------------------------------------------------------------------------------------------------------------------------
}
