#include "headers.h"
#include "pathmanager.h"

void prompt() {
    struct passwd* pw = getpwuid(getuid());
    char* hostname = (char*)malloc(64 * sizeof(char));
    gethostname(hostname, 64);
    printf("\r<%s@%s:", pw->pw_name, hostname);
    print_path();
    printf(">");
}
