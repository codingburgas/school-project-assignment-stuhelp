// main.cpp
// CALLS THE APP ENGINE WHICH RENDERS THE STUFF ELSE IT WILL CATCH THE ERROR PREVENTING A CRASH!
#include "AppEngine.h"
#include <iostream>

int main() {
    AppEngine app;
    if (!app.isWindowCreated()) {
        std::cerr << "The SFML window could not be created." << std::endl;
        return -1;
    }

    app.run();
    return 0;
}
