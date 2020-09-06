#include "headers.h"
#include "prompt.h"
#include "pathmanager.h"
#include "input.h"

int main() {
    initializePath();

    size_t len = 0;
    while (1) {
        prompt();
        input();
    }
    return 0;
}