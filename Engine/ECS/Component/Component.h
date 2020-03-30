#pragma once

class Entity;

class Component
{
public:
	explicit Component(Entity* entity);

    Entity* GetEntity() const;
    int GetEntityID() const;

    bool enabled = true;
	
private:
    Entity* _entity;
};