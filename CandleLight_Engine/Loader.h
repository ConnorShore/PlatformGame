#pragma once

#include "picoPNG.h"
#include "Texture.h"
#include <string>

class Loader
{
public:
	Loader();
	~Loader();

	Texture loadPNG(std::string filePath);
	bool loadFile(const std::string& fileName, std::vector<unsigned char>& buffer);

private:

};

