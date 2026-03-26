#include "config.h"

#include <gtc/type_ptr.hpp>

#include "NetBase.h"
#include "entity.h"
#include "worldManager.h"

ActionResult NetBase::Start(std::string IP)
{
	return ACTION_SUCCEEDED;
}

ActionResult NetBase::End()
{
	return ACTION_SUCCEEDED;
}

void NetBase::UpdateAsteroid(AsteroidUpdate packetData)
{
	uint32_t index = packetData.entityID;
	Thingies::Entity* ent = owner.GetEntity(index);

	// TODO: Should I add entity types???? ASK FREDRIK

	Thingies::TransformComp* tComp = (Thingies::TransformComp*)ent->GetComp(TRANSFORM);
	glm::mat4 trans = glm::make_mat4(packetData.transform);
	tComp->SetTransform(trans);
}
