#include "headers.h"
#include "prompt.h"
#include "pathmanager.h"
#include "processmanager.h"
#include "input.h"

int main() {
    initialize_path();
    start_list();


    size_t len = 0;
    while (1) {
        prompt();
        input();
    }
    return 0;
}