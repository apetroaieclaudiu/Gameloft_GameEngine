// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"

GLuint vboId;
Shaders myShaders;
GLfloat alpha = 0.0f;
Camera	cam;

int Init ( ESContext *esContext )
{
	//seteaza culoarea de background
	glClearColor ( 0.0f, 0.0f, 0.0f, 0.0f );

	//triangle data (heap)
	Vertex verticesData[3];
	//inmultim cu matricea de proiectie ca sa ducem in spatiul (-1,1)
	verticesData[0].pos.x =  0.0f;  verticesData[0].pos.y =  0.5f;  verticesData[0].pos.z =  0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z =  0.0f;
	verticesData[2].pos.x =  0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z =  0.0f;
	
	verticesData[0].color.x = 1.0f;	verticesData[0].color.y = 0.0f;	verticesData[0].color.z = 0.0f;
	verticesData[1].color.x = 0.0f;	verticesData[1].color.y = 1.0f;	verticesData[1].color.z = 0.0f;
	verticesData[2].color.x = 0.0f;	verticesData[2].color.y = 0.0f;	verticesData[2].color.z = 1.0f;

	//buffer object
	glGenBuffers(1, &vboId);
	//Imi leaga buffer de vboId
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW); //Static draw -> nu mi modifica bufferul
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs"); //Se da calea catre shadere

}

void Draw ( ESContext *esContext )
{
	Matrix mr;
	Matrix Pers;
	
	Pers.SetPerspective(cam.getFOV(), (float)Globals::screenWidth / (float)Globals::screenHeight, cam.getNear(), cam.getFar());

	alpha += 0.0f;

	mr.SetRotationZ(alpha);
	Matrix mvp = mr * cam.getViewMatrix() * Pers;
	
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program); //alegem shaderul folosit

	glBindBuffer(GL_ARRAY_BUFFER, vboId);

	if(myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}

	if (myShaders.matrixUniform != -1)
	{
		glUniformMatrix4fv(myShaders.matrixUniform, 1, GL_FALSE, (GLfloat *)mvp.m);
	}

	if(myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) sizeof(Vector3));
	}

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );
}

void Update ( ESContext *esContext, float deltaTime )
{
	cam.setDeltaTime(deltaTime);
}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (key == 'W')
		cam.moveOz(-1);

	if (key == 'S')
		cam.moveOz(1);

	if (key == 'A')
		cam.moveOx(-1);

	if (key == 'D')
		cam.moveOx(1);
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

