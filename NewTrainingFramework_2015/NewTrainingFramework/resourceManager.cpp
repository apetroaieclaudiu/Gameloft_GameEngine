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

void			 resourceManager::parsare()
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
			printf("ID: %s\n", pTest->first_attribute("id")->value());
			printf("Path: %s\n", pTest->first_node("path")->value());
		}
	}
	cout << '\n';
	for (xml_node<> * pNode = root_node->first_node("shaders"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("shader"); pTest; pTest = pTest->next_sibling())
		{
			printf("ID: %s\n", pTest->first_attribute("id")->value());
			printf("VS: %s\n", pTest->first_node("vs")->value());
			printf("FS: %s\n", pTest->first_node("fs")->value());
		}
	}
	cout << '\n';
	for (xml_node<> * pNode = root_node->first_node("textures"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("texture"); pTest; pTest = pTest->next_sibling())
		{
			printf("ID: %s\n", pTest->first_attribute("id")->value());
			printf("TYPE: %s\n", pTest->first_attribute("type")->value());
			printf("Path: %s\n", pTest->first_node("path")->value());
			printf("MIN_FILTER: %s\n", pTest->first_node("min_filter")->value());
			printf("MAG_FILTER: %s\n", pTest->first_node("mag_filter")->value());
			printf("WRAP_S: %s\n", pTest->first_node("wrap_s")->value());
			printf("WRAP_T: %s\n", pTest->first_node("wrap_t")->value());
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
