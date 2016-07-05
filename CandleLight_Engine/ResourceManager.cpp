#include "ResourceManager.h"

Loader ResourceManager::_loader;

Texture ResourceManager::loadTexture(const std::string & filePath)
{
	return _loader.loadPNG(filePath);
}
