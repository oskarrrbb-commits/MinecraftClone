#include "core/Application.h"
#include <cstdio>

int main() {
    try {
        Application app;
        app.run();
    } catch (const std::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    
    return 0;
}