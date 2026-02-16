#pragma once
#include <iostream>
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "core/random.h"


enum CompType
{
	BASE,
	TRANSFORM,
	MOVE,
	MESH,
	COLLIDER,
	LIGHT
};



namespace Thingies
{

class Entity;

//----------------------------------------------------------------------------------------------------------------------------------


class BaseComponent
{
private:
	// Variable to store owner entity

public:
	Entity* owner;
	CompType type;
	BaseComponent();
	BaseComponent(Entity* newOwner, CompType comptype) : owner(newOwner), type(comptype) {};
	virtual ~BaseComponent();

	// Performs all component behavior
	//virtual void Update();

	virtual void Draw() {};


	// Sets up any needed connecuions to other components
	virtual void Start();
	
	// Function to get owner entity
	Entity* GetOwner();
	CompType GetType();
};

//----------------------------------------------------------------------------------------------------------------------------------

// Child component classes


class TransformComp : public BaseComponent
{
private:
	glm::mat4 transform;

public:
	TransformComp(Entity* newOwner, glm::mat4 trans) : BaseComponent(newOwner, TRANSFORM), transform(trans) {};
	~TransformComp();
	glm::mat4 GetTransform();
};


class MeshComp : public BaseComponent
{
private:
	Render::ModelId mesh;
	TransformComp* transform;
	
public:
	//void Start() override;
	MeshComp(Entity* newOwner, Render::ModelId mID, TransformComp* trans) : BaseComponent(newOwner, MESH), mesh(mID), transform(trans) {} ;
	~MeshComp();
	Render::ModelId GetMesh();
	glm::mat4 PullTransform();

	void Draw() override;

};

class ColliderComp : public BaseComponent
{
private:
	Physics::ColliderId collider;

public:
	ColliderComp(Entity* newOwner, Physics::ColliderId cID) : BaseComponent(newOwner, COLLIDER), collider(cID) {} ;
	~ColliderComp();
	Physics::ColliderId GetCollider();
};







//----------------------------------------------------------------------------------------------------------------------------------
}
