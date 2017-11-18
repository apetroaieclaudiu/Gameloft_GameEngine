#pragma once
#include "../Utilities/utilities.h"
#include <string>

struct TextureResource
{
	std::string		type;
	std::string		path;
	GLint			min_filter;
	GLint			mag_filter;
	GLint			wrap_s;
	GLint			wrap_t;
};