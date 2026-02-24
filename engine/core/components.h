#pragma once
#include <iostream>
#include "render/model.h"
#include "render/physics.h"
#include "render/resourceid.h"
#include "render/particlesystem.h"
#include "core/random.h"


enum CompType
{
	BASE,
	TRANSFORM,
	MOVE,
	MESH,
	COLLIDER,
	HEALTH,
	SHIP,
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
	virtual void Update(float dt) {};
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
	void SetTransform(glm::mat4 newTrans);
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
	void Draw() override;
	Render::ModelId GetMesh();
	glm::mat4 PullTransform();

};

class ColliderComp : public BaseComponent
{
private:
	Physics::ColliderId collider;

public:
	ColliderComp(Entity* newOwner, Physics::ColliderId cID) : BaseComponent(newOwner, COLLIDER), collider(cID) {} ;
	~ColliderComp();
	//void Update(float dt) override;
	Physics::ColliderId GetCollider();
};

class MoveComp : public BaseComponent
{
private:
	TransformComp* transform;
	glm::vec3 axis;
	float angle;

public:
	MoveComp(Entity* newOwner, glm::vec3 ax, float radian, TransformComp* trans) : BaseComponent(newOwner, MOVE), axis(ax), angle(radian), transform(trans) {} ;
	void Update(float dt) override;
};

class HealthComp : public BaseComponent
{
private:
	int health;

public:
	HealthComp(Entity* newOwner, int hp) : BaseComponent(newOwner, HEALTH), health(hp) {};
	void LoseHealth(int hit);
	void AddHealth(int potion);
	int GetHealth();
};

class ShipComp : public BaseComponent
{
private:
	TransformComp* transComp;
	glm::vec3 position = glm::vec3(0);
	glm::quat orientation = glm::identity<glm::quat>();
	glm::vec3 camPos = glm::vec3(0, 1.0f, -2.0f);
	glm::mat4 transform = glm::mat4(1);
	glm::vec3 linearVelocity = glm::vec3(0);

	const float normalSpeed = 1.0f;
	const float boostSpeed = normalSpeed * 2.0f;
	const float accelerationFactor = 1.0f;
	const float camOffsetY = 1.0f;
	const float cameraSmoothFactor = 10.0f;

	float currentSpeed = 0.0f;

	float rotationZ = 0;
	float rotXSmooth = 0;
	float rotYSmooth = 0;
	float rotZSmooth = 0;

	Render::ParticleEmitter* particleEmitterLeft;
	Render::ParticleEmitter* particleEmitterRight;
	float emitterOffset = -0.5f;

	const glm::vec3 colliderEndPoints[17] = {
		glm::vec3(1.40173, 0.0, -0.225342),  // left wing back
		glm::vec3(1.33578, 0.0, 0.088893),  // left wing front
		glm::vec3(0.227107, -0.200232, -0.588618),  // left back engine bottom
		glm::vec3(0.227107, 0.228809, -0.588618),  // left back engine top
		glm::vec3(0.391073, -0.130853, 1.28339),  // left weapon
		glm::vec3(0.134787, 0.0, 1.68965),  // left front
		glm::vec3(0.134787, 0.250728, 0.647422),  // left wind shield

		glm::vec3(-1.40173, 0.0, -0.225342),  // right wing back
		glm::vec3(-1.33578, 0.0, 0.088893),  // right wing front
		glm::vec3(-0.227107, -0.200232, -0.588618),  // right back engine bottom
		glm::vec3(-0.227107, 0.228809, -0.588618),  // right back engine top
		glm::vec3(-0.391073, -0.130853, 1.28339),  // right weapon
		glm::vec3(-0.134787, 0.0, 1.68965),  // right front
		glm::vec3(-0.134787, 0.250728, 0.647422),  // right wind shield

		glm::vec3(0.0, 0.525049, -0.392836),  // top back
		glm::vec3(0.0, 0.739624, 0.102582),  // top fin
		glm::vec3(0.0, -0.244758, 0.284825),  // bottom
	};

public:
	ShipComp(Entity* newOwner, TransformComp* trans);
	~ShipComp();
	void Update(float dt) override;
	bool CheckCollisions();
	glm::vec3 GetPos();

};

class LaserComp : public BaseComponent
{
private:
	float laserSpeed;
	TransformComp* transComp;

public:
	LaserComp(Entity* newOwner, TransformComp* tComp);
	~LaserComp();
	void Update(float dt) override;
};





//----------------------------------------------------------------------------------------------------------------------------------
}
