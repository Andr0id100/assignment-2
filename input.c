#include "headers.h"
#include "processmanager.h"
#include "history.h"

int count_tokens(char *, char);
char **get_tokens(char *, char);
void replace_tabs(char *);

void input()
{
    // Declaring a small buffer which is resized by the getline function according to input size
    char *line = malloc(1 * sizeof(char));
    ssize_t len = 1;
    getline(&line, &len, stdin);
    add_entry(line);

    // Removing the \n from input
    line[len - 2] = '\0';
    // Replacing the tabs with spaces for ease of handling
    replace_tabs(line);

    // Dividing the input into separate commands to run
    char **commands = get_tokens(line, ';');

    // Running the commands one at a time
    int i = 0;
    while (commands[i] != NULL)
    {
        char** components = get_tokens(commands[i], ' ');
        start_process(components);
        i++;
    }
}

void replace_tabs(char *line)
{
    int i = 0;
    while (line[i] != '\0')
    {
        if (line[i] == '\t')
        {
            line[i] = ' ';
        }
        i++;
    }
}

char **get_tokens(char *input, char delim)
{

    int token_count = count_tokens(input, delim);
    char **tokens = malloc((token_count + 1) * sizeof(char *));

    char *token = strtok(input, &delim);
    int i = 0;
    while (token != NULL)
    {
        tokens[i++] = token;
        token = strtok(NULL, &delim);
    }
    tokens[i] = NULL;
    return tokens;
}

int count_tokens(char *input, char delim)
{
    int count = 0;
    int p = 0;
    int token_started = 0;
    while (input[p] != '\0')
    {
        if (input[p] == delim)
        {
            if (token_started)
            {
                token_started = 0;
                count++;
            }
        }
        else
        {
            if (!token_started)
            {
                token_started = 1;
            }
        }

        p++;
    }
    if (token_started)
        count++;
    return count;
}