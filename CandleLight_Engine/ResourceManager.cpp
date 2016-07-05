#include "ResourceManager.h"

Loader ResourceManager::_loader;

Texture ResourceManager::loadTexture(const std::string & filePath)
{
	Texture tex = {};
	tex = _loader.loadPNG(filePath);
	tex.filePath = filePath;
	return tex;
}
