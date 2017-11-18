#include "stdafx.h"
#include "../Resources/RapidXML/rapidxml.hpp"
#include "resourceManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../Utilities/utilities.h"

using namespace rapidxml;
using namespace std;

resourceManager* resourceManager::spInstance = NULL;

resourceManager::resourceManager()
{
	
}

void			 resourceManager::Init()
{
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile("../Resources/resourceManager/resourceManager.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("resourceManager");
	// Iterate over the brewerys
	for (xml_node<> * pNode = root_node->first_node("models"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("model"); pTest; pTest = pTest->next_sibling())
		{
			ModelResource temp = { pTest->first_node("path")->value() };
			model.insert (pair <int, ModelResource> (atoi(pTest->first_attribute("id")->value()), temp));
		}
	}
	for (xml_node<> * pNode = root_node->first_node("shaders"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("shader"); pTest; pTest = pTest->next_sibling())
		{
			ShaderResource temp = { pTest->first_node("vs")->value(), pTest->first_node("fs")->value()};
			shader.insert(pair <int, ShaderResource> (atoi(pTest->first_attribute("id")->value()), temp));
		}
	}

	for (xml_node<> * pNode = root_node->first_node("textures"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("texture"); pTest; pTest = pTest->next_sibling())
		{

			TextureResource temp = { pTest->first_attribute("type")->value(), pTest->first_node("path")->value(),(GLint) pTest->first_node("min_filter")->value(),
				(GLint) pTest->first_node("mag_filter")->value(),(GLint) pTest->first_node("wrap_s")->value(),(GLint) pTest->first_node("wrap_t")->value()};
			textures.insert(pair <int, TextureResource>(atoi(pTest->first_attribute("id")->value()), temp));
		}
	}
	theFile.close();
}

resourceManager* resourceManager::getInstance() {
	
	if (!spInstance) {
		spInstance = new resourceManager();
	}

	return spInstance;
}

resourceManager::~resourceManager()
{
	spInstance = NULL;
}
