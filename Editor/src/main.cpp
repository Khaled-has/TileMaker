#include "Application.h"


int main(int argc, char** argv)
{
	auto app = Editor::CreateApplication();

	app->Run();
	delete app;

	return 0;
}