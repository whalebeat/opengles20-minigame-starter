#include "targetver.h"
#include "Shader.h"
#include "Application.h"
#include "utilities.h" 

int Globals::screenWidth = 480;
int Globals::screenHeight = 800;

GLint Init(ESContext* esContext)
{
	Application::GetInstance()->Init();
	return 0;
}

void Draw(ESContext* esContext)
{
	Application::GetInstance()->Render();
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, GLfloat deltaTime)
{
	Application::GetInstance()->Update(deltaTime);
}

void OnKey(ESContext* esContext, unsigned char key, bool bbIsPresseded)
{
	Application::GetInstance()->HandleKeyEvent(key, bbIsPresseded);
}

void OnMouseClick(ESContext* esContext, GLint x, GLint y, bool bbIsPresseded)
{
	Application::GetInstance()->HandleTouchEvent(x, y, bbIsPresseded);
}

void OnMouseMove(ESContext* esContext, GLint x, GLint y)
{
	Application::GetInstance()->HandleMouseMoveEvent(x, y);
}

void CleanUp()
{
	Application::GetInstance()->Exit();
	Application::FreeInstance();
}

GLint _tmain(GLint argc, _TCHAR* argv[])
{
	ESContext esContext;
	esInitContext(&esContext);
	esCreateWindow(&esContext, "Epic Game", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);
	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, OnKey);
	esRegisterMouseFunc(&esContext, OnMouseClick);
	esRegisterMouseMoveFunc(&esContext, OnMouseMove);
	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//printf("Press any key...\n");
	//_getch();

	return 0;
}