#pragma once

#include <string>

#include "Loader.h"
#include "Texture.h"

class ResourceManager
{
public:

	static Texture loadTexture(const std::string& filePath);

private:
	static Loader _loader;
};

