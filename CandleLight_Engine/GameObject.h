#pragma once

#include "Transform.h"
#include "Component.h"

#include <string>
#include <map>

class GameObject
{
public:
	typedef std::multimap<const ComponentType, Component*> ComponentBag;

	GameObject(unsigned int id);
	~GameObject();

	void update();
	void attachComponent(Component* component);
	Component* removeComponent(ComponentType& type);
	Component* removeComponent(ComponentType& type, int id);

	Component* getComponent(const ComponentType& type);
	ComponentBag getComponents() const { return _components; }

	bool hasComponent(const ComponentType& type);
	bool hasComponentWithTag(std::string& tag);

	unsigned int getID() const { return _id; }
	void setID(const unsigned int id) { _id = id; }

	Transform transform;
	std::string name;

private:
	ComponentBag _components;
	unsigned int _id;
};
