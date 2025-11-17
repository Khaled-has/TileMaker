#include "Application.h"


int main(int argc, char** argv)
{
	Editor::Application* app = Editor::CreateApplication();

	app->Run();
	delete app;

	return 0;
}