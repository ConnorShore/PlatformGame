#pragma once

#include "Component.h"
#include "LuaManager.h"

class ScriptComponent : public Component
{
public:
	ScriptComponent(const std::string& script) 
	{
		scriptName = script;

		LuaManager::instance()->loadScript(scriptName);
		LuaManager::instance()->callFunction("initialize");
	}

	~ScriptComponent() {}

	virtual void update() override 
	{
		LuaManager::instance()->loadScript(scriptName, false);
		LuaManager::instance()->callFunction("update");
	}

	virtual std::string getID() override { return "script"; }


	std::string scriptName;
};