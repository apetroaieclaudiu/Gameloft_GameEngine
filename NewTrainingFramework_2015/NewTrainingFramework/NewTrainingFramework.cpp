// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include "Model.h"

GLuint	vboId;
GLuint	elementbuffer;
GLuint	textureUniform;
GLuint	id_textura;
Shaders myShaders;
Camera	cam;
Model	model("../Resources/Models/Croco.nfg");
int width, height, bpp;
GLuint format;

int Init ( ESContext *esContext )
{
	//seteaza culoarea de background
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), &(model.indices)[0], GL_STATIC_DRAW);
	//buffer object
	glGenBuffers(1, &vboId);
	//Imi leaga buffer de vboId
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, model.points.size() * sizeof(Vertex), &(model.points)[0], GL_STATIC_DRAW); //Static draw -> nu mi modifica bufferul
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	char *array_pixeli;
	
	array_pixeli = LoadTGA("../Resources/Textures/Croco.tga", &width, &height, &bpp);
	
	if (bpp == 24) {
		format = GL_RGB;
	}
	else {
		format = GL_RGBA;
	}

	glGenTextures(1, &id_textura);
	glBindTexture(GL_TEXTURE_2D, id_textura);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid *) array_pixeli);
	glBindTexture(GL_TEXTURE_2D, 0);
	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs"); //Se da calea catre shadere
}

void Draw ( ESContext *esContext )
{
	Matrix m;
	m.SetScale(0.01f, 0.01f, 0.01f);
	Matrix mvp = m * cam.getView();
	Matrix P;
	
	P.SetPerspective(cam.getFOV(),(GLfloat) Globals::screenWidth / Globals::screenHeight, cam.getNear(), cam.getFar());
	mvp = mvp * P;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(myShaders.program); //alegem shaderul folosit

	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBindTexture(GL_TEXTURE_2D, id_textura);

	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.uvAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (4 * sizeof(Vector3)));
	}

	if (myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (GLfloat *)mvp.m);
	}

	if (myShaders.textureUniform != -1)
	{
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(textureUniform, 0);
	}

	glDrawElements(GL_TRIANGLES, model.indices.size(), GL_UNSIGNED_INT, (void *) 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	cam.setDeltaTime(deltaTime);

	if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
	{
		printf("Merge...\n");
	}
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
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
		cam.moveOy(-1);
		break;
	case 'E':
		cam.moveOy(1);
		break;
	case 'A':
		cam.moveOx(-1);
		break;
	case 'D':
		cam.moveOx(1);
		break;
	case 'Z':
		cam.rotateOz(1);
		break;
	case VK_UP:
		cam.rotateOx(-1);
		break;
	case VK_RIGHT:
		cam.rotateOy(1);
		break;
	case VK_DOWN:
		cam.rotateOx(1);
		break;
	case VK_LEFT:
		cam.rotateOy(-1);
		break;
	case 'X':
		cam.rotateOz(-1);
		break;
	}
}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;

	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );

	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

