#include "config.h"
#include "components.h"
#include "entity.h"


// Mesh Component functions------------------------------------------------------------------------------

Render::ModelId Thingies::MeshComp::GetMesh()
{
	return mesh;
}

glm::mat4 Thingies::MeshComp::PullTransform()
{
	return transform->GetTransform();
}





// Transform Component functions-------------------------------------------------------------------------

glm::mat4 Thingies::TransformComp::GetTransform()
{
	return transform;
}






// Transform Component functions-------------------------------------------------------------------------

Physics::ColliderId Thingies::ColliderComp::GetCollider()
{
	return collider;
}
