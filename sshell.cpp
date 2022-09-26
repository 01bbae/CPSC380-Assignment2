#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstring>

#define MAX_LINE 80

using namespace std;

int main(int argc, char const *argv[])
{
    printf("Works!\n");

    char *args[MAX_LINE / 2 + 1]; /* max of 40 arguments */
    char input[MAX_LINE / 2 + 1];
    int should_run = 1;
    int i, wstatus;
    pid_t pid, w;
    bool childwait = false;

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);

        /** fork a child to execute command (using one of the exec calls)
             Break out of loop if user types ‘quit’ or ‘exit’ then exit
        program **/
        // cin.ignore(255, '\n');
        memset(input, 0, 41);
        cin.getline(input, sizeof(input));

        // argument tokenizer
        char *tok = strtok(input, " &");
        i = 0;

        while (tok != NULL and i < sizeof(input))
        {
            if (tok[i] == '&')
            {
                childwait = true;
            }
            args[i] = tok;
            ++i;
            tok = strtok(NULL, " &");
        }
        args[MAX_LINE / 2] = NULL;
        printf("finished tokenizing\n");

        if (strcmp(args[0], &"exit"[0]) == 0 || strcmp(args[0], &"quit"[0]) == 0)
        {
            should_run = 0;
        }
        else
        {
            // pid = fork();
            pid = 1;
            printf("created fork\n");
            switch (pid)
            {
            case -1:
                perror("fork creation failed\n");
                break;
            case 0:
                printf("running %s\n", *args);
                if (execvp(*args, (char *const *)args) < 0)
                {
                    perror("could not execute command");
                }
                printf("fork finished\n");
                break;
            default:
                cout << &args[0] << &args[1] << endl;
                if (execvp(*args, (char *const *)args) < 0)
                {
                    perror("could not execute command");
                }
                // waiting for children to finish
                if (childwait)
                {
                    w = wait(&wstatus);
                    if (WIFEXITED(wstatus))
                    {
                        printf("child exited with code %d\n", WEXITSTATUS(wstatus));
                    }
                    else
                    {
                        printf("child not terminated normally\n");
                    }
                }
                printf("parent finished\n");
                break;
            }
        }
    }

    return 0;
}
