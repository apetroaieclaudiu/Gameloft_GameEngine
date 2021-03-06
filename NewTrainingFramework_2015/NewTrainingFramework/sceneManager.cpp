#include "stdafx.h"
#include "../Resources/RapidXML/rapidxml.hpp"
#include "sceneManager.h"
#include "resourceManager.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace rapidxml;
using namespace std;

extern Camera cam;

sceneManager* sceneManager::spInstance = NULL;

sceneManager::sceneManager()
{
}


void	sceneManager::Load()
{
	lightTypes = Vector3(0.0, 0.0, 0.0);
	xml_document<> doc;
	xml_node<> * root_node;
	// Read the xml file into a vector
	ifstream theFile("../Resources/sceneManager/sceneManager.xml");
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc 
	doc.parse<0>(&buffer[0]);
	// Find our root node
	root_node = doc.first_node("sceneManager");
	// Iterate over the brewerys
	backgroundColor.x = atof(root_node->first_node("backgroundColor")->first_node("r")->value());
	backgroundColor.y = atof(root_node->first_node("backgroundColor")->first_node("g")->value());
	backgroundColor.z = atof(root_node->first_node("backgroundColor")->first_node("b")->value());

	for (xml_node<> * pNode = root_node->first_node("cameras"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("camera"); pTest; pTest = pTest->next_sibling())
		{
			Camera *cam = new Camera{ Vector3(atof(pTest->first_node("position")->first_node("x")->value()),
				atof(pTest->first_node("position")->first_node("y")->value()),
				atof(pTest->first_node("position")->first_node("z")->value())),
				Vector3(atof(pTest->first_node("target")->first_node("x")->value()),
					atof(pTest->first_node("target")->first_node("y")->value()),
					atof(pTest->first_node("target")->first_node("z")->value())),
				Vector3(atof(pTest->first_node("up")->first_node("x")->value()),
					atof(pTest->first_node("up")->first_node("y")->value()),
					atof(pTest->first_node("up")->first_node("z")->value())),
					(GLfloat)atof(pTest->first_node("translationSpeed")->value()),
				(GLfloat)atof(pTest->first_node("rotationSpeed")->value()),
				(GLfloat)atof(pTest->first_node("fov")->value()),
				(GLfloat)atof(pTest->first_node("near")->value()),
				(GLfloat)atof(pTest->first_node("far")->value()) };
			unsigned int i = atoi(pTest->first_attribute("id")->value());
			cameras.insert(pair <unsigned int, Camera*>(i, cam));
		}
	}
	for (xml_node<> * pNode = root_node->first_node("objects"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("object"); pTest; pTest = pTest->next_sibling())
		{
			SceneObject *so;
			if ((strcmp(pTest->first_node("type")->value(), "terrain")) == 0)
			{
				Terrain *t = new Terrain(atoi(pTest->first_node("cells")->value()), (float)atof(pTest->first_node("size")->value()), (float)atof(pTest->first_node("offsetY")->value()), pTest->first_node("model")->value());
				t->setHeight(Vector3(atof(pTest->first_node("inaltimi")->first_node("r")->value()),
					atof(pTest->first_node("inaltimi")->first_node("g")->value()),
					atof(pTest->first_node("inaltimi")->first_node("b")->value())));
				so = (SceneObject*)t;
			}
			else if ((strcmp(pTest->first_node("type")->value(), "normal")) == 0)
			{
				so = new SceneObject();
			}
			else if ((strcmp(pTest->first_node("type")->value(), "SkyBox")) == 0)
			{
				SkyBox *s = new SkyBox();
				so = (SceneObject*)s;
			}
			else if ((strcmp(pTest->first_node("type")->value(), "Fire")) == 0)
			{
				so = new Fire(atof(pTest->first_node("dispMax")->value()));
			}
			so->position = Vector3(atof(pTest->first_node("position")->first_node("x")->value()),
				atof(pTest->first_node("position")->first_node("y")->value()),
				atof(pTest->first_node("position")->first_node("z")->value()));
			so->rotation = Vector3(atof(pTest->first_node("rotation")->first_node("x")->value()),
							atof(pTest->first_node("rotation")->first_node("y")->value()),
							atof(pTest->first_node("rotation")->first_node("z")->value()));
			so->scale = Vector3(atof(pTest->first_node("scale")->first_node("x")->value()),
							atof(pTest->first_node("scale")->first_node("y")->value()),
							atof(pTest->first_node("scale")->first_node("z")->value()));
			so->depthTest = pTest->first_node("depthTest")->value() == "true" ? true : false;
			unsigned int i = atoi(pTest->first_attribute("id")->value());
			if (strcmp(pTest->first_node("model")->value(),"generated")!=0)
				so->setModel(resourceManager::getInstance()->loadModel(atoi(pTest->first_node("model")->value())));
			
			so->setShader(resourceManager::getInstance()->loadShader(atoi(pTest->first_node("shader")->value())));
			for (xml_node<> *pTex = pTest->first_node("textures")->first_node("texture"); pTex; pTex = pTex->next_sibling())
			{
				so->addTexture(resourceManager::getInstance()->loadTexture(atoi(pTex->first_attribute("id")->value())));
			}
			objects.insert(pair <unsigned int, SceneObject*>(i, so));
		}
	}

	for (xml_node<> * pNode = root_node->first_node("lights"); pNode; pNode = pNode->next_sibling())
	{
		for (xml_node<> * pTest = pNode->first_node("light"); pTest; pTest = pTest->next_sibling())
		{
			if (strcmp(pTest->first_attribute("type")->value(), "Spotlight") == 0)
			{
				lightTypes.z = 1.0;
				diffColor = Vector3(atof(pTest->first_node("Difuza")->first_node("color")->first_node("r")->value()), atof(pTest->first_node("Difuza")->first_node("color")->first_node("g")->value()), atof(pTest->first_node("Difuza")->first_node("color")->first_node("b")->value()));
				diffDirection = Vector3(atof(pTest->first_node("Difuza")->first_node("direction")->first_node("x")->value()), atof(pTest->first_node("Difuza")->first_node("direction")->first_node("y")->value()), atof(pTest->first_node("Difuza")->first_node("direction")->first_node("z")->value()));
				specColor = Vector3(atof(pTest->first_node("Speculara")->first_node("color")->first_node("r")->value()), atof(pTest->first_node("Speculara")->first_node("color")->first_node("g")->value()), atof(pTest->first_node("Speculara")->first_node("color")->first_node("b")->value()));
				specPower = atof(pTest->first_node("Speculara")->first_node("power")->value());
				spotLightOpening = atof(pTest->first_node("deschidere")->value());
				spotLightPosition = Vector3(atof(pTest->first_node("position")->first_node("x")->value()), atof(pTest->first_node("position")->first_node("y")->value()), atof(pTest->first_node("position")->first_node("z")->value()));
				spotLightAttenuation = atof(pTest->first_node("attenuation")->value());
			}
			if (strcmp(pTest->first_attribute("type")->value(), "Directional") == 0)
			{
				lightTypes.y = 1.0;
				diffColor = Vector3(atof(pTest->first_node("Difuza")->first_node("color")->first_node("r")->value()), atof(pTest->first_node("Difuza")->first_node("color")->first_node("g")->value()), atof(pTest->first_node("Difuza")->first_node("color")->first_node("b")->value()));
				diffDirection = Vector3(atof(pTest->first_node("Difuza")->first_node("direction")->first_node("x")->value()), atof(pTest->first_node("Difuza")->first_node("direction")->first_node("y")->value()), atof(pTest->first_node("Difuza")->first_node("direction")->first_node("z")->value()));
				specColor = Vector3(atof(pTest->first_node("Speculara")->first_node("color")->first_node("r")->value()), atof(pTest->first_node("Speculara")->first_node("color")->first_node("g")->value()), atof(pTest->first_node("Speculara")->first_node("color")->first_node("b")->value()));
				specPower = atof(pTest->first_node("Speculara")->first_node("power")->value());
			}	
			if (strcmp(pTest->first_attribute("type")->value(), "Point") == 0)
			{
				lightTypes.x = 1.0;
				diffColor = Vector3(atof(pTest->first_node("Difuza")->first_node("color")->first_node("r")->value()), atof(pTest->first_node("Difuza")->first_node("color")->first_node("g")->value()), atof(pTest->first_node("Difuza")->first_node("color")->first_node("b")->value()));
				diffDirection = Vector3(atof(pTest->first_node("Difuza")->first_node("direction")->first_node("x")->value()), atof(pTest->first_node("Difuza")->first_node("direction")->first_node("y")->value()), atof(pTest->first_node("Difuza")->first_node("direction")->first_node("z")->value()));
			}
			if (strcmp(pTest->first_attribute("type")->value(), "Ambientala") == 0)
			{
				ambientalColor = Vector3(atof(pTest->first_node("color")->first_node("r")->value()), atof(pTest->first_node("color")->first_node("g")->value()), atof(pTest->first_node("color")->first_node("b")->value()));
			}
		}
	}
	xml_node<> * pNode = root_node->first_node("fog");
	color = Vector3(atof(pNode->first_node("color")->first_node("r")->value()), atof(pNode->first_node("color")->first_node("g")->value()), atof(pNode->first_node("color")->first_node("b")->value()));
	r = atof(pNode->first_node("raza_mica")->value());
	R = atof(pNode->first_node("raza_mare")->value());
	pNode = root_node->first_node("ratio");
	ratio = atof(pNode->value());
	


	theFile.close();
}

void sceneManager::Update()
{
	for (std::map<unsigned int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		it->second->Update();

}

void	sceneManager::Draw()
{
	for (std::map<unsigned int, SceneObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		it->second->Draw();

}

sceneManager* sceneManager::getInstance() {

	if (!spInstance) {
		spInstance = new sceneManager();
	}

	return spInstance;
}

sceneManager::~sceneManager()
{
	spInstance = NULL;
}

//
//if ((strcmp(pTest->first_node("type")->value(), "normal")) == 0)
//{
//	SceneObject *s = new SceneObject{ Vector3(atof(pTest->first_node("position")->first_node("x")->value()),
//		atof(pTest->first_node("position")->first_node("y")->value()),
//		atof(pTest->first_node("position")->first_node("z")->value())),
//		Vector3(atof(pTest->first_node("rotation")->first_node("x")->value()),
//			atof(pTest->first_node("rotation")->first_node("y")->value()),
//			atof(pTest->first_node("rotation")->first_node("z")->value())),
//		Vector3(atof(pTest->first_node("scale")->first_node("x")->value()),
//			atof(pTest->first_node("scale")->first_node("y")->value()),
//			atof(pTest->first_node("scale")->first_node("z")->value())),
//		pTest->first_node("depthTest")->value() == "true" ? true : false };
//	unsigned int i = atoi(pTest->first_attribute("id")->value());
//	s->setModel(resourceManager::getInstance()->loadModel(atoi(pTest->first_node("model")->value())));
//	s->setShader(resourceManager::getInstance()->loadShader(atoi(pTest->first_node("shader")->value())));
//	for (xml_node<> *pTex = pTest->first_node("textures")->first_node("texture"); pTex; pTex = pTex->next_sibling())
//	{
//		s->addTexture(resourceManager::getInstance()->loadTexture(atoi(pTex->first_attribute("id")->value())));
//	}
//	objects.insert(pair <unsigned int, SceneObject*>(i, s));
//}
//else if ((strcmp(pTest->first_node("type")->value(), "terrain")) == 0)
//{
//	SceneObject *s = new Terrain{ atoi(pTest->first_node("cells")->value()), (float)atof(pTest->first_node("size")->value()), (float)atof(pTest->first_node("offsetY")->value()), pTest->first_node("model")->value() };
//
//	unsigned int i = atoi(pTest->first_attribute("id")->value());
//	s->setShader(resourceManager::getInstance()->loadShader(atoi(pTest->first_node("shader")->value())));
//	for (xml_node<> *pTex = pTest->first_node("textures")->first_node("texture"); pTex; pTex = pTex->next_sibling())
//	{
//		s->addTexture(resourceManager::getInstance()->loadTexture(atoi(pTex->first_attribute("id")->value())));
//	}
//	objects.insert(pair <unsigned int, SceneObject*>(atoi(pTest->first_attribute("id")->value()), s));
//}