#include <iostream>

#include "framework/Application.h"

int main()
{
    // allocating on heap 
    std::unique_ptr<ly::Application> app{new ly::Application()};
    app->Run();
    std::cout << "Hello Worlds!" << '\n';
}
