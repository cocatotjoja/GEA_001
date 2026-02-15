#include "config.h"
#include "components.h"
#include "entity.h"


// Base Component functions------------------------------------------------------------------------------

Thingies::BaseComponent::BaseComponent()
{
	owner = nullptr;
	type = BASE;
	//std::cout << "Base Component Created!" << std::endl;
}

Thingies::BaseComponent::~BaseComponent()
{
	//std::cout << "Base Component Destroyed!" << std::endl;
}

void Thingies::BaseComponent::Start()
{
	//std::cout << "Base Component Start!" << std::endl;
}

Thingies::Entity* Thingies::BaseComponent::GetOwner()
{
	return owner;
}

CompType Thingies::BaseComponent::GetType()
{
	return type;
}



// Mesh Component functions------------------------------------------------------------------------------

/*
void Thingies::MeshComp::Start()
{
	transform = dynamic_cast<TransformComp*>(owner->GetComp(TRANSFORM));
}
*/

Thingies::MeshComp::~MeshComp()
{
	//std::cout << "Mesh Component Destroyed!" << std::endl;
}

Render::ModelId Thingies::MeshComp::GetMesh()
{
	return mesh;
}

glm::mat4 Thingies::MeshComp::PullTransform()
{
	return transform->GetTransform();
}





// Transform Component functions-------------------------------------------------------------------------

Thingies::TransformComp::~TransformComp()
{
	//std::cout << "Transform Component Destroyed!" << std::endl;
}

glm::mat4 Thingies::TransformComp::GetTransform()
{
	return transform;
}






// Transform Component functions-------------------------------------------------------------------------

Thingies::ColliderComp::~ColliderComp()
{
	//std::cout << "Collider Component Destroyed!" << std::endl;
}

Physics::ColliderId Thingies::ColliderComp::GetCollider()
{
	return collider;
}

