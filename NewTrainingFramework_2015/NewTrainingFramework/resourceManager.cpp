#include "stdafx.h"
#include "../Resources/RapidXML/rapidxml.hpp"
#include "resourceManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
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
			ModelResource *mr = new ModelResource{ pTest->first_node("path")->value() };
			unsigned int i = atoi(pTest->first_attribute("id")->value());
			models.insert(pair <unsigned int, ModelResource*>(i, mr));

		}
	}
	for (xml_node<> * pNode = root_node->first_node("shaders"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("shader"); pTest; pTest = pTest->next_sibling())
		{
			ShaderResource *mr = new ShaderResource{ pTest->first_node("vs")->value(), pTest->first_node("fs")->value() };
			unsigned int i = atoi(pTest->first_attribute("id")->value());
			shaders.insert(pair <unsigned int, ShaderResource*>(i, mr));
		}
	}
	for (xml_node<> * pNode = root_node->first_node("textures"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("texture"); pTest; pTest = pTest->next_sibling())
		{
			TextureResource *tr = new TextureResource{ pTest->first_attribute("type")->value(), pTest->first_node("path")->value(),
				pTest->first_node("min_filter")->value(), pTest->first_node("mag_filter")->value(), pTest->first_node("wrap_s")->value(),
				pTest->first_node("wrap_t")->value() };
			unsigned int i = atoi(pTest->first_attribute("id")->value());
			textures.insert(pair <unsigned int, TextureResource*>(i, tr));
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

Model* resourceManager::loadModel(unsigned int i)
{
	std::map<unsigned int, Model*>::iterator it;

	it = loadedModels.find(i);
	if (it != loadedModels.end())
		return it->second;
	else {
		Model *m = new Model();
		std::map<unsigned int, ModelResource*>::iterator search;
		search = models.find(i);
		m->setMr(search->second);
		m->Load();
		loadedModels.insert(pair <unsigned int, Model*>(i, m));
		return m;
	}
}

Texture* resourceManager::loadTexture(unsigned int i)
{
	std::map<unsigned int, Texture*>::iterator it;

	it = loadedTextures.find(i);
	if (it != loadedTextures.end())
		return it->second;
	else {
		Texture *m = new Texture();
		std::map<unsigned int, TextureResource*>::iterator search;
		search = textures.find(i);
		m->setMr(search->second);
		m->Load();
		loadedTextures.insert(pair <unsigned int, Texture*>(i, m));
		return m;
	}
}

Shader* resourceManager::loadShader(unsigned int i)
{
	std::map<unsigned int, Shader*>::iterator it;

	it = loadedShaders.find(i);
	if (it != loadedShaders.end())
		return it->second;
	else {
		Shader *m = new Shader();
		std::map<unsigned int, ShaderResource*>::iterator search;
		search = shaders.find(i);
		m->setMr(search->second);
		m->Load();
		loadedShaders.insert(pair <unsigned int, Shader*>(i, m));
		return m;
	}
}