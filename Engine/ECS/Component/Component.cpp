#include "Component.h"
#include "../Entity/Entity.h"

Component::Component(Entity* entity) :
    _entity(entity)
{}

Entity* Component::GetEntity() const
{
    return _entity;
}

int Component::GetEntityID() const
{
    return _entity->GetID();
}
