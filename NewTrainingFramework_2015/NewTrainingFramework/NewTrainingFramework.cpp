// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "resourceManager.h"
#include "sceneManager.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h" // if you use STL, please include this line AFTER all other include

Camera	cam;
float	contor = 0;
bool	wired = false;
resourceManager* res = resourceManager::getInstance();
sceneManager*    scn = sceneManager::getInstance();


int Init(ESContext *esContext)
{

	glEnable(GL_DEPTH_TEST);
	resourceManager::getInstance()->Init();
	sceneManager::getInstance()->Load();
	//seteaza culoarea de background
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	return 0;
}

void Draw(ESContext *esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	sceneManager::getInstance()->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
 }

void Update(ESContext *esContext, float deltaTime)
{
	sceneManager::getInstance()->Update();
	contor += deltaTime;
	if (contor >= 0.05)
	{
		contor -= 0.05;
		cam.setDeltaTime(deltaTime);
	}
	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
	{
		printf("Merge...\n");
	}
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{

		switch (key)
		{
		case 'W':
			cam.moveOz(-1);
			break;
		case 'S':
			cam.moveOz(1);
			break;
		case 'Q':
			cam.moveOy(1);
			break;
		case 'E':
			cam.moveOy(-1);
			break;
		case 'A':
			cam.moveOx(1);
			break;
		case 'D':
			cam.moveOx(-1);
			break;
		case 'Z':
			cam.rotateOz(-1);
			break;
		case VK_UP:
			cam.rotateOx(1);
			break;
		case VK_RIGHT:
			cam.rotateOy(-1);
			break;
		case VK_DOWN:
			cam.rotateOx(-1);
			break;
		case VK_LEFT:
			cam.rotateOy(1);
			break;
		case 'X':
			cam.rotateOz(1);
			break;
		case 'F':
			wired = false;
			break;
		case 'T':
			wired = true;
			break;
		}
}

void CleanUp()
{
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();


	return 0;
}

