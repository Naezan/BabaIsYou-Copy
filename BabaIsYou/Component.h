#pragma once

class Entity;

class Component
{
public:
	Entity* componentOwner;

	virtual void init() {}
	virtual void update(float deltaTime) {}
	virtual void render() {}
	virtual ~Component() {}
};

