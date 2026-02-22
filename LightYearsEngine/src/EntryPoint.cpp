#include "EntryPoint.h"
#include "framework/Application.h"

int main(int argc, char* argv[])
{
    ly::Application* app = get_application();
    app->Run();
    delete app;
}
